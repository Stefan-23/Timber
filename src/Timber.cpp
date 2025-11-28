//Inclucde C++ Libraries
#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PlayerActions.h"

typedef std::map<std::string, Texture> TextureLibrary;
typedef std::map<std::string, SoundBuffer> SoundLibrary;
typedef Sound Clip;
using namespace sf;
void updateBranches(int seed);

const float HIT_POSITION_LEFT = 700;
const float HIT_POSITION_RIGHT = 1075;

const int NUM_BRANCHES = 7;
const int NUM_CLOUDS = 3;
const int NUM_KUNAI = 2;
const int NUM_CHOPS = 5;

PlayerSide branchPositions[NUM_BRANCHES];

struct GameTime {
    Clock clock;
    Time gameTimeTotal;
    float timeRemaining;
    float timeBarStartWidth;
    float timeBarWidthPerSecond;
    float timeBarHeight;
};

struct Sprites {
    Sprite background;
    Sprite tree;
    Sprite kunai[NUM_KUNAI];
    Sprite cloud[NUM_CLOUDS];
    Sprite branch[NUM_BRANCHES];
    Sprite player[2];
    Sprite streak;
    Sprite hit[2];
    Sprite log;
};

struct Clips {
    Clip menu;
    Clip chops[NUM_CHOPS];
    Clip death;
    Clip outOfTime;
};

struct GameplayCloud {
    bool active = false;
    float speed = 0.0f;
};

struct GameplayLog {
    bool active = false;
    float speedX = 1000;
    float speedY = -1500;
}; 

struct GameplayInput {
    PlayerSide playerSide = PlayerSide::LEFT;
    bool acceptInput = false;
};

struct Gameplay {
    GameplayCloud clouds[NUM_CLOUDS];
    GameplayLog log;
    GameplayInput input;
    bool paused = true;
    int score = 0;

};

struct UI {
    RectangleShape timeBar;
    Text messageText;
    Text scoreText;
};

struct GameResources {
    GameTime time;
    Font font;
    TextureLibrary textures;
    Sprites sprites;
    SoundLibrary sounds;
    Clips clips;
    Gameplay gameplay;
    UI ui;
};

void RegisterTexture(GameResources& res, std::string name, std::string path)
{
    Texture texture;
    texture.loadFromFile(path);
    res.textures[name] = texture;
}

void RegisterClip(GameResources& res, Sound& sound, std::string path)
{
    SoundBuffer buffer;
    buffer.loadFromFile(path);
    res.sounds[path] = buffer;
    sound.setBuffer(res.sounds[path]);
}

void GetSprite(GameResources& res, Sprite& sprite, std::string name)
{
    sprite.setTexture(res.textures[name]);
}

void InitializeGameTime(GameTime& time)
{
    time.timeBarStartWidth = 400;
    time.timeBarHeight = 80;
    time.timeRemaining = 6.0f;
    time.timeBarWidthPerSecond = time.timeBarStartWidth / time.timeRemaining;
}

void SetupSprite(GameResources& res, Sprite& sprite, 
    std::string name, float x, float y)
{
    sprite.setTexture(res.textures[name]);
    sprite.setPosition(x, y);
}

void InitializeTextures(GameResources& res)
{
    RegisterTexture(res, "background", "graphics/background.png");
    RegisterTexture(res, "tree", "graphics/tree.png");
    RegisterTexture(res, "kunai", "graphics/bee.png");
    RegisterTexture(res, "cloud", "graphics/cloud.png");
    RegisterTexture(res, "branch", "graphics/branch.png");
    RegisterTexture(res, "jcvd1", "graphics/JCVD1.gif");
    RegisterTexture(res, "jcvd2", "graphics/JCVD2.gif");
    RegisterTexture(res, "rip", "graphics/RIP.jpg");
    RegisterTexture(res, "hit1", "graphics/JCVDLft1.png");
    RegisterTexture(res, "hit2", "graphics/JCVDLft2.png");
    RegisterTexture(res, "log", "graphics/log.png");
}

