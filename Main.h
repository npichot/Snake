#pragma once
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp> //Chargement bibliothèque Graphique

#include "Input.h" //Gestion des commandes
#include "Serpent.h"//Gestion du serpent
#include "Map.h" // Gestion de l'affichage

using namespace std;
using namespace sf; // Pour utiliser la bibliothèque graphique plus rapidement.

					// Définition de la fenêtre
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;