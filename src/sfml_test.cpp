#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include "frame.h"

int main()
{
    int number_of_particles = 100;

    auto window = sf::RenderWindow(sf::VideoMode({500, 500}), "Fluid Simulator");
    window.setFramerateLimit(60);
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
        double x = rand()%window.getSize().x;
        double y = rand()%window.getSize().y;
        p.position = Vector{x, -y};
        x = rand()%100;
        y = rand()%100;
        p.velocity = Vector{x, y};
        double mass = rand()%5 + 10;
        // p.mass = 2;
        p.mass = mass;
        double radius = rand()%10+1;
        p.radius = radius;
        // p.radius = 10;

        frame.all_particles.push_back(p);

        sf::CircleShape circle(p.radius);
        // circle.setFillColor(sf::Color::White);
        circle.setFillColor({255, 255, 255, 255/(mass-9)});
        circle.setPosition({p.position.x-p.radius, p.position.y-p.radius});
        
        all_circles.push_back(circle);

        // display_details(p);

    }

    // Particle test;
    // test.position = Vector{250, 250};
    // test.radius = 8;
    // test.mass = 32;
    // frame.all_particles.push_back(test);
    // frame.number_of_particles += 1;
    // sf::CircleShape circle_test(test.radius);
    // circle_test.setFillColor(sf::Color::Red);
    // circle_test.setPosition({test.position.x, test.position.y});
    // all_circles.push_back(circle_test);

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
        for (size_t i = 0; i < frame.number_of_particles - 1; ++i) {
            for (size_t j = i + 1; j < frame.number_of_particles; ++j) {
                detect_collision(frame.all_particles[i], frame.all_particles[j], frame.dt);
            }
        }

        check_boundaries(frame);

        for (size_t i = 0; i < frame.number_of_particles; ++i){
            update_particle(frame.all_particles[i], frame.dt);
        }

        window.clear(sf::Color::Black); 
         for (int i = 0; i < frame.number_of_particles; ++i) {
            all_circles[i].setPosition({frame.all_particles[i].position.x-frame.all_particles[i].radius, -frame.all_particles[i].position.y-frame.all_particles[i].radius});
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