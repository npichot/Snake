#ifndef __HEAD_H_INCLUDED__
#define __HEAD_H_INCLUDED__

enum Orientation //Pour la tete du serpent
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

class Head { //Classe pour la tête du serpent

	//Méthodes
public:
	Head();
	~Head();
	Head(int line, int column, Orientation orientation);
	int getLine() const;
	int getColumn() const;
	Orientation getOrientation() const;
	
private:
	//Attributs
	int m_line, m_column;//Position ligne/colonne dans la grille de jeu
	Orientation m_orientation; //orientation
};

#endif