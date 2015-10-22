#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include "Input.h"
#include "Head.h"
#include <vector>




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
	vector<vector<int>> deplacementSerpent(); // Méthode qui permet de déplacer le serpent
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextHead(Button entree); //Méthode pour obtenir la future position de la tête, sans changer la position actuelle
	bool isAlive(Map carte) const;
	bool 
	
private:
	vector<vector<int>> m_posSerpent;
	Head m_head; 
	Head m_headFuture; // Rajouter des commentaires
	Tail m_tail;
};

#endif // !__SERPENT_H_INCLUDED__






