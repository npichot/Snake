#pragma once
using namespace std;

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
	*/
	void updateField();

	/*
	Méthode pour dessiner la map dans la fenêtre
	*/
	void draw(RenderWindow * window);
	
};

const enum Tiles //differentes tuiles dessin
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
};

