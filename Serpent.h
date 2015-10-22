#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include "Input.h"
#include "Head.h"
#include <vector>

// Structure pour identifier un ŽlŽment du serpent (ligne, colonne, orientation);
struct elementSerpent
{ 
	int row, column;
    Orientation orientation;
};

//Classe permettant de gerer le serpent en temps reel.
class Serpent
{
public:
    //Methodes
	Serpent();
	~Serpent();
    std::vector<elementSerpent> deplacementSerpent(); // Méthode qui permet de déplacer le serpent
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextHead(Button entree); //Méthode pour obtenir la future position de la tête, sans changer la position actuelle
	bool isAlive(Map carte);
	
private:
    std::vector<elementSerpent> m_posSerpent;
	Head m_head; 
	Head m_headFuture; // Rajouter des commentaires
    bool m_alive;
};

#endif // !__SERPENT_H_INCLUDED__






