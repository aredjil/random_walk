#include <SFML/Graphics.hpp>
#include <iostream>

/*
This code contains a simple simulation of a random walker using SFML 
*/

int main()
{
    const int width{500};
    const int height{width};
    // We start first by creating a window 
    sf::RenderWindow window(sf::VideoMode(width, height), "2 D random Walk", sf::Style::Default);

    // Creating the random walker as a circle in the center of the screen 
    sf::CircleShape random_walker(5.0f);
    // Now we start the scene loop
    while(window.isOpen())

    {   sf::Event event; 
        // Closing the window logic 
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            
            default:
                break;
            }
        }
        window.draw()


    }
    return 0;
}