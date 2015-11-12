#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



//Chaque element de la map est represente par un carre de 32*32
const int TILE_SIZE = 32;

enum Tiles //differentes tuiles dessin
{
	//Element Fixes
	TREE=0,
	// Serpent
	BODY_NORTH=10,
	BODY_EAST=11,
	BODY_SOUTH=12,
	BODY_WEST=13,
	HEAD_NORTH=20,
	HEAD_EAST=21,
	HEAD_SOUTH=22,
	HEAD_WEST=23,
	//Autres
	FRUIT=30,
	EMPTY=40,
	UNKNOWN
};

//Definition d'une map pour convertir un string en enum
const std::map<std::string, Tiles> getEnumValue = 
{ 
	{"BUSHES",TREE},
	{"BODY_NORTH",BODY_NORTH},
	{"BODY_SOUTH",BODY_SOUTH},
	{"BODY_EAST",BODY_EAST},
	{"BODY_WEST",BODY_WEST},
	{"HEAD_NORTH",HEAD_NORTH},
	{"HEAD_SOUTH",HEAD_SOUTH},
	{"HEAD_EAST",HEAD_EAST},
	{"HEAD_WEST",HEAD_WEST},
	{"FRUIT",FRUIT},
	{"EMPTY",EMPTY}, 
};

const std::map<Tiles, Tiles> convertHeadtoBody =
{
    {HEAD_EAST, BODY_EAST},
    {HEAD_NORTH, BODY_NORTH},
    {HEAD_SOUTH, BODY_SOUTH},
    {HEAD_WEST, BODY_WEST}
};

class Map
{
private:
	std::vector < std::vector <sf::Sprite> > field; // Le terrain ne peut pas etre modifie directement. Notamment sa taille est calculee et fixee une fois au debut.
	sf::RenderWindow & window;
	sf::Texture * textures[5];
public:
	/*
	Initialisation de la map en fonction de la taille de l'ecran
	*/
	Map(std::string filename, sf::RenderWindow & window);
	~Map();

	/*
	Methode pour modifier indirectement les elements de la map
	On modifie l'element a la position (i,j) par la Tile t
	*/
	void updateField(int i, int j, Tiles t);

	/*
	Recuperer la tile a l'emplacement (i, j)
	*/
	Tiles getTile(int i, int j);

	/*
	Methode pour dessiner la map dans la fenetre
	*/
	void drawField();

	/*
	Methode pour intitialiser la map a partir d'un fichier
	*/
	void loadMapFromFile(std::string filename);

	/*
	Methode pour faire apparaitre un fruit aleatoirement
	*/
	void popFruit();

};

#endif


