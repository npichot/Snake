#include "Serpent.h"

//TODO definition de la classe
using namespace std;

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    ElementSerpent body = {5, 5, EAST};
    m_posSerpent.push_back(body);
    
    Head m_head;
    Head m_headFuture; // Rajouter des commentaires
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
		m_headFuture = Head(m_head.getLine() + 1, m_head.getColumn(), NORTH);
		break;
	case DOWN:
		m_headFuture = Head(m_head.getLine() - 1, m_head.getColumn(), SOUTH);
		break;
	case EAST:
		m_headFuture = Head(m_head.getLine(), m_head.getColumn() + 1, EAST);
		break;
	case WEST:
		m_headFuture = Head(m_head.getLine(), m_head.getColumn() - 1, WEST);
		break;
	}
}

void Serpent::allongerQueue()
{

}

bool Serpent::isAlive(Map carte)
{
	return true;
}