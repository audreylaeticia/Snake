#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
# include <iostream>

class Snake
{
private:
    
   
    sf::Vector2i _direction;

    
    std::vector<sf::Vector2i> _body;

    
    sf::Texture _textureTete;
    sf::Texture _textureCorps;
    sf::Texture _textureQueue;
  

   
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
    void grow(); 

    void draw(sf::RenderWindow& window);
    
    void initialise();
    bool checkCollisionWithWall(int width, int height);
    bool willHitWall(int width, int height) const;
    bool checkSelfCollision() const;

};
