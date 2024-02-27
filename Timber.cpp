//Inclucde C++ Libraries
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>

using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 7;
Sprite branches[NUM_BRANCHES];

// Where is the player/branch? 
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


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
    spriteBackground.setPosition(0,0);

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
    spriteBee.setPosition(0,800);
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

    //********** Cloud **********
    bool paused = true;
    int score = 0;
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
    //Player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/JCVD1.gif");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(720, 850);

    //Player
    Texture texturePlayer2;
    texturePlayer2.loadFromFile("graphics/JCVD2.gif");
    Sprite spritePlayer2;
    spritePlayer2.setTexture(texturePlayer2);
    spritePlayer2.setPosition(720, 850);

    //starting side
    side playerSide = side::LEFT;

    //RIP
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(650, 900);
    //Hit
    Texture textureHit;
    textureHit.loadFromFile("graphics/jcvdLft1.png");
    Sprite spriteHit;
    spriteHit.setTexture(textureHit);
    spriteHit.setPosition(1100, 850);

    Texture textureHit2;
    textureHit2.loadFromFile("graphics/jcvdLft.png");
    Sprite spriteHit2;
    spriteHit2.setTexture(textureHit2);
    spriteHit2.setPosition(650, 850);


    Texture textureStreak;
    textureStreak.loadFromFile("graphics/RIP.jpg");
    Sprite spriteStreak;
    spriteStreak.setTexture(textureStreak);
    spriteStreak.setPosition(650, 850);

    const float HIT_POSITION_LEFT = 700;
    const float HIT_POSITION_RIGHT = 1075;

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 900);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    //control input of player
    bool acceptInput = false;

    // Prepare the sound
    SoundBuffer menuBuffer;
    menuBuffer.loadFromFile("sound/menu.wav");
    Sound menu;
    menu.setBuffer(menuBuffer);

    // Prepare the sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    // Prepare the sound
    SoundBuffer chop1Buffer;
    chop1Buffer.loadFromFile("sound/chop1.wav");
    Sound chop1;
    chop1.setBuffer(chop1Buffer);

    // Prepare the sound
    SoundBuffer chop2Buffer;
    chop2Buffer.loadFromFile("sound/chop2.wav");
    Sound chop2;
    chop2.setBuffer(chop2Buffer);

    // Prepare the sound
    SoundBuffer chop3Buffer;
    chop3Buffer.loadFromFile("sound/chop3.wav");
    Sound chop3;
    chop3.setBuffer(chop3Buffer);

    // Prepare the sound
    SoundBuffer chop4Buffer;
    chop4Buffer.loadFromFile("sound/chop4.wav");
    Sound chop4;
    chop4.setBuffer(chop4Buffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    // Out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased && !paused)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Enter)
                {
                    acceptInput = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Left)
                {
                    acceptInput = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Right)
                {
                    acceptInput = true;
                }
                // Listen for key presses again
                //acceptInput = true;

                // hide the hit image
                spriteHit.setPosition(2000,
                    spriteHit.getPosition().y);
                // hide the hit image
                spriteHit2.setPosition(2000,
                    spriteHit2.getPosition().y);

                
            }
            
          
        }
        /*
            Player input
        */
        messageText.setFillColor(Color::White);
        scoreText.setFillColor(Color::White);
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        scoreText.setPosition(20, 20);

       
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            menu.play();
            score = 0;
            timeRemaining = 6;
            paused = false;
            //Hide branches
            for (int i = 1; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }
            //Hide RIP
            spriteRIP.setPosition(675, 2000);
            //Player position
            spritePlayer.setPosition(650, 850);
            acceptInput = true;
        }
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                //Player right side
                playerSide = side::RIGHT;
                spritePlayer2.setPosition(1100, 850);
                score++;
                //Time increase
                timeRemaining += (2 / score) + .15;
                spriteHit.setPosition(HIT_POSITION_RIGHT, spriteHit.getPosition().y);
                updateBranches(score);
                //Log moving
                spriteLog.setPosition(810, 900);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                // Play a chop sound
                chop.play();

                int randFuncIdx = std::rand() % 4;
                switch (randFuncIdx) {
                case 0:
                    chop2.play();
                    break;
                case 1:
                    chop3.play();
                    break;
                case 2:
                    chop4.play();
                    break;
                default:
                    break;
                }
                // chop.play();
            }

            // Player left side
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                //Player right side
                playerSide = side::LEFT;
                score++;
                //Time increase
                timeRemaining += (2 / score) + .15;
                spriteHit2.setPosition(HIT_POSITION_LEFT, spriteHit2.getPosition().y);
                spritePlayer.setPosition(650, 850);
                updateBranches(score);
                //Log moving
                spriteLog.setPosition(810, 900);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
                chop.play();

                int randFuncIdx = std::rand() % 4;
                switch (randFuncIdx) {
                case 0:
                    chop2.play();
                    break;
                case 1:
                    chop3.play();
                    break;
                case 2:
                    chop4.play();
                    break;
                default:
                    break;
                }
            }
            int streak[4] = { 10, 20, 50, 100 };
            for (int x = 0; x < 4; x++)
            {
                if (score == streak[x])
                {
                    spriteStreak.setPosition(1500, 20);
                }
                if (event.type == Event::KeyReleased && !paused)
                {
                    spriteStreak.setPosition(-2000, -2000);
                
                }

            }
        }
          
        /*
            Updating scene
        */
        if (!paused)
        {
            //Time
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;

                messageText.setString("Out of time");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            //Giving bee life
            if (!beeActive)
            {
                srand((int)time(0) * 10);
                beeSpeed = (rand() % 200) + 200;

                //Bee height
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

                //Bee side check
                if (spriteBee.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }


            //Second kunai movement
            if (!beeActive1)
            {
                srand((int)time(0) * 10);
                beeSpeed1 = (rand() % 250) + 200;

                //Bee height
                srand((int)time(0) * 10);
                float height = (rand() % 550) + 500;
                spriteBee1.setPosition(2000, height);
                beeActive1 = true;
            }
            else
            {
                spriteBee1.setPosition(spriteBee1.getPosition().x - (beeSpeed1 * dt.asSeconds()), spriteBee1.getPosition().y);

                //Bee side check
                if (spriteBee1.getPosition().x < -100)
                {
                    beeActive1 = false;
                }
            }
            // Cloud movement
            if (!cloud1Active)
            {
                //cloud speed
                srand((int)time(0) * 10);
                cloud1Speed = 150;
                //cloud height
                srand((int)time(0) * 10);
                float height = 800;
                spriteCloud1.setPosition(-200, height);
                cloud1Active = 1;
            }
            else
            {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

                if (spriteCloud1.getPosition().x > 1920)
                {
                    cloud1Active = false;
                }
            }
            if (!cloud2Active)
            {
                //cloud speed
                srand((int)time(0) * 20);
                cloud2Speed = 200;
                //cloud height
                srand((int)time(0) * 20);
                float height = 850;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

                if (spriteCloud2.getPosition().x > 1920)
                {
                    cloud2Active = false;
                }
            }
            if (!cloud3Active)
            {
                //cloud speed
                srand((int)time(0) * 30);
                cloud3Speed = 300;
                //cloud height
                srand((int)time(0) * 30);
                float height = 900;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

                if (spriteCloud3.getPosition().x > 1920)
                {
                    cloud3Active = false;
                }

                //Updating score text
                std::stringstream ss;
                ss << "Score = " << score;
                scoreText.setString(ss.str());
            }
            for (int i = 0; i < NUM_BRANCHES; i++)
            {

                float height = i * 150;

                if (branchPositions[i] == side::LEFT)
                {
                    // Move the sprite to the left side
                    branches[i].setPosition(600, height);
                    // Flip the sprite round the other way
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    // Move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // Set the sprite rotation to normal
                    branches[i].setRotation(0);

                }
                else
                {
                    // Hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    //Sprite goes to the left side
                    branches[i].setPosition(610, height);
                    //Mirror sprite
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    //Sprite goes to the right side
                    branches[i].setPosition(1330, height);
                    //Default value
                    branches[i].setRotation(0);
                }
                else
                {
                    //Hide branch
                    branches[i].setPosition(3000, height);
                }
            }
            if (logActive)
            {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                //Is log on the edge
                if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
                {
                    //Make log in next scene
                    logActive = false;
                    spriteLog.setPosition(810, 900);
                }
         
            }
            // has the player been squished by a branch?
			if (branchPositions[6] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				spriteRIP.setPosition(650, 900);

				// hide the player
				spritePlayer.setPosition(2000, 660);


				// Change the text of the message
				messageText.setString("Steven Seagal WINS!!");

				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);

				// Play the death sound
				death.play();


			}

    }

        // Drawing scene
        
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }
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
        //window.draw(spritePlayer);
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
        {
            window.draw(messageText);
        }

        //Removing everything from previous scene
        //Showing everything we created
        window.display();

    }
    return 0;

}
// Function definition
void updateBranches(int seed)
{
    // Move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT or NONE
    srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;

    case 1:
        branchPositions[0] = side::RIGHT;
        break;

    default:
        branchPositions[0] = side::NONE;
        break;
    }


}
