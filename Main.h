#pragma once
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp> //Chargement biblioth�que Graphique

#include "Input.h" //Gestion des commandes
#include "Serpent.h"//Gestion du serpent
#include "Map.h" // Gestion de l'affichage

using namespace std;
using namespace sf; // Pour utiliser la biblioth�que graphique plus rapidement.

					// D�finition de la fen�tre
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;