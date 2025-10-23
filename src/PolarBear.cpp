#include "PolarBear.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#include <SFML/Audio.hpp>

PolarBear::PolarBear(Player *playerPtr) : Enemy(playerPtr), roarSound(roarBuffer)
{
  if (!texture.loadFromFile("assets/textures/PolarBear.png"))
  {
    std::cout << "Error loading PolarBear.png\n";
  }

  if (!roarBuffer.loadFromFile("assets/sounds/polarBearRoar.wav"))
    throw std::runtime_error("Failed to load roar sound!");

  roarSound.setBuffer(roarBuffer);

  sf::IntRect bearRect({0, 0}, {108, 68}); // actual bear region in texture
  sprite.setTexture(texture, true);
  sprite.setTextureRect(bearRect);
  sprite.setScale({1.5f, 1.5f});
  sprite.setOrigin({static_cast<float>(bearRect.size.x / 2), static_cast<float>(bearRect.size.y / 2)});

  setHealth(50);
  setDamage(5);
}

void PolarBear::update(float deltaTime)
{
  if (!player)
    return;

  sf::Vector2f toPlayer = player->getPosition() - getPosition();
  float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
  sf::Vector2f dir = (distance > 0.001f) ? toPlayer / distance : sf::Vector2f{0.f, 0.f};

  switch (state)
  {
  case State::Idle:
  case State::Chasing:
  {
    // If within range and cooldown expired, start dash
    if (distance < dashRange && cooldownClock.getElapsedTime().asSeconds() > dashCooldown)
    {
      state = State::Dashing;
      dashDirection = dir; // Lock direction
      dashClock.restart();
      cooldownClock.restart(); // Reset cooldown timer
      if (!(roarSound.getStatus() == sf::Sound::Status::Playing))
        roar();
      break;
    }

    // Normal chase movement
    setPosition(getPosition() + dir * normalSpeed * deltaTime);
    sprite.setPosition(getPosition());
    break;
  }

  case State::Dashing:
  {
    // Move quickly in locked direction
    setPosition(getPosition() + dashDirection * dashSpeed * deltaTime);
    sprite.setPosition(getPosition());

    // End dash after dashDuration
    if (dashClock.getElapsedTime().asSeconds() > dashDuration)
    {
      state = State::Cooldown; // enter cooldown recovery
      dashClock.restart();
    }
    break;
  }

  case State::Cooldown:
  {
    // Bear rests briefly before resuming chase
    if (dashClock.getElapsedTime().asSeconds() > 0.5f) // short recovery pause
    {
      state = State::Chasing;
    }
    break;
  }
  }

  // Flip sprite orientation
  if (dir.x >= 0)
    sprite.setScale({-1.5f, 1.5f});
  else
    sprite.setScale({1.5f, 1.5f});

  // Attack if close
  if (player->getHitbox().findIntersection(this->getHitbox()))
    player->takeDamage(getDamage());
}

void PolarBear::takeDamage(int amount)
{
  // polar bear is a tough one
  health -= amount / 2;
}

void PolarBear::roar()
{
  roarSound.play();
}