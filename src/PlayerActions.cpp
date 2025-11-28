#include "PlayerActions.h"
#include <cstdlib>

void updateBranches(int seed);


const float HIT_POSITION_LEFT = 700.f;
const float HIT_POSITION_RIGHT = 1075.f;

void handleChopRight(
    side& playerSide,
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
)
{
    playerSide = side::RIGHT;
    spritePlayerRight.setPosition(1100, 850);
    score++;
    timeRemaining += (2.f / score) + .15f;

    spriteHitRight.setPosition(HIT_POSITION_RIGHT, spriteHitRight.getPosition().y);

    updateBranches(score);

    spriteLog.setPosition(810, 900);
    logSpeedX = -5000.f;
    logActive = true;
    acceptInput = false;

    chop.play();

    int randFuncIdx = std::rand() % 4;
    switch (randFuncIdx) {
    case 0: chop2.play(); break;
    case 1: chop3.play(); break;
    case 2: chop4.play(); break;
    default: break;
    }
}

void handleChopLeft(
    side& playerSide,
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
)
{
    playerSide = side::LEFT;
    score++;
    timeRemaining += (2.f / score) + .15f;

    spriteHitLeft.setPosition(HIT_POSITION_LEFT, spriteHitLeft.getPosition().y);
    spritePlayerLeft.setPosition(650, 850);

    updateBranches(score);

    spriteLog.setPosition(810, 900);
    logSpeedX = 5000.f;
    logActive = true;
    acceptInput = false;

    chop.play();

    int randFuncIdx = std::rand() % 4;
    switch (randFuncIdx) {
    case 0: chop2.play(); break;
    case 1: chop3.play(); break;
    case 2: chop4.play(); break;
    default: break;
    }

}
