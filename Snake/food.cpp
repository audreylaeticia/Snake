#include "food.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

Food::Food()
{
    _cellSize = 32;

    _score = 0;
    _record = 0;

    // initialiser le random
    srand(time(NULL));

    //  charger texture pomme
    if (!_texturePomme.loadFromFile("ressources/pomme.png"))
    {
        cout << "Erreur chargement pomme\n";
    }
    else
    {
        _spritePomme.setTexture(_texturePomme);

        _spritePomme.setScale(
            (float)_cellSize / _texturePomme.getSize().x,
            (float)_cellSize / _texturePomme.getSize().y
        );
    }

    initialiserTexte();
    loadRecord();
}

//  positionner la pomme
void Food::spawn(const std::vector<sf::Vector2i>& snakeBody)
{
    bool valid = false;

    while (!valid)
    {
        _position.x = rand() % 25;
        _position.y = rand() % 18;

        valid = true;

        for (auto& part : snakeBody)
        {
            if (part == _position)
            {
                valid = false;
                break;
            }
        }
    }

    // +100 pour descendre sous la UI
    _spritePomme.setPosition(
        _position.x * _cellSize,
        _position.y * _cellSize + 100
    );
}

//  augmenter score
void Food::incrementScore()
{
    _score++;

    if (_score > _record)
    {
        _record = _score;
        saveRecord();
    }
}

//  affichage
void Food::draw(sf::RenderWindow& window)
{
    window.draw(_spritePomme);

    _textScore.setString("Score: " + std::to_string(_score));
    _textRecord.setString("Record: " + std::to_string(_record));

    window.draw(_textScore);
    window.draw(_textRecord);
}

//  position logique
sf::Vector2i Food::getPosition() const
{
    return _position;
}

//  sauvegarde record
void Food::saveRecord()
{
    ofstream file("record.txt");
    if (file.is_open())
    {
        file << _record;
    }
}

// 🔥 chargement record
void Food::loadRecord()
{
    ifstream file("record.txt");
    if (file.is_open())
    {
        file >> _record;
    }
    else
    {
        _record = 0;
    }
}

//  initialisation texte UI
void Food::initialiserTexte()
{
    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        cout << "Erreur police\n";
    }

    _textScore.setFont(_font);
    _textScore.setCharacterSize(22);
    _textScore.setFillColor(sf::Color::White);
    _textScore.setPosition(20, 20); // 🔥 dans la barre UI

    _textRecord.setFont(_font);
    _textRecord.setCharacterSize(22);
    _textRecord.setFillColor(sf::Color::Yellow);
    _textRecord.setPosition(200, 20);
}

int Food::getScore() const
{
    return _score;
}
