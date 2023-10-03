//Inclucde C++ Libraries
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


using namespace sf;

int main()
{

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!", Style::Fullscreen);

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

    while (window.isOpen())
    {
       

        /*
        
            Player input
        
        */
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        
            Updating scene
        
        */

        /*
        
            Drawing scene

        
        */

        window.clear();
        window.draw(spriteBackground);

        //Removing everything from previous scene
        

        //Showing everything we created
        window.display();

    }

    return 0;
}