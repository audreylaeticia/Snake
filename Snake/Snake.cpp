#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "food.h"
#include <iostream>

using namespace std;
using namespace sf;


Snake::Snake()
{
    initialise();
}

void Snake::setDirection(const sf::Vector2i& newdirection)
{
    if (newdirection.x == -_direction.x && newdirection.y == -_direction.y)
        return; 

    _direction = newdirection;
}
Vector2i Snake::getHeadPosition() const
{
    return _body.front(); // tête du serpent
}

const std::vector<sf::Vector2i>& Snake::getBody() const
{
    return _body; // tout le corps
}
void Snake::move()
{
    Vector2i newHead = _body.front() + _direction;


    _body.insert(_body.begin(), newHead);

    if (_grandit)
    {
        _grandit = false;
    }
    else
    {
        _body.pop_back();
    }
}

void Snake::grow()
{
    _grandit = true;
}

void Snake::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < _body.size(); i++)
    {
        sf::Sprite sprite;

        if (i == 0)
            sprite = _spriteTete;
        else if (i == _body.size() - 1)
            sprite = _spriteQueue;
        else
            sprite = _spriteCorps;

        sprite.setPosition(
            _body[i].x * 32,
            _body[i].y * 32 + 100 
        );

        window.draw(sprite);
    }
}

void Snake::initialise()
{

  
    _body.clear();
    _body.push_back({ 5, 5 });
    _body.push_back({ 4, 5 });
    _body.push_back({ 3, 5 });

  
    _direction = { 1, 0 };

    
    _grandit = false;


    if (!_textureTete.loadFromFile("ressources/serpentTete.png")) {
        cout << "Érreur chargement serpentTete.png";
    }
    if (!_textureCorps.loadFromFile("ressources/serpentCorps.png")) {
        cout << "Érreur chargement serpentCorps.png";
    }
    if (!_textureQueue.loadFromFile("ressources/serpentQueue.png")) {
        cout << "Érreur chargement serpentQueue.png";
    }

   
    _spriteTete.setTexture(_textureTete);
    _spriteCorps.setTexture(_textureCorps);
    _spriteQueue.setTexture(_textureQueue);

}

bool Snake::checkCollisionWithWall(int width, int height)
{
    Vector2i head = _body.front();

    if (head.x < 0 || head.x >= width ||
        head.y < 0 || head.y >= height)
    {
        return true; 
    }

    return false;
}

bool Snake::willHitWall(int width, int height) const
{
    Vector2i next = _body.front() + _direction;

    if (next.x < 0 || next.x >= width ||
        next.y < 0 || next.y >= height)
    {
        return true;
    }

    return false;
}

bool Snake::checkSelfCollision() const
{
    Vector2i head = _body.front();

    for (int i = 1; i < _body.size(); i++)
    {
        if (_body[i] == head)
        {
            return true; 
        }
    }

    return false;
}
