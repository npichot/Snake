#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "Map.h" 
#include "Menu.h"
#include "Serpent.h"
#include "MapCreation.h"

// Definition de la fenetre
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

void play(sf::RenderWindow & window);
void displayHowTo(sf::RenderWindow & window);

#endif // !__MAIN_H__