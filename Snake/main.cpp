#include <iostream>
#include "Snake.h"
#include "Game.h"
#include "food.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60); // frame

    Menu menu;
    Game game; //  UNE SEULE FOIS

    while (window.isOpen())
    {
        int choix = menu.run(window, game.paused);

        if (choix == 1) // PLAY
        {
            game.resetGame(); // nouvelle partie
            game.paused = false;
            game.run(window);
        }
        else if (choix == 2) // REPRENDRE
        {
            game.paused = false;
            game.run(window); // reprend là où tu étais
        }
        else {
            std::cout << "Vous nous quittez, au revoir et a la prochaine !" << std::endl;
            window.close(); //pour fermer la console
            // break;
        }

        //Game game;
        //game.run();
    }
    return 0;
}