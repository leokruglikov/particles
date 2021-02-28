#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
class Graph {
public:

    Graph(float a, float b, float c, float d, float e, float f);


    void create_graph(sf::RenderWindow& wind);
    float get_N_max_x();

    void histogramm(std::vector<std::vector<Ball>>& classed_v, sf::RenderWindow& wind);

private:
    sf::Vector2f k;
    sf::Vector2f o;
    sf::Vector2f n;
    float thickness;
    float N_max_Y;
    float N_max_X;
    sf::RectangleShape rectangles;
};