#pragma once
using namespace std;

typedef enum  //Pour la t�te du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}Orientation;

struct Head { //Structure pour la t�te du serpent
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};

struct Tail { // Structure pour identifier la queue du serpent
	int row, column;
};

//Classe permettant de g�rer le serpent en temps r�el.
class Serpent
{
public:
	Serpent();
	~Serpent();
private:
	Head head;
	Tail tail;
};








