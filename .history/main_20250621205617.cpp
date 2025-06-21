#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include<string>
#include<vector>
/*
This code contains a simple simulation of a random walker using SFML
*/

// random number generator
std::random_device dv;
std::mt19937 gen(dv());

inline int get_direction()
{
    std::uniform_int_distribution<int> dist(0, 3);
    int next = dist(gen);
    return next;
}
int main()
{
    const int width{500};
    const int height{width};
    const float step{0.01f};
    const std::string states[] = {
        "up", 
        "right", 
        "down", 
        "left"
    };
    // We start first by creating a window
    sf::RenderWindow window(sf::VideoMode(width, height), "2 D random Walk", sf::Style::Default);
    window.setFramerateLimit(1);
    // Loading the font
    sf::Font font;
    font.loadFromFile("./arial/ARIAL.TTF");

    sf::Text text(" ", font, 30); // text, font, size
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height); // center horizontally
    text.setPosition(window.getSize().x / 2.f, 10);    // upper middle

    // Creating the random walker as a circle in the center of the screen
    sf::CircleShape random_walker(5.0f);
    random_walker.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    // random_walker.setOrigin(sf::Vector2f(width /2.0f, height/2.0f));
        std::vector<sf::Vertex> trail;



    while (window.isOpen())

    {
        sf::Event event;
        // Closing the window logic
        while (window.pollEvent(event))
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
        // Get one of the 4 states
        // 0 up, 1 right, 2 down, 3 left
        int next_state = get_direction();
        switch (next_state)
        {
        case 0:
            /* code */
            random_walker.move(sf::Vector2f(step, step));
        case 1:
            random_walker.move(sf::Vector2f(step, 0.0f));
            break;
        case 2:
            random_walker.move(sf::Vector2f(-step, -step));
            break;
        case 3:
            random_walker.move(sf::Vector2f(-step, 0.0f));
            break;
        default:
            break;
        }

        text.setString(states[next_state]);
        // Clearing the window after every frame
        window.clear(sf::Color::Black);
        // Displaying the random walker on the screen
        window.draw(random_walker);
        window.draw(text);
        window.display();
    }
    return 0;
}