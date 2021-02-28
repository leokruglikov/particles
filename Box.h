#pragma once
#include<SFML/Graphics.hpp>

class Box {
public:
    Box();
    Box(float A, float B, float C, float D, float E, float F, float G, float H);
    void create_walls(sf::RenderWindow& wind);

    float get_up_wall_Y_position();
    float get_down_wall_y_position();
    float get_left_wall_x_position();
    float get_right_wall_x_position();

protected:
    sf::Vector2f a;
    sf::Vector2f b;
    sf::Vector2f c;
    sf::Vector2f d;
    float thickness;


};
