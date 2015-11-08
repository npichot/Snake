#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

// Definition de la fenetre principale
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

//Chaque element de la map est represente par un carre de 32*32
const int TILE_SIZE = 32;

enum Tiles //differentes tuiles dessin
{
	//Element Fixes
	TREE,
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
	UNKNOWN
};

//Definition d'une map pour convertir un string en enum
const std::map<std::string, Tiles> stringToEnum = 
{ 
	{"TREE",TREE},
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

const std::map<Tiles,std::string> enumToString =
{
	{ TREE,"TREE" },
	{ BODY_NORTH,"BODY_NORTH" },
	{ BODY_SOUTH,"BODY_SOUTH" },
	{ BODY_EAST,"BODY_EAST" },
	{ BODY_WEST,"BODY_WEST" },
	{ HEAD_NORTH,"HEAD_NORTH" },
	{ HEAD_SOUTH,"HEAD_SOUTH" },
	{ HEAD_EAST,"HEAD_EAST" },
	{ HEAD_WEST,"HEAD_WEST" },
	{ FRUIT,"FRUIT" },
	{ EMPTY,"EMPTY" },
};


class Map
{
private:
	std::vector<std::vector<Tiles>> field; // Le terrain ne peut pas etre modifie directement. Notamment sa taille est calculee et fixee une fois au debut.
public:
	/*
	Initialisation de la map en fonction de la taille de l'ecran
	*/
	Map(std::string filename, sf::RenderWindow const & window);
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
	void drawField(sf::RenderWindow & window, bool gridOn);

	/*
	Methode pour intitialiser la map a partir d'un fichier
	*/
	void loadMapFromFile(std::string filename);

	/*
	Methode pour la ligne potentielle correspondant à une position de la souris
	*/
	int getRowFromMouseCoordinate(int x, int y);

	/*
	Methode pour la colonne potentielle correspondant à une position de la souris
	*/
	int getColumnFromMouseCoordinate(int x, int y);

	std::vector<std::vector<Tiles>> getField() { return field; }
	
};

#endif


