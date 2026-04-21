#include <SFML/Graphics.hpp>
#include "Snake.h"

Snake::Snake()
{
    // serpent de départ (3 blocs)
    body.push_back({ 5, 5 });
    body.push_back({ 4, 5 });
    body.push_back({ 3, 5 });

    direction = 3; // RIGHT
}

void Snake::setDirection(int dir)
{
    direction = dir;
}

void Snake::move()
{
    sf::Vector2i newHead = body[0];

    if (direction == 0) // UP
        newHead.y -= 1;

    if (direction == 1) // DOWN
        newHead.y += 1;

    if (direction == 2) // LEFT
        newHead.x -= 1;

    if (direction == 3) // RIGHT
        newHead.x += 1;

    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::draw(sf::RenderWindow& window)
{
    for (auto& part : body)
    {
        sf::RectangleShape block;
        block.setSize(sf::Vector2f(32, 32));
        block.setFillColor(sf::Color::Green);
        block.setPosition(part.x * 32, part.y * 32);

        window.draw(block);
    }
}