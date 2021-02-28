#pragma once
#include <SFML/Graphics.hpp>
class Ball {
public:
    Ball();
    sf::Vector2f get_position();

    void setposition(float x, float y);
    void create_ball(sf::RenderWindow& wind);
    float get_velocity_x();

    float get_velocity_y();
    void set_velocity_x(float vel);
    void set_velocity_y(float vel);
    float get_module_velocity();
    float get_velocity_angle();
    float get_radius();
    void set_color(sf::Color col);

private:
    float module_velocity;
    float pos_x;
    float pos_y;
    float radius;
    float point_count;
    float vel_x;
    float vel_y;
    sf::CircleShape ball;


};