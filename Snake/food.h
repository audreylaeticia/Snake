#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include<fstream>
#include<cassert>

class Food
{

private:
    sf::Vector2i _position;
    int _cellSize;
    int _score;
    int _record;

    sf::CircleShape _shape;

    sf::Font _font;
    sf::Text _textScore;
    sf::Text _textRecord;
    sf::Texture _texturePomme;
    sf::Sprite _spritePomme;

    

public:
    Food();

    void spawn(const std::vector<sf::Vector2i>& snakeBody);
    void incrementScore();

    void draw(sf::RenderWindow& window);

    sf::Vector2i getPosition() const;

    void saveRecord();
    void loadRecord();
    void initialiserTexte();



};






