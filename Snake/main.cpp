#include <iostream>
#include "Snake.h"
#include "Game.h"
#include "food.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60); // frame

    Game game; //  UNE SEULE FOIS
    game.runApp(window);
  
    return 0;
}