#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Ball.h"
#include "Box.h"
#include "Graph.h"
#define PI 3.1416


bool check_collision_right(Ball& arr, Box& box);
bool check_collision_left(Ball& arr, Box& box);
bool check_collision_down(Ball& arr, Box& box);
bool check_collision_up(Ball& arr, Box& box);
void set_start_position(std::vector<Ball>& arr, Box& box);
void create_vector_of_balls(std::vector<Ball>& arr, sf::RenderWindow& wind);
void increment_position(std::vector<Ball>& arr, Box& box);
void set_start_velocity(std::vector<Ball>& arr, int& max);
float calculate_total_kinetic_energy(std::vector<Ball>& ball);
void classify_velocities(std::vector<std::vector<Ball>>& class_velocities, std::vector<Ball>& balls, float& max_vel);
float calculate_mean_square(std::vector<Ball>& b);
void create_text(sf::RenderWindow& wind, std::string mystring, float scale, float position_x, float position_y, sf::Color col);

int main() {
    sf::RenderWindow main_wind;
    main_wind.create(sf::VideoMode(1200, 800), "Hi");



    int const NUMBER_OF_BALLS = 300;

    Box box_one(10, 10, 310, 10, 10, 310 , 310, 310);
    Box box_two(410 +110, 10, 710+110, 10, 410+110, 310 , 710+110, 310);
    Graph graph(box_one.get_left_wall_x_position(), box_one.get_down_wall_y_position() + 50, box_one.get_left_wall_x_position(), box_one.get_down_wall_y_position() + 350, box_one.get_right_wall_x_position() - 100, box_one.get_down_wall_y_position() + 350);
    Graph graph2(box_two.get_left_wall_x_position(), box_two.get_down_wall_y_position() + 50, box_two.get_left_wall_x_position(), box_two.get_down_wall_y_position() + 350, box_two.get_right_wall_x_position() - 100, box_two.get_down_wall_y_position() + 350);
    std::vector<Ball> balls(NUMBER_OF_BALLS);
    std::vector<Ball> balls2(NUMBER_OF_BALLS);
    set_start_position(balls, box_one);
    set_start_position(balls2, box_two);
    int max1 = 2000;
    int max2 = 3000;
    set_start_velocity(balls, max1);
    set_start_velocity(balls2, max2);
    balls[3].set_color(sf::Color::Red);

    //find the maximal velocity, in order to scale the graph
    std::vector<Ball>::iterator res;
    res = std::max_element(balls.begin(), balls.end(), [](Ball& ball1, Ball& ball2) {
        return ball1.get_module_velocity() < ball2.get_module_velocity();
        });
    float max_velocity = res->get_module_velocity();

    std::vector<Ball>::iterator res2;
    res2 = std::max_element(balls2.begin(), balls2.end(), [](Ball& ball1, Ball& ball2) {
        return ball1.get_module_velocity() < ball2.get_module_velocity();
        });
    float max_velocity2 = res2->get_module_velocity();
    //create a vector of vector, ~13 lines and arbitrary coulumns
    std::cout << max_velocity << "\t" << max_velocity2 << "\n";
    float result_scale = max_velocity + max_velocity2;


    std::cout << "Max initial velocity is : " << result_scale << std::endl;
    //sf::Clock time_of_simulation;


    while (main_wind.isOpen()) {
        sf::Event my_event;

        while (main_wind.pollEvent(my_event)) {

            if (my_event.type == sf::Event::EventType::Closed) {
                main_wind.close();
                break;
            }

        }

        std::vector<std::vector<Ball>> velocities_in_graph(70);
        std::vector<std::vector<Ball>> velocities_in_graph2(70);
        graph.create_graph(main_wind);
        graph2.create_graph(main_wind);
        classify_velocities(velocities_in_graph, balls, result_scale);
        classify_velocities(velocities_in_graph2, balls2, result_scale);
        graph.histogramm(velocities_in_graph, main_wind);
        graph2.histogramm(velocities_in_graph2, main_wind);
        create_vector_of_balls(balls, main_wind);
        create_vector_of_balls(balls2, main_wind);
        main_wind.display();
        main_wind.clear();
        increment_position(balls, box_one);
        increment_position(balls2, box_two);
        box_one.create_walls(main_wind);
        box_two.create_walls(main_wind);

    }




    return 0;
}



