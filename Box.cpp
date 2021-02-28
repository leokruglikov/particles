#include "Box.h"
Box::Box() {

}
Box::Box(float A, float B, float C, float D, float E, float F, float G, float H) {
    a = sf::Vector2f(A, B);
    b = sf::Vector2f(C, D);
    c = sf::Vector2f(E, F);
    d = sf::Vector2f(G, H);
    thickness = 5.f;
}
void Box::create_walls(sf::RenderWindow& wind)
{
    sf::RectangleShape left_r;
    sf::RectangleShape up_r;
    sf::RectangleShape right_r;
    sf::RectangleShape down_r;
    left_r.setSize(sf::Vector2f(thickness, c.y - a.y));
    right_r.setSize(sf::Vector2f(thickness, d.y - b.y));
    up_r.setSize(sf::Vector2f(b.x - a.x, thickness));
    down_r.setSize(sf::Vector2f(d.x - c.x, thickness));

    left_r.setPosition(a.x, a.y);
    right_r.setPosition(b.x, b.y);
    up_r.setPosition(a.x, a.y);
    down_r.setPosition(c.x, c.y);

    left_r.setFillColor(sf::Color::Red);
    right_r.setFillColor(sf::Color::Red);
    up_r.setFillColor(sf::Color::Red);
    down_r.setFillColor(sf::Color::Red);

    wind.draw(left_r);
    wind.draw(up_r);
    wind.draw(right_r);
    wind.draw(down_r);
}

float Box::get_up_wall_Y_position() {
    return a.y;
}
float Box::get_down_wall_y_position() {
    return c.y;
}
float Box::get_left_wall_x_position() {
    return a.x;
}
float Box::get_right_wall_x_position() {
    return b.x;
}
