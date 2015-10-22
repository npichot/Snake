#include "Head.h"

using namespace std;

//TODO définition de la classe

Head::Head()   // Valeurs initiales à revoir
{
	m_line = 10;
	m_column = 10;
	m_orientation = EAST; // Utilisation de l'enum à revoir
}

Head::~Head()
{
}

Head::Head(int line, int column, Orientation orientation) : m_line(line), m_column(column), m_orientation(orientation)
{

}

int Head::getLine() const
{
	return m_line;
}

int Head::getColumn() const
{
	return m_column;
}

Orientation Head::getOrientation()
{
	return m_orientation;
}
