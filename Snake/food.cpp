#include "food.h"

using namespace std;

Food::Food()
{
    _cellSize = 32;

    _score = 0;
    _record = 0;

    
    if (!_texturePomme.loadFromFile("ressources/pomme.png"))
    {
        std::cout << "Erreur chargement pomme\n";
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

    _spritePomme.setPosition(
        _position.x * _cellSize,
        _position.y * _cellSize
    );
}

void Food::incrementScore()
{
    _score++;

    if (_score > _record)
    {
        _record = _score;
        saveRecord();
}
}

void Food::draw(sf::RenderWindow& window)
{
    window.draw(_spritePomme);

    _textScore.setString("Score: " + std::to_string(_score));
    _textRecord.setString("Record: " + std::to_string(_record));

    window.draw(_textScore);
    window.draw(_textRecord);
}

sf::Vector2i Food::getPosition() const
{
        return _position;
    
}

void Food::saveRecord()
{
       std:: ofstream file("record.txt");
        if (file.is_open())
            file << "Vous avez terminé votre partie avec un meilleur score de: "<<_record;
        file.close();
    }

void Food::loadRecord()
{
    std::ifstream file("record.txt");
    if (file.is_open())
        file >> _record;
}



void Food::initialiserTexte()
{
    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        std::cout << "Erreur police\n";
    }

    _textScore.setFont(_font);
    _textScore.setCharacterSize(20);
    _textScore.setFillColor(sf::Color::White);
    _textScore.setPosition(610, 20);

    _textRecord.setFont(_font);
    _textRecord.setCharacterSize(20);
    _textRecord.setFillColor(sf::Color::Yellow);
    _textRecord.setPosition(610, 60);
}
