#pragma once


typedef enum  //Pour la t�te du serpent
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}Orientation;

class Head { //Classe pour la t�te du serpent

	//M�thodes
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