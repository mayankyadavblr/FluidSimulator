#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    // Create a circle
    sf::CircleShape circle(100.f); // Radius of 100 pixels
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition({860u, 490u}); // Center it roughly in 1920x1080

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Red); // Background color
        window.draw(circle);          // Draw the circle
        window.display();             // Display the frame
    }
}
