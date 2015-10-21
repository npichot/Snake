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
	Serpent();
	~Serpent();
    void guiderTete(); //Guide la t�te en fonction de l'input
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextPosition(Button entree); //M�thode pour obtenir la future position de la t�te, sans changer la position actuelle
	bool isAlive(Map carte) const; 
	
private:
	Head m_head; 
	Head m_headFuture;
	Tail m_tail;
};

#endif // !__SERPENT_H_INCLUDED__






