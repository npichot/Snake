#pragma once
#include <vector>
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

class Map
{
private:
	vector < vector <Tiles> > field; // Le terrain ne peut pas être modifié directement. Notamment sa taille est calculée et fixée une fois au début.
public:
	/*
	Initialisation de la map en fonction de la taille de l'écran
	*/
	Map();// 
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
	
};



