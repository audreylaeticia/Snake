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
sf::Vector2i Snake::getHeadPosition() const
{
    return _body.front(); // tête du serpent
}

const std::vector<sf::Vector2i>& Snake::getBody() const
{
    return _body; // tout le corps
}
void Snake::move()
{
    // nouvelle position de la tête
    sf::Vector2i newHead = _body.front() + _direction;

    // limites de la grille (800x600 avec cases de 32px)
    int maxX = 25;
    int maxY = 18;

    //  BLOQUER SI LE SERPENT SORT
    if (newHead.x < 0 || newHead.x >= maxX ||
        newHead.y < 0 || newHead.y >= maxY)
    {
        return; // ? on ne bouge pas
    }

    // ajouter la nouvelle tête
    _body.insert(_body.begin(), newHead);

    // gestion de la croissance
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

bool Snake::checkCollisionWithWall(int width, int height)
{
    sf::Vector2i head = _body.front();

    if (head.x < 0 || head.x >= width ||
        head.y < 0 || head.y >= height)
    {
        return true;
    }

    return false;
}

