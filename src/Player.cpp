#include "Player.h"

Player::Player(Map &mapRef)
    : Entity(), map(mapRef), damageSound(damageBuffer), walkSound(walkBuffer)
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
  sprite.setPosition({720.f / 2.f, 480.f / 2.f});

  velocity = {0.f, 0.f};
  speed = 250.f;
  hunger = 10;
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
}

void Player::update(float deltaTime)
{
  if (getHealth() <= 0) {
    return;
  }
  // Movement
  position += velocity * deltaTime;
  sprite.setPosition(position);

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
    if (walkSound.getStatus() == sf::Sound::Status::Stopped) {
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
}

void Player::takeDamage(int damage)
{
  if (!damageImmune && health > 0)
  {
    health - damage >= 0 ? health -= damage : health = 0;
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

bool Player::pickUpItem(Item* item) {
  if (inventory.isFull()) {
      return false;
  }
  inventory.addItem(item);
  return true;
}

void Player::displayInventory() {
  inventory.displayInventory();
}