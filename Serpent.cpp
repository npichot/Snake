#include "Serpent.h"

//TODO definition de la classe

Serpent::Serpent()
{
    
}

Serpent::~Serpent()
{
    
}

void Serpent::nextPosition(Input input) // Plus condition dans l'input empechant le serpent de revenir en arrière
{

	switch (input)
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

bool Serpent::estVivant() 
{
	return true;
}