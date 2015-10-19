#pragma once
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp> //Chargement bibliotheque Graphique

#include "Input.h" //Gestion des commandes
#include "Serpent.h"//Gestion du serpent
#include "Map.h" // Gestion de l'affichage
#include "Menu.h" // Gestion du menu

using namespace std;
using namespace sf; // Pour utiliser la bibliotheque graphique plus rapidement.

					// Definition de la fenetre
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

void play(RenderWindow & window);