#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

enum Orientation //Pour la tete du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

//Structure pour la tete du serpent
struct Head 
{ 
	int line, column;//Position ligne/colonne dans la grille de jeu
	Orientation orientation; //orientation
};

// Structure pour identifier la queue du serpent
struct Tail 
{ 
	int row, column;
};

//Classe permettant de gerer le serpent en temps reel.
class Serpent
{
public:
    //Methodes
    void guiderTete(); //Guide la tête en fonction de l'input
    void allongerQueue();//Allonge la queue si fruit est mange
    bool estVivant();//Test si le serpent est vivant
	Serpent();
	~Serpent();
private:
	Head head;
	Tail tail;
};

#endif // !__SERPENT_H_INCLUDED__






