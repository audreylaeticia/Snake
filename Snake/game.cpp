#include "Snake.h"
#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game()
{
    //window.create(VideoMode(800, 700), "Snake");
    //window.setFramerateLimit(60);

    hasStarted = false;
    gameOver = false;
    speed = 0.2f;
    minSpeed = 0.05f;
    int score;

    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        std::cout << "Erreur chargement police\n";
    }

    initGameOverUI();

    uiBar.setSize(sf::Vector2f(800, 100));
    uiBar.setFillColor(sf::Color(40, 40, 40));
    uiBar.setPosition(0, 0);

    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    _spriteFond.setTexture(_textureFond);

    _spriteFond.setScale(
        800.0f / _textureFond.getSize().x,
        600.0f / _textureFond.getSize().y
    );

    _spriteFond.setPosition(0, 100);

    food.spawn(snake.getBody());

    if (!keyBuffer.loadFromFile("ressources/music_move.wav"))
    {
        std::cout << "Erreur son touche\n";
    }

    keySound.setBuffer(keyBuffer);
    keySound.setVolume(60);


    if (!eatBuffer.loadFromFile("ressources/music_food.wav"))
    {
        std::cout << "Erreur son pomme\n";
    }

    eatSound.setBuffer(eatBuffer);
    eatSound.setVolume(70);

    if (!gameMusic.openFromFile("ressources/son.wav"))
    {
        std::cout << "Erreur musique jeu\n";
    }

    gameMusic.setLoop(true);
    gameMusic.setVolume(15); 
    gameMusic.play();
}

void Game::resetGame()
{
    gameOver = false;
    hasStarted = false;

    snake.initialise();
    food.spawn(snake.getBody());
    food.resetScore();
    clock.restart();
}

void Game::startMusic()
{
    gameMusic.play();
}
void Game::runApp(sf::RenderWindow& window)
{
    Menu menu;

    while (window.isOpen())
    {
        int choix = menu.run(window, paused);

        if (choix == 1) // PLAY
        {
            resetGame();
            paused = false;
            run(window);
        }
        else if (choix == 2) // REPRENDRE
        {
            paused = false;
            run(window);
        }
        else
        {
            std::cout << "Vous nous quittez, au revoir !" << std::endl;
            window.close();
        }
    }
}

void Game::run(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    paused = true;
                    return; // retour au menu
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    snake.setDirection({ 0, -1 });
                    keySound.stop();
                    keySound.play();
                    hasStarted = true; 
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    snake.setDirection({ 0, 1 });
                    keySound.stop();
                    keySound.play();
                    hasStarted = true; 
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    snake.setDirection({ -1, 0 });
                    keySound.stop();
                    keySound.play();
                    hasStarted = true; 
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    snake.setDirection({ 1, 0 });
                    keySound.stop();
                    keySound.play();
                    hasStarted = true; 
                }
            }

            if (gameOver && event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (replayButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    resetGame();
                }
            }
        }

        if (!gameOver && hasStarted && clock.getElapsedTime().asSeconds() > speed)
        {
            if (snake.willHitWall(25, 15))
            {
                gameOver = true;
            }
            else
            {
                snake.move();

                if (snake.checkSelfCollision())
                {
                    gameOver = true;
                }
            }

            clock.restart();
        }

        if (!gameOver && snake.getHeadPosition() == food.getPosition())
        {
            speed -= 0.01f;

            if (speed < minSpeed)
                speed = minSpeed;

            snake.grow();
            food.incrementScore();
            food.spawn(snake.getBody());
            eatSound.stop();
            eatSound.play(); 
        }

        window.clear();

        window.draw(uiBar);
        window.draw(_spriteFond);
        food.draw(window);
        snake.draw(window);

        if (gameOver)
        {
            textFinalScore.setString(
                "Score: " + std::to_string(food.getScore())
            );

            window.draw(overlay);
            window.draw(panel);
            window.draw(textGameOver);
            window.draw(textFinalScore);
            window.draw(replayButton);
            window.draw(textReplay);
        }

        window.display();
    }
}

void Game::initGameOverUI()
{
    overlay.setSize(sf::Vector2f(800, 700));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    panel.setSize(sf::Vector2f(300, 220));
    panel.setFillColor(sf::Color(200, 160, 40));
    panel.setPosition(250, 200);

    replayButton.setSize(sf::Vector2f(200, 50));
    replayButton.setFillColor(sf::Color(50, 180, 50));
    replayButton.setPosition(300, 350);

    textGameOver.setFont(_font);
    textGameOver.setString("GAME OVER");
    textGameOver.setCharacterSize(28);
    textGameOver.setFillColor(sf::Color::White);
    textGameOver.setPosition(300, 220);

    textFinalScore.setFont(_font);
    textFinalScore.setCharacterSize(20);
    textFinalScore.setFillColor(sf::Color::White);
    textFinalScore.setPosition(320, 270);

    textReplay.setFont(_font);
    textReplay.setString("REPLAY");
    textReplay.setCharacterSize(20);
    textReplay.setFillColor(sf::Color::White);
    textReplay.setPosition(350, 360);
}