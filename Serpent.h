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
	void run(Map & map, Tiles & head_tile, Serpent & serpentBot, Map copie);
	bool run(Map & map, Tiles & head_tile);
	void runBot(Map & map);
    int getScore() const;
    std::vector<ElementSerpent> getSnake();
    bool fruit_action(Map & map, Tiles & head_tile);
    int getSize();

private:
	std::vector<ElementSerpent> m_posSerpent;
	bool alive;
	ElementSerpent m_lastPosition; 
	void deplacementSerpent();
	void deplacementTete(Tiles head_tile, const Map & map);
	void setAlive(Map & map, bool bot);
    bool reverse_input;
	Tiles calculateNextHeadMove(Map & map);
    int m_Score;
};



#endif // !__SERPENT_H_INCLUDED__






