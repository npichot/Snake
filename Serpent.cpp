#include "Serpent.h"

//TODO definition de la classe

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    
}

Serpent::~Serpent()
{
    
}

void Serpent::nextPosition(Button entree) // Plus condition dans l'input empechant le serpent de revenir en arrière
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

void Serpent::guiderTete()
{
	
}

void Serpent::allongerQueue()
{

}

bool Serpent::isAlive(Map carte) const
{
	return true;
}