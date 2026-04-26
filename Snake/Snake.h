#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
# include <iostream>

class Snake
{
private:
    
    // direction du serpent
    sf::Vector2i _direction;

    // corps du serpent (positions)
    std::vector<sf::Vector2i> _body;

    // textures
    sf::Texture _textureTete;
    sf::Texture _textureCorps;
    sf::Texture _textureQueue;
  

    // sprites
    sf::Sprite _spriteTete;
    sf::Sprite _spriteCorps;
    sf::Sprite _spriteQueue;
    


    bool _grandit;

public:
    Snake();

    sf::Vector2i getHeadPosition() const;
    const std::vector<sf::Vector2i>& getBody() const;

    void setDirection(const sf::Vector2i& newdirection);
    void move();
    void grow(); // allonger le serpent chaque fois qu'il mange

    void draw(sf::RenderWindow& window);
    
    void initialise();
    bool checkCollisionWithWall(int width, int height);

};
