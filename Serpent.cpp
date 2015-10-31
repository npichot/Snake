#include "Serpent.h"

//TODO definition de la classe
using namespace std;

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    ElementSerpent body = {5, 5, EAST};
    m_posSerpent.push_back(body);
    
    ElementSerpent m_head;
    ElementSerpent m_headFuture; 
    m_alive=true; 
}

Serpent::~Serpent()
{
   
}

vector<ElementSerpent> Serpent::deplacementSerpent()
{
	return m_posSerpent;
}

void Serpent::nextHead(Button entree) // Plus condition dans l'input empechant le serpent de revenir en arrière
{

	switch (entree)
	{
	case UP:
		m_headFuture = ElementSerpent(m_head.getLine() + 1, m_head.getColumn(), NORTH);
		break;
	case DOWN:
		m_headFuture = ElementSerpent(m_head.getLine() - 1, m_head.getColumn(), SOUTH);
		break;
	case RIGHT:
		m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() + 1, EAST);
		break;
	case LEFT:
		m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() - 1, WEST);
		break;
	default: // S'il n'y a pas eu d'input, la prochaine position dépend de l'orientation de la tête
		switch (m_head.getOrientation())
		{
		case NORTH:
			m_headFuture = ElementSerpent(m_head.getLine() + 1, m_head.getColumn(), NORTH);
			break;
		case SOUTH:
			m_headFuture = ElementSerpent(m_head.getLine() - 1, m_head.getColumn(), SOUTH);
			break;
		case EAST:
			m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() + 1, EAST);
			break;
		case LEFT:
			m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() - 1, WEST);
			break;
		}
		break;
	}
}

void Serpent::allongerQueue()
{

}

void Serpent::isAlive(Map carte)
{
	Tiles element;
	element = carte.getTile(m_headFuture.getLine(), m_headFuture.getColumn());
	if (element == EMPTY)
	{
		m_alive = true; // S'il y a un fruit ou que la case est vide, m_alive reste true
	}
	else if (element == FRUIT)
	{
		allongerQueue(); //On allonge la queue du serpent s'il y a un fruit
		m_alive = true; //
	}
	else
	{
		m_alive = false; // Les autres cas sont a priori des cas où le serpent meurt
	}
}

ElementSerpent Serpent::getElement(int i)
{
    ElementSerpent res;
    res = this->m_posSerpent[i];
    
    return res;
}