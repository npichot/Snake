#include "Serpent.h"

//TODO definition de la classe
using namespace std;

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    ElementSerpent head = {5, 5, HEAD_EAST};
    m_posSerpent.push_back(head);
    
    //ElementSerpent m_head;//A quoi ca sert ?
    //ElementSerpent m_headFuture;//A quoi ca sert ?
    m_alive=true; 
}

Serpent::~Serpent()
{
   
}

vector<ElementSerpent> Serpent::deplacementSerpent()
{
	return m_posSerpent;
}

void Serpent::nextHead(Button entree) // Plus condition dans l'input empechant le serpent de revenir en arri�re
{

	switch (entree)
	{
	case UP:
		m_headFuture = ElementSerpent(m_head.getLine() + 1, m_head.getColumn(), HEAD_NORTH);
		break;
	case DOWN:
		m_headFuture = ElementSerpent(m_head.getLine() - 1, m_head.getColumn(), HEAD_SOUTH);
		break;
	case RIGHT:
		m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() + 1, HEAD_EAST);
		break;
	case LEFT:
		m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() - 1, HEAD_WEST);
		break;
	default: // S'il n'y a pas eu d'input, la prochaine position d�pend de l'orientation de la t�te
		switch (m_head.getOrientation())
		{
		case NORTH:
			m_headFuture = ElementSerpent(m_head.getLine() + 1, m_head.getColumn(), HEAD_NORTH);
			break;
		case SOUTH:
			m_headFuture = ElementSerpent(m_head.getLine() - 1, m_head.getColumn(), HEAD_SOUTH);
			break;
		case EAST:
			m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() + 1, HEAD_EAST);
			break;
		case LEFT:
			m_headFuture = ElementSerpent(m_head.getLine(), m_head.getColumn() - 1, HEAD_WEST);
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
		m_alive = false; // Les autres cas sont a priori des cas o� le serpent meurt
	}
}

ElementSerpent Serpent::getElement(int i) 
{
    ElementSerpent res;
    res = this->m_posSerpent[i];
    
    return res;
}