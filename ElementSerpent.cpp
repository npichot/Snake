#include "ElementSerpent.h"

using namespace std;

//TODO définition de la classe

ElementSerpent::ElementSerpent()   // Valeurs initiales à revoir
{
	m_line = 10;
	m_column = 10;
	m_orientation = EAST; // Utilisation de l'enum à revoir
}

ElementSerpent::~ElementSerpent()
{
}

ElementSerpent::ElementSerpent(int line, int column, Orientation orientation) : m_line(line), m_column(column), m_orientation(orientation)
{

}

int ElementSerpent::getLine() const
{
	return m_line;
}

int ElementSerpent::getColumn() const
{
	return m_column;
}

Orientation ElementSerpent::getOrientation() const
{
	return m_orientation;
}
