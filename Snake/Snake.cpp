#include <SFML/Graphics.hpp>
#include "Snake.h"
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
        return; // empeche de faire un demi-tour

    _direction = newdirection;
}

void Snake::move()
{
    sf::Vector2i newHead = _body.front() + _direction;
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

        sprite.setPosition(_body[i].x * 32, _body[i].y * 32);

        window.draw(sprite);
    }
}

void Snake::initialise()
{

    // corps initial
    _body.clear();
    _body.push_back({ 5, 5 });
    _body.push_back({ 4, 5 });
    _body.push_back({ 3, 5 });

    // direction
    _direction = { 1, 0 };

    // croissance
    _grandit = false;


    if (!_textureTete.loadFromFile("ressources/serpentTete.png")) {
        cout << "érreur chargement serpentTete.png";
    }
    if (!_textureCorps.loadFromFile("ressources/serpentCorps.png")) {
        cout << "érreur chargement serpentCorps.png";
    }
    if (!_textureQueue.loadFromFile("ressources/serpentQueue.png")) {
        cout << "érreur chargement serpentQueue.png";
    }

    //associer les sprites 
    _spriteTete.setTexture(_textureTete);
    _spriteCorps.setTexture(_textureCorps);
    _spriteQueue.setTexture(_textureQueue);

}

