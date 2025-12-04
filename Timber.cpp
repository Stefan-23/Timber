#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "include/PlayerActions.h"
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace sf;

const int NUM_BRANCHES = 7;

// Branch sprites and positions
Sprite branches[NUM_BRANCHES];
side   branchPositions[NUM_BRANCHES];

// Globals 
side  playerSide = side::LEFT;
int   score = 0;
float timeRemaining = 6.0f;
bool  acceptInput = false;
bool  logActive = false;
float logSpeedX = 0.0f;

Sprite spritePlayer;
Sprite spritePlayer2;
Sprite spriteHit;
Sprite spriteHit2;
Sprite spriteLog;

Sound chop;
Sound chop2;
Sound chop3;
Sound chop4;

// 
void updateBranches(int seed);

int main()
{
    
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "JCVD Training!!", Style::Fullscreen);
    //Clock
    Clock clock;

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 10);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    //********** Background ********** 

    //Creating background for game
    Texture textureBackground;
    //Loading background
    textureBackground.loadFromFile("graphics/background.png");
    //Creating Sprite
    Sprite spriteBackground;
    //Connecting Spite
    spriteBackground.setTexture(textureBackground);
    //Setting position for Sprite
    spriteBackground.setPosition(0, 0);

    //********** Background **********

    //********** Tree **********
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);
    //********** Tree **********

    //********** Bee **********
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    //Is bee moving
    bool beeActive = false;
    float beeSpeed = 0.0f;
    //Second kunai
    Texture textureBee1;
    textureBee1.loadFromFile("graphics/bee.png");
    Sprite spriteBee1;
    spriteBee1.setTexture(textureBee1);
    spriteBee1.setPosition(0, 1000);
    //Is bee moving
    bool beeActive1 = false;
    float beeSpeed1 = 0.0f;
    //********** Bee **********

    //********** Cloud **********
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    //Creating Sprite for 3 clouds
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    //Position for clouds
    spriteCloud1.setPosition(0, 850);
    spriteCloud2.setPosition(0, 900);
    spriteCloud3.setPosition(0, 950);
    //Clound movement
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    //Cloud position
    spriteCloud1.setPosition(0, 0);

    //********** Cloud *********
    sf::Text messageText;
    sf::Text scoreText;

    //Font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to start JCVD Training");
    scoreText.setString("Score = 0");
    //Font size
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    //Color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    //HUD 

    // Prepare 5 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        // Set the sprite's origin to dead centre
        // We can then spin it round without changing its position
        branches[i].setOrigin(220, 20);
    }

    // Player
    Texture texturePlayerLeft;
    Texture texturePlayerRight;
    texturePlayerLeft.loadFromFile("graphics/JCVD1.gif");
    texturePlayerRight.loadFromFile("graphics/JCVD2.gif");
    spritePlayer.setTexture(texturePlayerLeft);
    spritePlayer2.setTexture(texturePlayerRight);
    spritePlayer.setPosition(650, 850);
    spritePlayer2.setPosition(1100, 850);
    playerSide = side::LEFT;

    // RIP / hits / streak
    Texture textureRIP;
    Texture textureHitLeft;
    Texture textureHitRight;
    Texture textureStreak;
    textureRIP.loadFromFile("graphics/rip.png");
    textureHitLeft.loadFromFile("graphics/jcvdLft.png");
    textureHitRight.loadFromFile("graphics/jcvdLft1.png");
    textureStreak.loadFromFile("graphics/RIP.jpg");

    Sprite spriteRIP(textureRIP);
    spriteHit2.setTexture(textureHitLeft);
    spriteHit.setTexture(textureHitRight);
    Sprite spriteStreak(textureStreak);

    spriteRIP.setPosition(650, 900);
    spriteHit.setPosition(2000, 850);
    spriteHit2.setPosition(2000, 850);
    spriteStreak.setPosition(-2000, -2000);

    // Log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 900);
    logActive = false;
    logSpeedX = 1000.0f;
    float logSpeedY = -1500.0f;

    // Sounds
    SoundBuffer menuBuffer;
    SoundBuffer chopBuffer;
    SoundBuffer chop2Buffer;
    SoundBuffer chop3Buffer;
    SoundBuffer chop4Buffer;
    SoundBuffer deathBuffer;
    SoundBuffer ootBuffer;

    menuBuffer.loadFromFile("sound/menu.wav");
    chopBuffer.loadFromFile("sound/chop.wav");
    chop2Buffer.loadFromFile("sound/chop2.wav");
    chop3Buffer.loadFromFile("sound/chop3.wav");
    chop4Buffer.loadFromFile("sound/chop4.wav");
    deathBuffer.loadFromFile("sound/death.wav");
    ootBuffer.loadFromFile("sound/out_of_time.wav");

    Sound menu(menuBuffer);
    chop.setBuffer(chopBuffer);
    chop2.setBuffer(chop2Buffer);
    chop3.setBuffer(chop3Buffer);
    chop4.setBuffer(chop4Buffer);
    Sound death(deathBuffer);
    Sound outOfTime(ootBuffer);

    bool paused = true;
    score = 0;

    int streak[4] = { 10, 20, 50, 100 };

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased && !paused)
            {
                acceptInput = true;
                spriteHit.setPosition(2000, spriteHit.getPosition().y);
                spriteHit2.setPosition(2000, spriteHit2.getPosition().y);
            }
        }

        // HUD positions
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(
            textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f
        );
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        scoreText.setPosition(20, 20);

        // General input
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            menu.play();
            score = 0;
            timeRemaining = 6.0f;
            paused = false;

            for (int i = 0; i < NUM_BRANCHES; ++i)
                branchPositions[i] = side::NONE;

            spriteRIP.setPosition(675, 2000);
            spritePlayer.setPosition(650, 850);
            spritePlayer2.setPosition(1100, 850);
            playerSide = side::LEFT;
            acceptInput = true;
        }

        // Player input (left / right)
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
                handleInput(side::RIGHT);
            else if (Keyboard::isKeyPressed(Keyboard::Left))
                handleInput(side::LEFT);

            // Streak
            bool showStreak = false;
            for (int s : streak)
                if (score == s)
                    showStreak = true;

            spriteStreak.setPosition(
                showStreak ? Vector2f(1500.0f, 20.0f)
                : Vector2f(-2000.0f, -2000.0f)
            );
        }

        // Update 
        if (!paused)
        {
            Time dt = clock.restart();
            float dtSec = dt.asSeconds();

            timeRemaining -= dtSec;
            timeBar.setSize(Vector2f(
                timeBarWidthPerSecond * timeRemaining,
                timeBarHeight
            ));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of time");
                outOfTime.play();
            }

            // Bee 1
            if (!beeActive)
            {
                beeSpeed = (std::rand() % 200) + 200;
                float height = (std::rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.move(-beeSpeed * dtSec, 0);
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            // Bee 2
            if (!beeActive1)
            {
                beeSpeed1 = (std::rand() % 250) + 200;
                float height = (std::rand() % 550) + 500;
                spriteBee1.setPosition(2000, height);
                beeActive1 = true;
            }
            else
            {
                spriteBee1.move(-beeSpeed1 * dtSec, 0);
                if (spriteBee1.getPosition().x < -100)
                    beeActive1 = false;
            }

            // Clouds
            if (!cloud1Active)
            {
                cloud1Speed = 150;
                spriteCloud1.setPosition(-200, 800);
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.move(cloud1Speed * dtSec, 0);
                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            if (!cloud2Active)
            {
                cloud2Speed = 200;
                spriteCloud2.setPosition(-200, 850);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.move(cloud2Speed * dtSec, 0);
                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            if (!cloud3Active)
            {
                cloud3Speed = 300;
                spriteCloud3.setPosition(-200, 900);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.move(cloud3Speed * dtSec, 0);
                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;
            }

            // Score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            // Branch sprites
            for (int i = 0; i < NUM_BRANCHES; ++i)
            {
                float height = i * 150.0f;

                if (branchPositions[i] == side::LEFT)
                {
                    branches[i].setPosition(610.0f, height);
                    branches[i].setRotation(180.0f);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330.0f, height);
                    branches[i].setRotation(0.0f);
                }
                else
                {
                    branches[i].setPosition(3000.0f, height);
                }
            }

            // Log movement
            if (logActive)
            {
                spriteLog.move(logSpeedX * dtSec, logSpeedY * dtSec);
                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000)
                {
                    logActive = false;
                    spriteLog.setPosition(810, 900);
                }
            }

            // Check if player is hit by branch
            if (branchPositions[6] == playerSide)
            {
                paused = true;
                acceptInput = false;

                spriteRIP.setPosition(650, 900);
                spritePlayer.setPosition(2000, 660);

                messageText.setString("Steven Seagal WINS!!");
                death.play();
            }
        }

        // Draw scene
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);

        for (int i = 0; i < NUM_BRANCHES; ++i)
            window.draw(branches[i]);

        if (event.type == Event::KeyReleased && !paused)
        {
            if (event.key.scancode == sf::Keyboard::Scan::Left)
            {
                window.draw(spritePlayer);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Right)
            {
                window.draw(spritePlayer2);
            }

            //window.draw(spritePlayer);
            //window.draw(spritePlayer2);
        }
        else
        {
            acceptInput = false;
        }

        if (event.key.scancode == sf::Keyboard::Scan::Enter)
        {
            window.draw(spritePlayer);
        }

        window.draw(spriteHit);
        window.draw(spriteHit2);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(spriteBee);
        window.draw(spriteBee1);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(scoreText);
        window.draw(timeBar);
        window.draw(spriteStreak);

        if (paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}

// Moves branches down and spawns new one at the top
void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; --j)
        branchPositions[j] = branchPositions[j - 1];

    std::srand(static_cast<unsigned>(std::time(nullptr)) + seed);
    int r = std::rand() % 5;

    switch (r)
    {
    case 0: branchPositions[0] = side::LEFT;  break;
    case 1: branchPositions[0] = side::RIGHT; break;
    default: branchPositions[0] = side::NONE; break;
    }
}
