#include "Player.h"
#include "GameManager.h"
#include "Spear.h"

Player::Player(GameManager &gm, Map &mapRef)
    : Entity(), gameManager(gm), window(nullptr), map(mapRef), damageSound(damageBuffer), walkSound(walkBuffer)
{
  if (!idleTexture.loadFromFile(PLAYER_IDLE_PATH))
    throw std::runtime_error("Failed to load idle texture!");
  if (!walkTexture.loadFromFile(PLAYER_WALK_PATH))
    throw std::runtime_error("Failed to load walk texture!");

  if (!damageBuffer.loadFromFile("assets/sounds/takeDamage.wav"))
    throw std::runtime_error("Failed to load damage sound!");

  if (!walkBuffer.loadFromFile("assets/sounds/walking.wav"))
    throw std::runtime_error("Failed to load walking sound!");

  // Link buffers to sounds
  damageSound.setBuffer(damageBuffer);
  walkSound.setBuffer(walkBuffer);

  // Optional volume adjustment
  damageSound.setVolume(80.f);
  walkSound.setVolume(40.f);

  walkSound.setLooping(true);

  texture = idleTexture;
  sprite.setTexture(texture, true);

  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);

  sprite.setScale({1, 1});
  setPosition({static_cast<float>(map.getWidth()) / 2.f, static_cast<float>(map.getHeight()) / 2.f});

  velocity = {0.f, 0.f};
  speed = 250.f;
  hunger = 10;

  window = gameManager.getWindow();
}

void Player::handleInput(const sf::Event &event)
{
  velocity = {0.f, 0.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    velocity.y = -speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    velocity.y = speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    velocity.x = -speed;
    facingRight = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    velocity.x = speed;
    facingRight = true;
  }

  // Update animation state
  if (velocity.x != 0.f || velocity.y != 0.f)
    state = PlayerState::Walking;
  else
    state = PlayerState::Idle;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && equippedItem)
  {
    equippedItem->useItem();
  }

  if (event.is<sf::Event::KeyPressed>())
  {
    auto keyEvent = *event.getIf<sf::Event::KeyPressed>();

    switch (keyEvent.code)
    {
    case sf::Keyboard::Key::Num1:
      equipItem(0);
      break;
    case sf::Keyboard::Key::Num2:
      equipItem(1);
      break;
    case sf::Keyboard::Key::Num3:
      equipItem(2);
      break;
    case sf::Keyboard::Key::Num4:
      equipItem(3);
      break;
    case sf::Keyboard::Key::Num5:
      equipItem(4);
      break;
    case sf::Keyboard::Key::Num6:
      equipItem(5);
      break;
    case sf::Keyboard::Key::Num7:
      equipItem(6);
      break;
    case sf::Keyboard::Key::Num8:
      equipItem(7);
      break;
    case sf::Keyboard::Key::Num9:
      equipItem(8);
      break;
    case sf::Keyboard::Key::Num0:
      equipItem(9);
      break;

    case sf::Keyboard::Key::E: // unequip
      unequipItem();
      break;
    default:
      break;
    }
  }
}

void Player::render(sf::RenderWindow &window)
{
  window.draw(sprite);

  if (equippedItem && equippedItem->isVisible())
  {
    equippedItem->render(window);
  }
}

