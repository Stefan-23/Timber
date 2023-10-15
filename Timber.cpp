//Inclucde C++ Libraries
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>

using namespace sf;
int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!", Style::Fullscreen);
    //Clock
    Clock clock;
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
    while (window.isOpen())
    {
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
            paused = false;
        }
        /*
            Updating scene
        */
        if (!paused)
        {
            //Time
            Time dt = clock.restart();

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


        }
        // Drawing scene
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteBee1);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(scoreText);
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