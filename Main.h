#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <SFML/Graphics.hpp> //Chargement bibliotheque Graphique
#include "Map.h" // Gestion de l'affichage
#include "Menu.h" // Gestion du menu

// Definition de la fenetre
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

void play(sf::RenderWindow & window);

#endif