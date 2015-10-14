#pragma once
using namespace std;

class Map
{
private:
	vector < vector <Tiles> > field; // Le terrain ne peut pas �tre modifi� directement. Notamment sa taille est calcul�e et fix�e une fois au d�but.
public:
	/*
	Initialisation de la map en fonction de la taille de l'�cran
	*/
	Map();// 
	~Map();

	/*
	M�thode pour modifier indirectement les �l�ments de la map
	*/
	void updateField();

	/*
	M�thode pour dessiner la map dans la fen�tre
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

