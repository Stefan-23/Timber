#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class PlayerSide { LEFT, RIGHT, NONE };

void handleChopRight(
    PlayerSide& playerSide,
    int& score,
    float& timeRemaining,
    bool& acceptInput,
    sf::Sprite& spritePlayerRight,
    sf::Sprite& spriteHitRight,
    sf::Sprite& spriteLog,
    bool& logActive,
    float& logSpeedX,
    sf::Sound& chop,
    sf::Sound& chop2,
    sf::Sound& chop3,
    sf::Sound& chop4
);

void handleChopLeft(
    PlayerSide& playerSide,
    int& score,
    float& timeRemaining,
    bool& acceptInput,
    sf::Sprite& spritePlayerLeft,
    sf::Sprite& spriteHitLeft,
    sf::Sprite& spriteLog,
    bool& logActive,
    float& logSpeedX,
    sf::Sound& chop,
    sf::Sound& chop2,
    sf::Sound& chop3,
    sf::Sound& chop4
);