#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "SFML\Graphics.hpp"

using namespace sf;
using namespace std;

//Chaque �lement de la map est repr�sent� par un carr� de 32*32
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

//D�finition d'une map pour convertir un string en enum
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
	vector < vector <Tiles> > field; // Le terrain ne peut pas �tre modifi� directement. Notamment sa taille est calcul�e et fix�e une fois au d�but.
public:
	/*
	Initialisation de la map en fonction de la taille de l'�cran
	*/
	Map(string filename);// 
	~Map();

	/*
	M�thode pour modifier indirectement les �l�ments de la map
	On modifie l'�l�ment � la position (i,j) par la Tile t
	*/
	void updateField(int i, int j, Tiles t);

	/*
	R�cup�rer la tile � l'emplacement (i, j)
	*/
	Tiles getTile(int i, int j);

	/*
	M�thode pour dessiner la map dans la fen�tre
	*/
	void drawField(RenderWindow & window);

	/*
	M�thode pour intitialiser la map � partir d'un fichier
	*/
	void loadMapFromFile(string filename);
	
};



