#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    //Creating video mode object(rezolution)
    VideoMode vm(1920, 1890);
    //Creating open window for game RenderWindow
    RenderWindow window(vm, "Timber!!", Style::Fullscreen);


    /*
        Background
        ********************************************************
    */

    //Creating texture which holds graphics in GPU
    Texture textureBackground;

    //Loading graphics in texture
    textureBackground.loadFromFile("graphics/background.png");

    //Creating sprite
    Sprite spriteBackground;

    //Connecting texture with sprite
    spriteBackground.setTexture(textureBackground);

    //Setting background postion so he could cover whole background
    spriteBackground.setPosition(0, 0);

    /*
        Background-END
       ********************************************************
   */
  


   /*
    Creating Tree
       ********************************************************
   */

    Texture textureTree;

    textureTree.loadFromFile("graphics/tree.png");

    Sprite spriteTree;

    spriteTree.setTexture(textureTree);

    spriteTree.setPosition(810, 0);

    /*
       Tree END
       ********************************************************
   */



   /*
        Creating BEE 
       ********************************************************
   */
    
    Texture textureBee;

    textureBee.loadFromFile("graphics/bee.png");

    Sprite spriteBee;

    spriteBee.setTexture(textureBee);

    spriteBee.setPosition(800, 800);

    //Is Bee moving
    bool beeActive = false;
    //Bee moving speed
    float beeSpeed = 0.0f;

  


    /*
        BEE end
       ********************************************************
   */



   /*
       Creating CLOUD
      ********************************************************
  */

    Texture textureCloud;

    textureCloud.loadFromFile("graphics/cloud.png");

    //3 new sprite with same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    //Position

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    //Is it active on window
    bool isCloudActive1 = false;
    bool isCloudActive2 = false;
    bool isCloudActive3 = false;

    //Cloud speed
    float CloudSpeed1 = 0.0f;
    float CloudSpeed2 = 0.0f;
    float CloudSpeed3 = 0.0f;

    /*
         CLOUD END
         ********************************************************
     */




     // Variables to control time itself
    Clock clock;

    while (window.isOpen())
    {

        /*
        ****************************************
        Handle the players input
        ****************************************
        */

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update the scene
        ****************************************
        */
        // Measure time
        Time dt = clock.restart();

        // Setup the bee
        if (!beeActive)
        {

            // How fast is the bee
            srand((int)time(0) * 10); //Time is 0 because that is current time on PC
            beeSpeed = (rand() % 200) + 200;

            // How high is the bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;

        }
        else
            // Move the bee
        {

            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),spriteBee.getPosition().y);

            // Has the bee reached the right hand edge of the screen?
            if (spriteBee.getPosition().x < -100)
            {
                // Set it up ready to be a whole new cloud next frame
                beeActive = false;
            }
        }
        /*
         Drawing scene
         ********************************************************
        */
        //clear everything from previous scene
        window.clear();

     //Background
        window.draw(spriteBackground);

        //3 clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        //Tree
        window.draw(spriteTree);

        //Bee
        window.draw(spriteBee);

        window.display();

        /*
             Drawing scene end
             ********************************************************
         */
    }

    
    return 0;


}