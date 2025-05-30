#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include "frame.h"

int main()
{
    int number_of_particles = 300;

    auto window = sf::RenderWindow(sf::VideoMode({500, 500}), "Fluid Simulator");
    window.setFramerateLimit(144);
    double x = window.getSize().x;
    double y = window.getSize().y;
    
    std::vector<sf::CircleShape> all_circles;
    std::vector<Particle> all_particles;
    std::vector<Particle*> neighbors;
    
    for (int i=0; i < number_of_particles; ++i) {
        Particle p;
        double x = rand()%window.getSize().x;
        double y = rand()%window.getSize().y;
        p.position = Vector{x, -y};

        x = rand()%100;
        y = rand()%100;
        // p.velocity = Vector{x, y};

        double mass = rand()%5 + 10;
        p.mass = mass;

        double radius = rand()%10+1;
        p.radius = radius;

        all_particles.push_back(p);

        sf::CircleShape circle(p.radius);
        // circle.setFillColor(sf::Color::White);
        circle.setFillColor({255, 255, 255, 255/(p.mass-9)});
        circle.setPosition({p.position.x-p.radius, p.position.y-p.radius});
        
        all_circles.push_back(circle);
    }

    sf::Font font("D:\\mayank\\Simulators\\Tinos-Regular.ttf"); 
    sf::Text text(font); 
    text.setString("Hello world");
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Red);

    sf::Text total_energy(font); 
    total_energy.setString("Hello world");
    total_energy.setCharacterSize(24); 
    total_energy.setFillColor(sf::Color::Red);
    total_energy.setPosition({window.getSize().x-250, 20});
    
    int frame_count = 0;
    sf::Clock clock;
    float lastTime = 0;

    double TE = 0;
    double PE = 0;
    double KE = 0;
    
    Frame quad_tree;

    quad_tree.boundary = Rectangle{Vector{x/2.00, y/2.00}, x/2.00, y/2.00};
    quad_tree.number_of_particles = 0;
    quad_tree.tr = {x, 0};
    quad_tree.bl = {0, y};

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        for (size_t i = 0; i < number_of_particles; ++i){
            insert_point(&all_particles[i], quad_tree);
        }

        for (size_t i = 0; i < number_of_particles; ++i){
            Rectangle search_area = Rectangle{Vector{all_particles[i].position.x, -all_particles[i].position.y}, 
            all_particles[i].radius + 10, 
            all_particles[i].radius + 10};
            
            query(search_area, quad_tree, neighbors);
            // show_details(quad_tree);
            // std::cout<<neighbors.size()<<std::endl;

            for (size_t j = 0; j < neighbors.size(); j++){
                if (&all_particles[i] != neighbors[j]){    
                    detect_collision(&all_particles[i], neighbors[j], quad_tree.dt);
                }
            }
            neighbors = std::vector<Particle*>();
            
        }
        
        check_boundaries(quad_tree, quad_tree.tr, quad_tree.bl);

        for (size_t i = 0; i < number_of_particles; ++i){
            update_particle(&all_particles[i], quad_tree.dt);
        }
        KE = 0;
        PE = 0;
        for (size_t i = 0; i < number_of_particles; ++i){
            PE += all_particles[i].mass * (all_particles[i].position.y+1000) * 9.81/1000.00;
            KE += 0.5 * all_particles[i].mass * pow(magnitude(all_particles[i].velocity), 2)/1000.00;
        }
        
        window.clear(sf::Color::Black); 
        for (int i = 0; i < number_of_particles; ++i) {
            all_circles[i].setPosition({all_particles[i].position.x-all_particles[i].radius, -all_particles[i].position.y-all_particles[i].radius});
            window.draw(all_circles[i]);
        }
        sf::Time ElapsedTime = clock.restart();
        int time = 1/ElapsedTime.asSeconds();
        if (frame_count == 50) {
            text.setString(std::to_string(time));
            frame_count = 0;
            TE = PE + KE;
            total_energy.setString(std::to_string(TE));
        }
        frame_count++;
        window.draw(text);
        window.draw(total_energy);
        // draw_quad_tree(window, quad_tree);
        clear_quad_tree(quad_tree);
        window.display();
        // break;
    }
    return 0;
}
