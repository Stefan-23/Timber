
#include "SFML/Graphics.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color(204, 77, 5)); // Color circle
    shape.setPosition(200, 200); // Center circle

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(18, 33, 43)); // Color background
        window.draw(shape);
        window.display();
    }

    return 0;
}