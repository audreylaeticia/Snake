#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{
private:
    std::vector<sf::Vector2i> body;
    int direction;
    

public:
    Snake();

    void setDirection(int dir);
    void move();
    void draw(sf::RenderWindow& window);
};
