#include <SFML/Graphics.hpp>
#include "frame.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    
    Frame frame;
    frame.dt = 1.00/60.00;
    frame.number_of_particles = 1;
    
    Particle p1;
    p1.position = Vector{0, 5};
    p1.velocity = Vector{120, 0};
    
    Particle p2;
    p2.position = Vector{290, 5};
    p2.velocity = Vector{-15, 0};
    
    frame.all_particles.push_back(p1);
    frame.all_particles.push_back(p2);
    
    sf::CircleShape circle1(p1.radius); 
    circle1.setFillColor(sf::Color::White);
    circle1.setPosition({p1.position.x, p1.position.y}); 
    
    sf::CircleShape circle2(p2.radius); 
    circle2.setFillColor(sf::Color::White);
    circle2.setPosition({p2.position.x, p2.position.y}); 
    
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
        for (size_t i = 0; i < frame.all_particles.size(); ++i){
            update_particle(frame.all_particles[i], frame.dt);
        }

        circle1.setPosition({frame.all_particles[0].position.x, -frame.all_particles[0].position.y});
        circle2.setPosition({frame.all_particles[1].position.x, -frame.all_particles[1].position.y});
        window.clear(sf::Color::Black); 
        window.draw(circle1);
        window.draw(circle2);
        window.display();
    }
    return 0;
}