#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>
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
    const int width{800};
    const int height{width};
    const float step{1.0f};
    const std::string states[] = {
        "up",
        "right",
        "down",
        "left"};
    // We start first by creating a window
    sf::RenderWindow window(sf::VideoMode(width, height), "2 D random Walk", sf::Style::Default);
    // window.setFramerateLimit(1000);
    // Loading the font
    sf::Font font;
    font.loadFromFile("./arial/ARIAL.TTF");

    sf::Text text(" ", font, 20); // text, font, size
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height); // center horizontally
    text.setPosition(window.getSize().x / 2.f, 10);    // upper middle

    sf::Vector2f position = sf::Vector2f(width / 2.0f, height / 2.0f);
    // Creating the random walker as a circle in the center of the screen
    sf::CircleShape random_walker(5.0f);
    random_walker.setPosition(position);
    // random_walker.setOrigin(sf::Vector2f(width /2.0f, height/2.0f));
    random_walker.setFillColor(sf::Color::Red);
    std::vector<sf::Vertex> trail;
    trail.push_back(sf::Vertex(position, sf::Color::Green));
    int count{0};
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
            position.y -= step;
            break; // up
        case 1:
            position.x += step;
            break; // right
        case 2:
            position.y += step;
            break; // down
        case 3:
            position.x -= step;
            break; // left
        }

        if (position.x < 0)
            position.x += width;
        if (position.x >= width)
            position.x -= width;
        if (position.y < 0)
            position.y += height;
        if (position.y >= height)
            position.y -= height;

        sf::Vector2f last_pos = trail.back().position;
        sf::Vector2f delta = position - last_pos;

        // If wrapped (jumped), don't draw a line across screen
        if (std::abs(delta.x) > width / 2 || std::abs(delta.y) > height / 2)
        {
            trail.push_back(sf::Vertex(position, sf::Color::Transparent)); // break the line
        }

        trail.push_back(sf::Vertex(position, sf::Color::Green));

        trail.push_back(sf::Vertex(position, sf::Color::Green));

        // Move the walker
        random_walker.setPosition(position);

        text.setString(std::to_string(count));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.f, bounds.height);
        text.setPosition(width / 2.f, 10);

        // Clearing the window after every frame
        window.clear(sf::Color::Black);
        if (trail.size() > 1)
            window.draw(&trail[0], trail.size(), sf::LinesStrip);
        // Displaying the random walker on the screen
        window.draw(random_walker);
        window.draw(text);
        window.display();
        count++;
    }
    return 0;
}