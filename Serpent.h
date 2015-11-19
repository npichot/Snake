#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include <vector>
#include "Menu.h"


typedef struct ElementSerpent
{
	int line;
	int column;
	Tiles tile;
};

//Classe permettant de gerer le serpent en temps reel.
class Serpent
{
public:
	//Methodes
	Serpent();
	~Serpent();
	bool isAlive() const { return alive; };// Permet de r�cup�rer l'attribut m_alive
	bool setHead(Map & map);
	Tiles getHead() { return m_posSerpent[0].tile; }; //Methode pour retourner l'�l�ment i du vecteur m_posSerpent
	void run(Map & map, Tiles head_tile);

private:
	std::vector<ElementSerpent> m_posSerpent;
	bool alive;
	ElementSerpent m_lastPosition; // Permet de garder en m�moire la derni�re position de la queue du serpent, pour pouvoir allonger la queue si besoin
	void deplacementSerpent(); // M�thode qui permet de d�placer le serpent
	void deplacementTete(Tiles head_tile, const Map & map);
	void setAlive(Map & map);
	void fruit_action(Map & map);
};



#endif // !__SERPENT_H_INCLUDED__






