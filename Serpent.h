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
    void deplacementSerpent(Serpent &serpent); // Méthode qui permet de déplacer le serpent
    void deplacementTete(Serpent &serpent, Tiles head_tile);
    void allongerQueue();//Allonge la queue si fruit est mange
	void setAlive(Map & map);
    ElementSerpent *getElement(int i); //Methode pour retourner l'ŽlŽment i du vecteur m_posSerpent
    int sizeSerpent();//Permet d'accŽder ˆ la taille du serpent
	bool isAlive() const { return alive; };// Permet de récupérer l'attribut m_alive
	
private:
    std::vector<ElementSerpent> m_posSerpent; 
    bool alive;
	ElementSerpent m_lastPosition; // Permet de garder en mémoire la dernière position de la queue du serpent, pour pouvoir allonger la queue si besoin
};

#endif // !__SERPENT_H_INCLUDED__






