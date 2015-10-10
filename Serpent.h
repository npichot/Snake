#pragma once
using namespace std;

//Classe permettant de g�rer le serpent en temps r�el.
class Serpent
{
public:
	Serpent();
	~Serpent();
};

enum Orientation //Pour la t�te du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

struct head { //Structure pour la t�te du serpent
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};




