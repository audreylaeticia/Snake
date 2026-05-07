#include <iostream>
#include "Snake.h"
#include "Game.h"
#include "food.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60); 

    Menu menu;
    Game game; 
    game.runApp(window);
  
    return 0;
}