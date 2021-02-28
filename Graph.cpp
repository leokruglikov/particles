#include "Graph.h"

    Graph::Graph(float a, float b, float c, float d, float e, float f) {
        k = sf::Vector2f(a, b);
        o = sf::Vector2f(c, d);
        n = sf::Vector2f(e, f);
        thickness = 2.f;
        N_max_Y = o.y - k.y;
        N_max_X = n.x - o.x;
    }


    void Graph::create_graph(sf::RenderWindow& wind) {
        sf::RectangleShape rect1;
        sf::RectangleShape rect2;

        rect1.setSize(sf::Vector2f(thickness, N_max_Y));
        rect1.setPosition(k);

        rect2.setSize(sf::Vector2f(N_max_X, thickness));
        rect2.setPosition(sf::Vector2f(o));

        wind.draw(rect1);
        wind.draw(rect2);

    }
    float Graph::get_N_max_x() {
        return N_max_X;
    }

    void Graph::histogramm(std::vector<std::vector<Ball>>& classed_v, sf::RenderWindow& wind) {


        std::vector<sf::RectangleShape> rect(classed_v.size());
        for (int i = 0; i < (classed_v.size()); i++) {
            rect[i].setSize(sf::Vector2f(7, 4 * classed_v[i].size()));
            rect[i].setPosition(o.x + (i * 7), o.y - rect[i].getSize().y);
            rect[i].setFillColor(sf::Color::Green);
            wind.draw(rect[i]);
        }

    }
