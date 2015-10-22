#ifndef __HEAD_H_INCLUDED__
#define __HEAD_H_INCLUDED__

enum Orientation;

class Head { //Classe pour la tête du serpent

	//Méthodes
	Head();
	~Head();
	Head(int line, int column, Orientation orientation);
	int getLine() const;
	int getColumn() const;
	Orientation getOrientation();
	

	//Attributs
	int m_line, m_column;//Position ligne/colonne dans la grille de jeu
	Orientation m_orientation; //orientation
};

#endif