#include <iostream>
#include "Snake.h"
#include "Game.h"
#include "food.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");

    Menu menu;

    int choice = menu.run(window);

    if (choice == 1) {
        // pour lancer le jeu
    }
    else {
        window.close();//fermer
    }

    Game game;
    game.run();

    return 0;
}