bool check_collision_right(Ball& arr, Box& box) {
    bool temp = false;
    if (arr.get_velocity_x() > 0.f && (arr.get_position().x + arr.get_radius()) >= box.get_right_wall_x_position()) {
        temp = true;
    }
    return temp;
}
bool check_collision_left(Ball& arr, Box& box) {
    bool temp = false;
    if (arr.get_velocity_x() < 0.f && (arr.get_position().x - arr.get_radius()) < box.get_left_wall_x_position()) {
        temp = true;
    }
    return temp;
}
bool check_collision_down(Ball& arr, Box& box) {
    bool temp = false;
    if (arr.get_velocity_y() > 0.f && (arr.get_position().y + arr.get_radius()) > box.get_down_wall_y_position()) {
        temp = true;
    }
    return temp;
}
bool check_collision_up(Ball& arr, Box& box) {
    bool temp = false;
    if (arr.get_velocity_y() < 0.f && (arr.get_position().y - arr.get_radius()) < box.get_up_wall_Y_position()) {
        temp = true;
    }
    return temp;
}

void set_start_position(std::vector<Ball>& arr, Box& box) {
    srand((unsigned)time(0));
    for (int i = 0; i < arr.size(); i++) {
        arr[i].setposition(rand() % (static_cast<int>(box.get_right_wall_x_position()) - static_cast<int>(box.get_left_wall_x_position()) + 1) + static_cast<int>(box.get_left_wall_x_position()), rand() % (static_cast<int>(box.get_down_wall_y_position()) - static_cast<int>(box.get_up_wall_Y_position()) + 1) + static_cast<int>(box.get_up_wall_Y_position()));

    }

}

void create_vector_of_balls(std::vector<Ball>& arr, sf::RenderWindow& wind) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i].create_ball(wind);
    }
}

void increment_position(std::vector<Ball>& arr, Box& box) {
    for (int i = 0; i < arr.size(); i++) {
        if (check_collision_right(arr[i], box) == false) {
            sf::Vector2f temp(arr[i].get_position().x + arr[i].get_velocity_x(), arr[i].get_position().y + arr[i].get_velocity_y());
            arr[i].setposition(temp.x, temp.y);
        }
        if (check_collision_right(arr[i], box) == true) {
            arr[i].set_velocity_x((-1) * arr[i].get_velocity_x());

        }
        if (check_collision_left(arr[i], box) == false) {
            sf::Vector2f temp(arr[i].get_position().x + arr[i].get_velocity_x(), arr[i].get_position().y + arr[i].get_velocity_y());
            arr[i].setposition(temp.x, temp.y);
        }
        if (check_collision_left(arr[i], box) == true) {
            arr[i].set_velocity_x((-1) * arr[i].get_velocity_x());

        }
        if (check_collision_up(arr[i], box) == false) {
            sf::Vector2f temp(arr[i].get_position().x + arr[i].get_velocity_x(), arr[i].get_position().y + arr[i].get_velocity_y());
            arr[i].setposition(temp.x, temp.y);
        }
        if (check_collision_up(arr[i], box) == true) {
            arr[i].set_velocity_y((-1) * arr[i].get_velocity_y());

        }
        if (check_collision_down(arr[i], box) == false) {
            sf::Vector2f temp(arr[i].get_position().x + arr[i].get_velocity_x(), arr[i].get_position().y + arr[i].get_velocity_y());
            arr[i].setposition(temp.x, temp.y);
        }
        if (check_collision_down(arr[i], box) == true) {
            arr[i].set_velocity_y((-1) * arr[i].get_velocity_y());

        }
        for (int k = 0; k < arr.size() && k != i; k++) {
            float xik = arr[k].get_position().x - arr[i].get_position().x;
            float yik = arr[k].get_position().y - arr[i].get_position().y;
            float rik = sqrt(xik * xik + yik * yik);
            if (rik < 2 * arr[k].get_radius()) {
                float xiku = xik / rik;
                float yiku = yik / rik;
                float dv = xiku * (arr[k].get_velocity_x() - arr[i].get_velocity_x()) + yiku * (arr[k].get_velocity_y() - arr[i].get_velocity_y());
                arr[i].set_velocity_x(arr[i].get_velocity_x() + xiku * dv);
                arr[i].set_velocity_y(arr[i].get_velocity_y() + yiku * dv);
                arr[k].set_velocity_x(arr[k].get_velocity_x() - xiku * dv);
                arr[k].set_velocity_y(arr[k].get_velocity_y() - yiku * dv);
                arr[i].setposition(arr[i].get_position().x + arr[i].get_velocity_x(), arr[i].get_position().y + arr[i].get_velocity_y());
                arr[k].setposition(arr[k].get_position().x + arr[k].get_velocity_x(), arr[k].get_position().y + arr[k].get_velocity_y());
                xik = arr[k].get_position().x - arr[i].get_position().x;
                yik = arr[k].get_position().y - arr[i].get_position().y;
                rik = sqrt(xik * xik + yik * yik);
                if (rik < 2 * arr[k].get_radius()) {
                    arr[k].setposition(arr[k].get_position().x + (2 * arr[k].get_radius() - rik) * xiku, arr[k].get_position().y + (2 * arr[k].get_radius() - rik) * yiku);
                    arr[i].setposition(arr[i].get_position().x - (2 * arr[i].get_radius() - rik) * xiku, arr[i].get_position().y - (2 * arr[i].get_radius() - rik) * yiku);
                }
            }

        }


    }
}

