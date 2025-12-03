#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class side { LEFT, RIGHT, NONE };

// External variables
extern side  playerSide;
extern int   score;
extern float timeRemaining;
extern bool  acceptInput;
extern bool  logActive;
extern float logSpeedX;

extern sf::Sprite spritePlayer;
extern sf::Sprite spritePlayer2;
extern sf::Sprite spriteHit;
extern sf::Sprite spriteHit2;
extern sf::Sprite spriteLog;

extern sf::Sound chop;
extern sf::Sound chop2;
extern sf::Sound chop3;
extern sf::Sound chop4;

void updateBranches(int seed);
void handleInput(side playerDirection);
