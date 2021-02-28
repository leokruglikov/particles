#include"Ball.h"

Ball::Ball() {
    radius = 1.5f;
    point_count = 7.f;
    ball.setRadius(radius);
    ball.setPointCount(point_count);
    ball.setOrigin(radius / 2, radius / 2);
    vel_x = 1.f;
    vel_y = 0.1f;
}
sf::Vector2f Ball::get_position() {
    return sf::Vector2f(pos_x, pos_y);
}
void Ball::setposition(float x, float y) {
    pos_x = x;
    pos_y = y;
}
void Ball::create_ball(sf::RenderWindow& wind) {
    ball.setPosition(sf::Vector2f(pos_x, pos_y));
    wind.draw(ball);
}
float Ball::get_velocity_x() {
    return vel_x;
}

float Ball::get_velocity_y() {
    return vel_y;
}
void Ball::set_velocity_x(float vel) {
    vel_x = vel;
}
void Ball::set_velocity_y(float vel) {
    vel_y = vel;
}
float Ball::get_module_velocity() {
    return sqrt(pow(vel_x, 2) + pow(vel_y, 2));
};
float Ball::get_velocity_angle() {
    return atan(vel_y / vel_x);
}
float Ball::get_radius() {
    return radius;
}
void Ball::set_color(sf::Color col) {
    ball.setFillColor(col);
}