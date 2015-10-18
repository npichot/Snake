#pragma once
using namespace std;

typedef enum  //Pour la tête du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}Orientation;

struct Head { //Structure pour la tête du serpent
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};

struct Tail { // Structure pour identifier la queue du serpent
	int row, column;
};

//Classe permettant de gérer le serpent en temps réel.
class Serpent
{
    public:
    //Mthodes
    void guiderTete(); //Guide la tte en fonction de l'input
    void allongerQueue();//Allonge la queue si fruit mang
    bool estVivant() const;//Test si le serpent est vivant
	Serpent();
	~Serpent();
private:
	Head head;
	Tail tail;
};








