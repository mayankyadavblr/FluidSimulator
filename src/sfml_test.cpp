#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include "frame.h"

int main()
{
    int number_of_particles = 250;

    auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "CMake SFML Project");
    window.setFramerateLimit(144);
    double x = window.getSize().x;
    double y = window.getSize().y;
    
    std::vector<sf::CircleShape> all_circles;
    
    Frame frame;
    frame.dt = 1.00/60.00;
    frame.number_of_particles = number_of_particles;
    frame.tr = {x, 0};
    frame.bl = {0, y};
    
    for (int i=0; i < number_of_particles; ++i) {
        Particle p;
        double x = 1000 - rand()%window.getSize().x;
        double y = 1000 - rand()%window.getSize().y;
        p.position = Vector{x, -y};
        x = rand()%20;
        y = rand()%20;
        p.velocity = Vector{x, y};

        frame.all_particles.push_back(p);

        sf::CircleShape circle(p.radius);
        circle.setFillColor(sf::Color::White);
        circle.setPosition({p.position.x, p.position.y});
        
        all_circles.push_back(circle);

        // display_details(p);

    }
    sf::Font font("D:\\mayank\\Simulators\\Tinos-Regular.ttf"); 
    sf::Text text(font); 
    text.setString("Hello world");
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Red);
    
    int frame_count = 0;
    sf::Clock clock;
    float lastTime = 0;
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        for (size_t i = 0; i < frame.all_particles.size() - 1; ++i) {
            for (size_t j = i + 1; j < frame.all_particles.size(); ++j) {
                detect_collision(frame.all_particles[i], frame.all_particles[j]);
            }
        }

        check_boundaries(frame);

        for (size_t i = 0; i < frame.all_particles.size(); ++i){
            update_particle(frame.all_particles[i], frame.dt);
        }

        window.clear(sf::Color::Black); 
        for (int i = 0; i < number_of_particles; ++i) {
            all_circles[i].setPosition({frame.all_particles[i].position.x, -frame.all_particles[i].position.y});
            window.draw(all_circles[i]);
        }
        sf::Time ElapsedTime = clock.restart();
        int time = 1/ElapsedTime.asSeconds();
        if (frame_count == 50) {
            text.setString(std::to_string(time));
            frame_count = 0;
        }
        frame_count++;
        window.draw(text);
        window.display();
        
    }
    return 0;
}