void InitializeSounds(GameResources& res)
{
    // Menu
    RegisterClip(res, res.clips.menu, "sound/menu.wav");
    // Chops
    std::string paths[5]{
        "sound/chop.wav",
        "sound/chop1.wav",
        "sound/chop2.wav",
        "sound/chop3.wav",
        "sound/chop4.wav",
    };

    for (int i = 0; i < NUM_CHOPS; i++)
    {
        RegisterClip(res, res.clips.chops[i], paths[i]);
    }
    // Death
    RegisterClip(res, res.clips.death, "sound/death.wav");
    // Out of time
    RegisterClip(res, res.clips.outOfTime, "sound/out_of_time.wav");
}

void InitializeSprites(GameResources& res)
{
    // Background
    SetupSprite(res, res.sprites.background, "background", 0, 0);
    // Tree
    SetupSprite(res, res.sprites.tree, "tree", 810, 0);
    // Kunai
    for (int i = 0; i < 2; i++)
    {
        SetupSprite(res, res.sprites.kunai[i], "bee", 0, 800 + i * 200);
    }
    // Clouds
    for (int i = 0; i < 3; i++)
    {
        SetupSprite(res, res.sprites.cloud[i], "cloud", 0, 800 + i * 50);
    }
    res.sprites.cloud[0].setPosition(0, 0);
    // Branches
    for (int i = 0; i < NUM_BRANCHES; i++) {
        SetupSprite(res, res.sprites.branch[i], "branch", -2000, -2000);
        res.sprites.branch[i].setOrigin(220, 20);
    }
    // Player
    SetupSprite(res, res.sprites.player[0], "jcvd1", 720, 850);
    SetupSprite(res, res.sprites.player[1], "jcvd2", 720, 850);
    // RIP
    SetupSprite(res, res.sprites.streak, "rip", 650, 850);
    // Log
    SetupSprite(res, res.sprites.log, "log", 810, 900);
}

void InitializeFontAndText(GameResources& res)
{
    res.font.loadFromFile("fonts/KOMIKAP_.ttf");

    res.ui.messageText.setFont(res.font);
    res.ui.messageText.setString("Press Enter to start JCVD Training");
    res.ui.messageText.setFillColor(Color::White);
    
    res.ui.scoreText.setFont(res.font);
    res.ui.scoreText.setString("Score = 0");
    res.ui.scoreText.setFillColor(Color::White);

    res.ui.timeBar.setSize(Vector2f(
        res.time.timeBarStartWidth, res.time.timeBarHeight));
    res.ui.timeBar.setFillColor(Color::Red);
    res.ui.timeBar.setPosition((1920 / 2) - res.time.timeBarStartWidth / 2, 10);
}

void InitializeGameResources(GameResources& res)
{
    InitializeGameTime(res.time);
    InitializeTextures(res);
    InitializeSprites(res);
    InitializeFontAndText(res);
}

void UpdateText(GameResources& res)
{
    FloatRect textRect = res.ui.messageText.getLocalBounds();
    res.ui.messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    res.ui.messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    res.ui.scoreText.setPosition(20, 20);
}

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "JCVD Training!!", Style::Fullscreen);

    GameResources res;
    InitializeGameResources(res);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased && !paused)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Enter ||
                    event.key.scancode == sf::Keyboard::Scan::Left ||
                    event.key.scancode == sf::Keyboard::Scan::Right)
                {
                    res.gameplay.input.acceptInput = true;
                }

                // hide the hit image
                res.sprites.hit->setPosition(2000,
                    res.sprites.hit->getPosition().y);
                
                // hide the hit image
                res.sprites.hit->setPosition(2000,
                    res.sprites.hit->getPosition().y);
            }
        }

        UpdateText(res);
       
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
                handleChopRight(
                    playerSide,
                    score,
                    timeRemaining,
                    acceptInput,
                    spritePlayer2,
                    spriteHit,
                    spriteLog,
                    logActive,
                    logSpeedX,
                    chop,
                    chop2,
                    chop3,
                    chop4
                );
            }

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                handleChopLeft(
                    playerSide,
                    score,
                    timeRemaining,
                    acceptInput,
                    spritePlayer,
                    spriteHit2,
                    spriteLog,
                    logActive,
                    logSpeedX,
                    chop,
                    chop2,
                    chop3,
                    chop4
                );
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
