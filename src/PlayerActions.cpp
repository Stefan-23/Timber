#include "../include/PlayerActions.h"
#include <cstdlib>

const float HIT_POSITION_LEFT = 700.0f;
const float HIT_POSITION_RIGHT = 1075.0f;

void handleInput(side playerDirection)
{
    if (!acceptInput) return;

    playerSide = playerDirection;
    score++;

    // Increase time
    timeRemaining += (2.0f / score) + 0.15f;

    // Update player sprite and hit sprite based on side
    if (playerDirection == side::RIGHT)
    {
        spritePlayer2.setPosition(1100, 850);
        spriteHit.setPosition(HIT_POSITION_RIGHT, spriteHit.getPosition().y);
        logSpeedX = -5000;
    }
    else // LEFT
    {
        spritePlayer.setPosition(650, 850);
        spriteHit2.setPosition(HIT_POSITION_LEFT, spriteHit2.getPosition().y);
        logSpeedX = 5000;
    }

    // Update branches
    updateBranches(score);

    // Start log movement
    spriteLog.setPosition(810, 900);
    logActive = true;
    acceptInput = false;

    // Sound
    chop.play();
    int randFuncIdx = std::rand() % 4;

    switch (randFuncIdx)
    {
    case 0: chop2.play(); break;
    case 1: chop3.play(); break;
    case 2: chop4.play(); break;
    default: break;
    }
}
