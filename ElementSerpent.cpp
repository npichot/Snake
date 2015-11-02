#include "ElementSerpent.h"

using namespace std;
using namespace sf;

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

void ElementSerpent::setLine(int i)
{
    m_line = i;
}

void ElementSerpent::setColumn(int i)
{
    m_column = i;
}

void ElementSerpent::setOrientationTile(Tiles tile)
{
    m_tile = tile;
}

void ElementSerpent::setAttribut(int i, int j, Tiles tile)
{
    m_line = i;
    m_column = j;
    m_tile = tile;
}