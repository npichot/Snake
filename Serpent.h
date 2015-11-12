#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include "Input.h"
#include "ElementSerpent.h"
#include <vector>
#include "Menu.h"



//Classe permettant de gerer le serpent en temps reel.
class Serpent
{
public:
    //Methodes
	Serpent();
	~Serpent();
    void deplacementSerpent(Serpent &serpent); // M�thode qui permet de d�placer le serpent
    void deplacementTete(Serpent &serpent, Tiles head_tile);
    void allongerQueue();//Allonge la queue si fruit est mange
	void nextHead(Button entree); //M�thode pour obtenir la future position de la t�te, sans changer la position actuelle
	void isAlive(Map carte);
    ElementSerpent *getElement(int i); //Methode pour retourner l'�l�ment i du vecteur m_posSerpent
    int sizeSerpent();//Permet d'acc�der � la taille du serpent
	bool getAlive() const; // Permet de r�cup�rer l'attribut m_alive
	
private:
    std::vector<ElementSerpent> m_posSerpent; 
	ElementSerpent m_head; 
	ElementSerpent m_headFuture; // Permet de garder la position future de la t�te en attributs, afin de pouvoir r�aliser le check des conditions
    bool m_alive;
	ElementSerpent m_lastPosition; // Permet de garder en m�moire la derni�re position de la queue du serpent, pour pouvoir allonger la queue si besoin
};

#endif // !__SERPENT_H_INCLUDED__






