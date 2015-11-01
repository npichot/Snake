#include "ElementSerpent.h"

using namespace std;

//TODO définition de la classe

ElementSerpent::ElementSerpent()
{
}

ElementSerpent::~ElementSerpent()
{
}

ElementSerpent::ElementSerpent(int line, int column, Tiles tile) : m_line(line), m_column(column), m_tile(tile)
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

Tiles ElementSerpent::gettile() const
{
	return m_tile;
}
