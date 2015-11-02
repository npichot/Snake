#ifndef __ELEMENTSERPENT_H_INCLUDED__
#define __ELEMENTSERPENT_H_INCLUDED__
#include "Map.h"

enum Orientation //Plus besoin
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

class ElementSerpent { //Classe pour chaque élément du serpent

	//Méthodes
public:
	ElementSerpent();
	~ElementSerpent();
	ElementSerpent(int line, int column, Tiles tile);
	int getLine() const;
	int getColumn() const;
	Tiles gettile() const;
    void setLine(int i);//Changer la ligne d'un ElementSerpent
    void setColumn(int i);//Changer la colonne d'un Elemeserpent
    void setOrientationTile(Tiles tile);//Changer l'orientation du tile d'un ElementSerpent
    void setAttribut(int i, int j, Tiles tile);
	
private: 
	//Attributs
	int m_line, m_column;//Position ligne/colonne dans la grille de jeu
	Tiles m_tile; //orientation
};

#endif