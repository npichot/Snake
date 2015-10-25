#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include "Input.h"
#include "Head.h"
#include <vector>



//Classe permettant de gerer le serpent en temps reel.
class Serpent
{
public:
    //Methodes
	Serpent();
	~Serpent();
    std::vector<ElementSerpent> deplacementSerpent(); // Méthode qui permet de déplacer le serpent
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextHead(Button entree); //Méthode pour obtenir la future position de la tête, sans changer la position actuelle
	void isAlive(Map carte);
	
private:
    std::vector<ElementSerpent> m_posSerpent; 
	ElementSerpent m_head; 
	ElementSerpent m_headFuture; // Permet de garder la position future de la tête en attributs, afin de pouvoir réaliser le check des conditions
    bool m_alive;
};

#endif // !__SERPENT_H_INCLUDED__






