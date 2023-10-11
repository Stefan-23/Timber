//Inclucde C++ Libraries
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


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

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

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
    while (window.isOpen())
    {
       
        /*
        
            Player input
        
        */
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

            // Cloud movement

            if (!cloud1Active)
            {
                //cloud speed
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                //cloud height
                srand((int)time(0) * 10);
                float height = (rand() % 150);
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
                cloud2Speed = (rand() % 200);
                //cloud height
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
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
                cloud3Speed = (rand() % 200);
                //cloud height
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
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
            }


        }
        // Drawing scene


        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        //Removing everything from previous scene
        

        //Showing everything we created
        window.display();

    }

    return 0;
}