void Player::update(float deltaTime)
{
  if (getHealth() <= 0)
  {
    return;
  }
  // --- Movement ---
  sf::Vector2f oldPosition = position;

  // Try moving on X axis
  position.x += velocity.x * deltaTime;
  sprite.setPosition(position);

  // If collision, revert X movement
  if (map.isBlocked(sprite.getGlobalBounds()))
  {
    position.x = oldPosition.x;
    sprite.setPosition(position);
  }

  // Try moving on Y axis
  position.y += velocity.y * deltaTime;
  sprite.setPosition(position);

  // If collision, revert Y movement
  if (map.isBlocked(sprite.getGlobalBounds()))
  {
    position.y = oldPosition.y;
    sprite.setPosition(position);
  }

  // Animation frame switching
  if (state == PlayerState::Walking)
  {
    if (animationClock.getElapsedTime().asSeconds() > animationInterval)
    {
      // Toggle between idle/walk frames for a "stepping" look
      if (&sprite.getTexture() == &idleTexture)
        sprite.setTexture(walkTexture, true);
      else
        sprite.setTexture(idleTexture, true);

      animationClock.restart();
    }
    if (walkSound.getStatus() == sf::Sound::Status::Stopped)
    {
      walkSound.play();
    }
  }
  else
  {
    // Return to idle
    sprite.setTexture(idleTexture, true);

    walkSound.stop();
  }

  // Flip sprite based on direction
  sprite.setScale(facingRight ? sf::Vector2f(1.f, 1.f)
                              : sf::Vector2f(-1.f, 1.f));

  // Damage immunity timer
  if (damageImmune && immuneClock.getElapsedTime().asSeconds() >= immuneDuration)
  {
    damageImmune = false;
    sprite.setColor(sf::Color::White); // reset sprite color
  }

  if (hungerClock.getElapsedTime().asSeconds() > hungerDrainDuration)
  {
    setHunger((getHunger() - 1 >= 0 ? getHunger() - 1 : 0));
    hungerClock.restart();
  }

  if (getHunger() <= 0)
  {
    takeDamage(1);
  }

  if (regenClock.getElapsedTime().asSeconds() >= regenDelay && getHealth() < 10 && getHunger() > 7)
  {
    setHunger(getHunger() - 1);
    setHealth(getHealth() + 1);
    regenClock.restart();
  }

  if (equippedItem)
  {
    sf::Vector2f offset(25.f * (facingRight ? 1.f : -1.f), 0.f); // offset to the right or left
    equippedItem->setPosition(position + offset);
    sf::Vector2f currentScale = equippedItem->getScale();
    equippedItem->setScale({std::abs(currentScale.x) * (facingRight ? 1.f : -1.f),
                            currentScale.y});
  }
}

void Player::takeDamage(int damage)
{
  if (!damageImmune && health > 0)
  {
    health -= damage;
    if (health < 0)
      health = 0;
    damageImmune = true;
    immuneClock.restart();

    sprite.setColor(sf::Color(255, 150, 150)); // turn red
    damageSound.play();
  }
}

int Player::getHunger()
{
  return hunger;
}
void Player::setHunger(int hunger)
{
  this->hunger = hunger;
}
int Player::getWarmth()
{
  return warmth;
}
void Player::setWarmth(int warmth)
{
  this->warmth = warmth;
}

bool Player::pickUpItem(Item *item)
{
  if (inventory.isFull())
  {
    return false;
  }
  inventory.addItem(item);
  return true;
}

void Player::displayInventory()
{
  inventory.displayInventory();
}

int Player::getItemIndexSelected()
{
  return itemNumberSelected;
}

Item *Player::getItemSelected()
{
  if (itemNumberSelected < 0)
    return nullptr;
  return inventory.getItem(itemNumberSelected);
}

Item *Player::dropSelectedItem()
{
  int index = getItemIndexSelected();
  if (index < 0)
    return nullptr;

  Item *item = inventory.getItem(index);
  if (item)
  {
    inventory.removeItem(index);
    return item;
  }
  return nullptr;
}

void Player::equipItem(int index)
{
  Item *item = inventory.getItem(index);
  if (!item)
  {
    return;
  }

  equippedItem = item;
  item->setVisible(true);
  item->setActive(true);

  if (auto *spear = dynamic_cast<Spear *>(item))
    spear->bind(this, gameManager.getItems()); // or a getter for the world items vector
}

void Player::unequipItem()
{
  if (!equippedItem)
  {
    return;
  }
  equippedItem->setActive(false);
  equippedItem->setVisible(false);
  equippedItem = nullptr;
}

Item *Player::getEquippedItem() const
{
  return equippedItem;
}
