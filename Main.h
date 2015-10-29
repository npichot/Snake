#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <SFML/Graphics.hpp> //Chargement bibliotheque Graphique
#include "Map.h" // Gestion de l'affichage
#include "Menu.h" // Gestion du menu
#include "Serpent.h"//Gestion du serpent
#include "MapCreation.h"//interface de creation de map

void play(sf::RenderWindow & window);

#endif