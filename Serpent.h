#ifndef __SERPENT_H_INCLUDED__
#define __SERPENT_H_INCLUDED__

#include "Map.h"
#include <vector>
#include "Menu.h"
#include <algorithm>

typedef struct ElementSerpent ElementSerpent;
struct ElementSerpent
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
	Serpent(bool alive);
	~Serpent();
	bool isAlive() const { return alive; };// Permet de récupérer l'attribut m_alive
	bool setHead(Map map, bool bot);
	Tiles getHead() { return m_posSerpent[0].tile; }; //Methode pour retourner l'ŽlŽment i du vecteur m_posSerpent
    bool isreverse() const { return reverse_input; }; //Permet de récupérer l'attribut reverse_input
	void run(Map & map, Tiles & head_tile, Serpent & serpentBot, Map copie);//Permet d'initialiser le bot
	bool run(Map & map, Tiles head_tile);
	void runBot(Map & map);

private:
	std::vector<ElementSerpent> m_posSerpent;
	bool alive;
	ElementSerpent m_lastPosition; // Permet de garder en mémoire la dernière position de la queue du serpent, pour pouvoir allonger la queue si besoin
	void deplacementSerpent(); // Méthode qui permet de déplacer le serpent
	void deplacementTete(Tiles head_tile, const Map & map);
	void setAlive(Map & map, bool bot);
	bool fruit_action(Map & map, Tiles & head_tile);
    bool reverse_input;
	Tiles calculateNextHeadMove(Map & map);
};



#endif // !__SERPENT_H_INCLUDED__






