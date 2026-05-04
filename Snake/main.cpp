#include <iostream>
#include "Snake.h"
#include "Game.h"
#include "food.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60); // frame

    Menu menu;

    int choix = menu.run(window);

    if (choix == 1) {
        Game game;// pour lancer le jeu
        game.startMusic();
        game.run();
    }
    else {
        std::cout << "Vous nous quittez, au revoir et a la prochaine !" << std::endl;
        window.close(); //pour fermer la console
       // break;
    }

    //Game game;
    //game.run();

    //return 0;
}