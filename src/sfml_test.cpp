#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include "frame.h"

int main()
{
    int number_of_particles = 1000;

    auto window = sf::RenderWindow(sf::VideoMode({1000u, 1000u}), "CMake SFML Project");
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
        double x = rand()%800;
        double y = rand()%800;
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
    // for(sf::CircleShape circle: all_circles) {
    //     std::cout<<circle.getPosition().x<<", "<<circle.getPosition().y<<std::endl;
    // }
    /*
    Particle p1;
    p1.position = Vector{50, -15};
    p1.velocity = Vector{20, 0};
    
    Particle p2;
    p2.position = Vector{180, -15};
    p2.velocity = Vector{-15, 0};

    Particle p3;
    p3.position = Vector{250, -250};
    p3.velocity = Vector{100, 100};
    
    frame.all_particles.push_back(p1);
    frame.all_particles.push_back(p2);
    frame.all_particles.push_back(p3);
    
    sf::CircleShape circle1(p1.radius); 
    circle1.setFillColor(sf::Color::White);
    circle1.setPosition({p1.position.x, p1.position.y}); 
    
    sf::CircleShape circle2(p2.radius); 
    circle2.setFillColor(sf::Color::White);
    circle2.setPosition({p2.position.x, p2.position.y}); 

    sf::CircleShape circle3(p3.radius); 
    circle3.setFillColor(sf::Color::White);
    circle3.setPosition({p3.position.x, p3.position.y});
    */
    // update_frame(frame);

    
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
        /*
        circle1.setPosition({frame.all_particles[0].position.x, -frame.all_particles[0].position.y});
        circle2.setPosition({frame.all_particles[1].position.x, -frame.all_particles[1].position.y});
        circle3.setPosition({frame.all_particles[2].position.x, -frame.all_particles[2].position.y});
        window.draw(circle1);
        window.draw(circle2);
        window.draw(circle3);
        */
        for (int i = 0; i < number_of_particles; ++i) {
            all_circles[i].setPosition({frame.all_particles[i].position.x, -frame.all_particles[i].position.y});
            window.draw(all_circles[i]);
        }
        window.display();
    }
    return 0;
}