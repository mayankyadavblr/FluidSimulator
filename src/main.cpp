#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include "frame.h"

int temp()
{
    int number_of_particles = 100;

    auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Fluid Simulator");
    window.setFramerateLimit(60);
    double x = window.getSize().x;
    double y = window.getSize().y;
    
    std::vector<sf::CircleShape> all_circles;
    std::vector<Particle> all_particles;
    std::vector<Particle*> neighbors;
    Rectangle search_area = Rectangle{Vector{250, 250}, 250, 250};
    
    for (int i=0; i < number_of_particles; ++i) {
        Particle p;
        double x = rand()%window.getSize().x;
        double y = rand()%window.getSize().y;
        p.position = Vector{x, -y};

        x = rand()%100;
        y = rand()%100;
        p.velocity = Vector{x, y};

        double mass = rand()%5 + 10;
        p.mass = mass;

        double radius = rand()%10+1;
        p.radius = radius;

        all_particles.push_back(p);

        sf::CircleShape circle(p.radius);
        // circle.setFillColor(sf::Color::White);
        circle.setFillColor({255, 255, 255, 255/(mass-9)});
        circle.setPosition({p.position.x-p.radius, p.position.y-p.radius});
        
        all_circles.push_back(circle);
    }

    sf::Font font("D:\\mayank\\Simulators\\Tinos-Regular.ttf"); 
    sf::Text text(font); 
    text.setString("Hello world");
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Red);
    
    int frame_count = 0;
    sf::Clock clock;
    float lastTime = 0;
    
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
        // show_details(quad_tree);
        // std::cout<<"inserting into quad tree"<<std::endl;
        // Insert points into fresh Quad Tree
        for (size_t i = 0; i < number_of_particles; ++i){
            insert_point(&all_particles[i], quad_tree);
        }
        // show_details(quad_tree);
        query(search_area, quad_tree, neighbors);
        for (int i=0; i<neighbors.size(); i++){
            std::cout<<neighbors[i]->position.x<<", "<<neighbors[i]->position.y<<std::endl;
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
        }
        frame_count++;
        window.draw(text);
        // draw_test(window);
        draw_quad_tree(window, quad_tree);
        clear_quad_tree(quad_tree);
        window.display();
        // break;
        
    }
    return 0;
}