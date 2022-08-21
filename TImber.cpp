#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    //Creating video mode object(rezolution)
    VideoMode vm(1920, 1890);
    //Creating open window for game RenderWindow
    RenderWindow window(vm, "Timber!!", Style::Fullscreen);

    /*
        ******** Drawing scene *********
    */
    //Creating texture who holds graphics in GPU
    Texture textureBackground;

    //Loading graphics in texture
    textureBackground.loadFromFile("graphics/background.png");

    //Creating sprite
    Sprite spriteBackground;

    //Connecting texture with sprite
    spriteBackground.setTexture(textureBackground);

    //Setting background postion so he could cover whole background
    spriteBackground.setPosition(0, 0);


    window.draw(spriteBackground);
    //Showing everyhting we drawed 
    window.display();

    //Telling window to close with Esc button
    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
    }
    /*
        Drawing scene
    */
    //clearing everything from previous scene
    window.clear();

    
    return 0;


}