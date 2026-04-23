#include <iostream>
#include "Snake.h"
#include "Game.h"

int main()
{
    Game game;
    game.run();

    return 0;


    /*
.h
    #pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
class MainMenu {
private:
    // Fenêtre du jeu
    sf::RenderWindow& window;

    // Police et textes
    sf::Font font;
    sf::Text title, playText, settingsText, quitText, aboutText, instructionsText;

     // Arrière-plan
    sf::Sprite background;
    sf::Texture backgroundTexture;
public:
    // Constructeur : initialise le menu principal avec la fenêtre passée en paramètre
    MainMenu(sf::RenderWindow& win);



.cpp

#include "MainMenu.h"
#include <iostream>
// Constructeur : initialise les éléments graphiques et sonores du menu principal
MainMenu::MainMenu(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("ressources/StalinistOne-Regular.ttf");

    // Titre principal
    title.setFont(font);
    title.setString("Snake");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(100, 50);

    // Bouton Play
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(40);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(100, 150);

    // Bouton Settings
    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(40);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition(100, 220);

    // Bouton Statistiques
    statsText.setFont(font);
    statsText.setString("STATS");
    statsText.setCharacterSize(40);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(100, 290); // Ajuste la position si nécessaire

    // Bouton Quitter
    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(40);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(100, 490);

    // Bouton About
    aboutText.setFont(font);
    aboutText.setString("About Us");
    aboutText.setCharacterSize(40);
    aboutText.setFillColor(sf::Color::White);
    aboutText.setPosition(100, 360);

    // Bouton Instructions
    instructionsText.setFont(font);
    instructionsText.setString("Instructions");
    instructionsText.setCharacterSize(40);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(100, 430);
    */

   
}