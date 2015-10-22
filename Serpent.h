#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include "Input.h"
#include "Head.h"




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
    void guiderTete(); //Guide la tête en fonction de l'input
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextPosition(Button entree); //MÈthode pour obtenir la future position de la tÍte, sans changer la position actuelle
	bool isAlive(Map carte) const; 
	
private:
	Head m_head; 
	Head m_headFuture;
	Tail m_tail;
};

#endif // !__SERPENT_H_INCLUDED__






