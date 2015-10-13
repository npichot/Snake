#pragma once
using namespace std;

//Classe permettant de gérer le serpent en temps réel.
class Serpent
{
public:
	Serpent();
	~Serpent();
private:
	Head head;
	Tail tail;
};

enum Orientation //Pour la tête du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

struct Head { //Structure pour la tête du serpent
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};

struct Tail { // Structure pour identifier la queue du serpent
	int row, column;
};




