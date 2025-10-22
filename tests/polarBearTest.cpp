#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PolarBear.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// A mock Player subclass for testing
class MockPlayer : public Player {
public:
    bool damaged = false;
    int damageTaken = 0;

    MockPlayer() {
        setPosition({0.f, 0.f});
        setHealth(100);
    }

    void takeDamage(int amount) override {
        damaged = true;
        damageTaken += amount;
    }
};

TEST_CASE("PolarBear initialization", "[PolarBear]") {
    MockPlayer player;
    PolarBear bear(&player);

    REQUIRE(bear.getHealth() == 200);
    REQUIRE(bear.getDamage() == 30);
}

TEST_CASE("PolarBear movement towards player", "[PolarBear]") {
    MockPlayer player;
    PolarBear bear(&player);

    // Place player far away
    player.setPosition({100.f, 0.f});
    bear.setPosition({0.f, 0.f});

    float deltaTime = 1.0f;
    bear.update(deltaTime);

    // After one second at speed 70, bear should have moved toward player
    REQUIRE(bear.getPosition().x > 0.f);
    REQUIRE(bear.getPosition().x <= Approx(70.f).epsilon(0.1));
}

TEST_CASE("PolarBear attacks when in range", "[PolarBear]") {
    MockPlayer player;
    PolarBear bear(&player);

    player.setPosition({0.f, 0.f});
    bear.setPosition({10.f, 0.f}); // within attack range (28.f)

    float deltaTime = 0.1f;
    bear.update(deltaTime);

    REQUIRE(player.damaged == true);
    REQUIRE(player.damageTaken == bear.getDamage());
}

TEST_CASE("PolarBear ignores non-spear damage", "[PolarBear]") {
    MockPlayer player;
    PolarBear bear(&player);

    int beforeHealth = bear.getHealth();
    bear.takeDamage(50); // Normal attack, should do nothing
    int afterHealth = bear.getHealth();

    REQUIRE(beforeHealth == afterHealth);
}

TEST_CASE("PolarBear roar output", "[PolarBear]") {
    MockPlayer player;
    PolarBear bear(&player);

    // Redirect std::cout for testing
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    bear.roar();

    std::cout.rdbuf(oldCout); // restore cout
    REQUIRE(oss.str().find("roars") != std::string::npos);
}
