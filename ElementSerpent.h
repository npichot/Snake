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

class ElementSerpent { //Classe pour chaque �l�ment du serpent

	//M�thodes
public:
	ElementSerpent();
	~ElementSerpent();
	ElementSerpent(int line, int column, Tiles tile);
	int getLine() const;
	int getColumn() const;
	Tiles getOrientation() const;
	
private: 
	//Attributs
	int m_line, m_column;//Position ligne/colonne dans la grille de jeu
	Tiles m_tile; //orientation
};

#endif