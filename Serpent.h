#pragma once
using namespace std;

//Classe permettant de gérer le serpent en temps réel.
class Serpent
{
public:
	Serpent();
	~Serpent();
};

enum Orientation //Pour la tête du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

struct head { //Structure pour la tête du serpent
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};




