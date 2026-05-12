#include "Snake.h"
#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

Game::Game()
{
    hasStarted = false;
    gameOver = false;
    speed = 0.2f;
    minSpeed = 0.05f;
    int score;

    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        cout << "Erreur chargement police\n";
    }

    initGameOverUI();

    uiBar.setSize(sf::Vector2f(800, 100));
    uiBar.setFillColor(sf::Color(40, 40, 40));
    uiBar.setPosition(0, 0);

    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        cout << "Erreur chargement fond\n";
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
    eatSound.setVolume(400);

    if (!gameMusic.openFromFile("ressources/son.wav"))
    {
        cout << "Erreur musique jeu\n";
    }

    gameMusic.setLoop(true);
    gameMusic.setVolume(40);

    if (!gameOverBuffer.loadFromFile("ressources/music_gameover.wav"))
    {
        cout << "Erreur son game over"<<endl;
    }

    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(100);
}

void Game::resetGame()
{
    gameOver = false;
    hasStarted = false;

    speed = 0.2f;
    snake.initialise();
    food.spawn(snake.getBody());
    food.resetScore();
    clock.restart();
    
}

void Game::startMusic()
{
    if (gameMusic.getStatus() != sf::Music::Playing)
    {
        gameMusic.play();
    }
}

void Game::runApp(sf::RenderWindow& window)
{
    Menu menu;

    while (window.isOpen())
    {
        int choix = menu.run(window, paused);

        if (choix == 1) //play
        {
            menu.stopMusic();
            startMusic();

            resetGame();
            paused = false;
            startMusic();
            run(window);
        }
        else if (choix == 2) // reprendre
        {
            menu.stopMusic();

           

            paused = false;
            startMusic();
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
                    gameMusic.pause();
                    return;
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

                if (event.key.code == sf::Keyboard::P)
                {
                    paused = !paused;
                }
            }

            if (gameOver && event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    
                    gameMusic.stop();
                    resetGame();
                    paused = false;
                    return;
                    
                }
                if (replayButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    resetGame();
                }
            }

        }

        if (!paused && !gameOver && hasStarted && clock.getElapsedTime().asSeconds() > speed)
        {
            if (snake.willHitWall(25, 15))
            {
                gameOver = true;
                gameMusic.stop();
                gameOverSound.play();
            }

            else
            {
                snake.move();

                if (snake.checkSelfCollision())
                {
                    gameOver = true;
                    gameMusic.stop();
                    gameOverSound.play();
                }
            }

            clock.restart();
        }

        if (!gameOver && snake.getHeadPosition() == food.getPosition())
        {
            speed -= 0.01f;

            if (speed < minSpeed)
                speed = minSpeed;

            eatSound.stop();
            eatSound.play();

            snake.grow();
            food.incrementScore();
            food.spawn(snake.getBody());
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
            window.draw(returnButton);
            window.draw(textReturn);
        }

        if (paused)
        {
            window.draw(textPause);
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

    

   

    textGameOver.setFont(_font);
    textGameOver.setString("GAME OVER");
    textGameOver.setCharacterSize(28);
    textGameOver.setFillColor(sf::Color::White);
    textGameOver.setPosition(300, 220);

    textFinalScore.setFont(_font);
    textFinalScore.setCharacterSize(20);
    textFinalScore.setFillColor(sf::Color::White);
    textFinalScore.setPosition(320, 270);

    returnButton.setSize(sf::Vector2f(200, 50));
    returnButton.setFillColor(sf::Color(50, 180, 50));
    returnButton.setPosition(300, 310);

    textReturn.setFont(_font);
    textReturn.setString("RETURN");
    textReturn.setCharacterSize(20);
    textReturn.setFillColor(sf::Color::White);
    textReturn.setPosition(360, 320);

    replayButton.setSize(sf::Vector2f(200, 50));
    replayButton.setFillColor(sf::Color(50, 180, 50));
    replayButton.setPosition(300, 370);

    textReplay.setFont(_font);
    textReplay.setString("REPLAY");
    textReplay.setCharacterSize(20);
    textReplay.setFillColor(sf::Color::White);
    textReplay.setPosition(365, 380);

}