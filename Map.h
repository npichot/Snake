#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "SFML\Graphics.hpp"

using namespace sf;
using namespace std;

//Chaque élement de la map est représenté par un carré de 32*32
const int TILE_SIZE = 32;

typedef enum  //differentes tuiles dessin
{
	//Element Fixes
	BUSHES,
	// Serpent
	BODY_NORTH,
	BODY_SOUTH,
	BODY_EAST,
	BODY_WEST,
	HEAD_NORTH,
	HEAD_SOUTH,
	HEAD_EAST,
	HEAD_WEST,
	//Autres
	FRUIT,
	EMPTY,
} Tiles;

//Définition d'une map pour convertir un string en enum
const map<string, Tiles> getEnumValue = 
{ 
	{"BUSHES",BUSHES},
	{"BODY_NORTH",BODY_NORTH},
	{"BODY_SOUTH",BODY_SOUTH},
	{"BODY_EAST",BODY_EAST},
	{"BODY_WEST",BODY_WEST},
	{"HEAD_NORTH",HEAD_NORTH},
	{"HEAD_SOUTH",HEAD_SOUTH},
	{"HEAD_EAST",HEAD_EAST},
	{"HEAD_WEST",HEAD_WEST},
	{"FRUIT",FRUIT},
	{"EMPTY",EMPTY} 
};

typedef struct //Definition d'une structure pour un item de la map
{
	int i;
	int j;
	Tiles tile;
}Item;

class Map
{
private:
	vector < vector <Tiles> > field; // Le terrain ne peut pas être modifié directement. Notamment sa taille est calculée et fixée une fois au début.
public:
	/*
	Initialisation de la map en fonction de la taille de l'écran
	*/
	Map(string filename);// 
	~Map();

	/*
	Méthode pour modifier indirectement les éléments de la map
	On modifie l'élément à la position (i,j) par la Tile t
	*/
	void updateField(int i, int j, Tiles t);

	/*
	Récupérer la tile à l'emplacement (i, j)
	*/
	Tiles getTile(int i, int j);

	/*
	Méthode pour dessiner la map dans la fenêtre
	*/
	void drawField(RenderWindow & window);

	/*
	Méthode pour intitialiser la map à partir d'un fichier
	*/
	void loadMapFromFile(string filename);
	
};