void set_start_velocity(std::vector<Ball>& arr, int& max) {

    int num = max;
    float rand_x_pos = 0;
    float rand_y_pos = 0;
    float rand_x_neg = 0;
    float rand_y_neg = 0;
    float temp1 = 0;
    float temp2 = 0;
    float temp3 = 0;
    float temp4 = 0;
    float lol = 0.0;
    srand(time(NULL));
    for (int i = 0; i < arr.size(); i++) {
        temp1 = rand() % num;
        temp2 = rand() % num;
        temp3 = rand() % num;
        temp4 = rand() % num;
        lol = (temp1 / 1000);
        rand_x_pos = temp1 / 1000;
        rand_x_neg = temp2 / 1000;
        rand_y_pos = temp3 / 1000;
        rand_y_neg = temp4 / 1000;
        if (static_cast<int>(temp1) % 2 == 0) {
            arr[i].set_velocity_x(rand_x_pos);
            arr[i].set_velocity_y(rand_y_pos);
        }
        else {
            arr[i].set_velocity_x((-1) * rand_x_neg);
            arr[i].set_velocity_y((-1) * rand_y_neg);
        }


    }
}

float calculate_total_kinetic_energy(std::vector<Ball>& ball) {
    float temporary = 0;
    for (int i = 0; i < ball.size(); i++) {
        temporary = temporary + (ball[i].get_module_velocity() * ball[i].get_module_velocity()) / 2;
    }
    return temporary;
}

void classify_velocities(std::vector<std::vector<Ball>>& class_velocities, std::vector<Ball>& balls, float& max_vel) {
    float step = max_vel / class_velocities.size();

    for (int i = 0; i < class_velocities.size(); i++) {
        std::copy_if(balls.begin(), balls.end(), std::back_inserter(class_velocities[i]), [&step, &i](Ball& b) {
            return b.get_module_velocity() > i * step && b.get_module_velocity() < step * (i + 1);
            });

    }

}
float calculate_mean_square(std::vector<Ball>& b) {
    float temp = 0;
    for (int i = 0; i < b.size(); i++) {
        temp = temp + pow(b[i].get_module_velocity(), 2);
    }
    return temp / b.size();

}
void create_text(sf::RenderWindow& wind, std::string mystring, float scale, float position_x, float position_y, sf::Color col) {
    sf::Text temporary_text;
    sf::Font font;
    font.loadFromFile("C://Users//leokr//Desktop//Bounding_box//Bounding");
    temporary_text.setFont(font);
    temporary_text.setString(mystring);
    float w, h;
    w = temporary_text.getLocalBounds().width;
    h = temporary_text.getLocalBounds().height;
    temporary_text.setScale(scale, scale);
    temporary_text.setOutlineColor(sf::Color::Cyan);
    temporary_text.setOrigin(w / 2, h / 2);
    temporary_text.setPosition(position_x, position_y);
    temporary_text.setFillColor(col);
    wind.draw(temporary_text);

}
float calculate_mean_kinetic_energy(std::vector<Ball>& ball) {
    float temp = 0;
    for (int i = 0; i < ball.size(); i++) {
        temp = temp + (ball[i].get_module_velocity() * ball[i].get_module_velocity()) / 2;
    }
    return temp / ball.size();
}


