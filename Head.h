#ifndef __HEAD_H_INCLUDED__
#define __HEAD_H_INCLUDED__

enum Orientation //Pour l'orientation de chaque �l�ment
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
	ElementSerpent(int line, int column, Orientation orientation);
	int getLine() const;
	int getColumn() const;
	Orientation getOrientation() const;
	
private: 
	//Attributs
	int m_line, m_column;//Position ligne/colonne dans la grille de jeu
	Orientation m_orientation; //orientation
};

#endif