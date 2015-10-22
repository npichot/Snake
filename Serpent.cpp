#include "Serpent.h"

//TODO definition de la classe
using namespace std;

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    elementSerpent body = {5, 5, EAST};
    m_posSerpent.push_back(body);
    
    Head m_head;
    Head m_headFuture; // Rajouter des commentaires
    bool m_alive;
}

Serpent::~Serpent()
{
   
}

vector<elementSerpent> Serpent::deplacementSerpent()
{
    
}

void Serpent::nextHead(Button entree) // Plus condition dans l'input empechant le serpent de revenir en arrière
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