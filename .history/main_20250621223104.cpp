#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>
/*
This code contains a simple simulation of a random walker using SFML
*/
const float width{500.0f}; // Width of the window
const float height{width}; // Height of the window

// random number generator
std::random_device dv; // 
std::mt19937 gen(dv());

// Check events on the window

void check_events(sf::RenderWindow &window, const sf::Event &event, const int &count);
void jump(sf::Vector2f &position, const int &step);
inline int get_direction();

int main()
{
    const float step{1.0f};
    const std::string states[] = {
        "up",
        "right",
        "down",
        "left"};
    // We start first by creating a window
    sf::RenderWindow window(sf::VideoMode(width, height), "2 D random Walk", sf::Style::Default);
    // window.setFramerateLimit(600'000);
    // Loading the font
    sf::Font font;
    font.loadFromFile("./arial/ARIAL.TTF");

    sf::Text text(" ", font, 15.0f); // text, font, size
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
    sf::Color c = sf::Color::Green; // base color
    c.a = 10;                       // 50% transparent
    sf::Texture texture;
    int count{0};
    while (window.isOpen())
    {
        sf::Event event;
        // Closing the window logic
        while (window.pollEvent(event))
        {
            check_events(window, event, count);
        }
        jump(position, step);

        sf::Vector2f last_pos = trail.back().position;
        sf::Vector2f delta = position - last_pos;

        // If wrapped (jumped), don't draw a line across screen
        if (std::abs(delta.x) > width / 2 || std::abs(delta.y) > height / 2)
        {
            // Break the trail (no line across wrap)
            trail.push_back(sf::Vertex(position, sf::Color::Transparent));
        }
        else
        {
            // Normal trail
            trail.push_back(sf::Vertex(position, c));
        }
        // Move the walker
        random_walker.setPosition(position);

        text.setString("Steps: " + std::to_string(count));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.f, bounds.height);
        text.setPosition(width / 2.f, 30);

        // Clearing the window after every frame
        window.clear(sf::Color::Black);

        for (size_t i = 1; i < trail.size(); ++i)
        {
            sf::Vector2f p1 = trail[i - 1].position;
            sf::Vector2f p2 = trail[i].position;

            sf::Vector2f delta = p2 - p1;

            // If wrapped, skip drawing the line
            if (std::abs(delta.x) > width / 2 || std::abs(delta.y) > height / 2)
                continue;

            sf::Vertex line[] = {
                sf::Vertex(p1, c),
                sf::Vertex(p2, c)};
            line->color = c;
            window.draw(line, 2, sf::Lines);
        }
        // Displaying the random walker on the screen
        window.draw(random_walker);
        window.draw(text);
        window.display();
        count++;
    }
    return 0;
}

void check_events(sf::RenderWindow &window, const sf::Event &event, const int &count)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::KeyPressed:
    {
        if (event.key.code == sf::Keyboard::S)
        {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);

            sf::Image screenshot = texture.copyToImage();
            screenshot.saveToFile("screenshot_" + std::to_string(count) + ".png");
            std::cout << "Screenshot saved!\n";
        }
        break;
    }

    default:
        break;
    }
};

inline int get_direction()
{
    std::uniform_int_distribution<int> dist(0, 3);
    int next = dist(gen);
    return next;
}

void jump(sf::Vector2f &position, const int &step)
{
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
}
