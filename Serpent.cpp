#include "Serpent.h"

//TODO definition de la classe
using namespace std;
using namespace sf;

Serpent::Serpent() // Ne pas oublier d'initialiser le vector
{
    ElementSerpent head = {5, 4, HEAD_EAST};
    m_posSerpent.push_back(head);
    ElementSerpent body = {5, 3, BODY_EAST};
    m_posSerpent.push_back(body);
    ElementSerpent body2 = {5, 2, BODY_EAST};
    m_posSerpent.push_back(body2);
    ElementSerpent body3 = {5,1,BODY_EAST};
    m_posSerpent.push_back(body3);

    
    ElementSerpent m_head;//A quoi ca sert ?
    ElementSerpent m_headFuture;//A quoi ca sert ?
	ElementSerpent m_lastPosition = m_posSerpent[m_posSerpent.size() - 1];
    m_alive=true; 
}

Serpent::~Serpent()
{
   
}

void Serpent::deplacementSerpent(Serpent &serpent)
{
    for (int i = serpent.sizeSerpent()-1; i >= 2; --i)
    {
		m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la dernière position de la queue
        m_posSerpent[i]=m_posSerpent[i-1];
    }
    m_posSerpent[1].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn(), convertHeadtoBody.at(m_posSerpent[0].gettile()));
    
}

void Serpent::deplacementTete(Serpent &serpent, Tiles head_tile)//Gre le dŽplacement de la tte
{
    switch (head_tile)
    {
        case HEAD_NORTH:
            serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine()-1, serpent.getElement(0)->getColumn(), HEAD_NORTH);
            break;
        case HEAD_EAST:
            serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine(), serpent.getElement(0)->getColumn()+1, HEAD_EAST);
            break;
        case HEAD_SOUTH:
            serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine()+1, serpent.getElement(0)->getColumn(), HEAD_SOUTH);
            break;
        case HEAD_WEST:
            serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine(), serpent.getElement(0)->getColumn()-1, HEAD_WEST);
            break;
        default:
            break;
    }

}

void Serpent::nextHead(Button entree) // Plus condition dans l'input empechant le serpent de revenir en arrière
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
	default: // S'il n'y a pas eu d'input, la prochaine position dépend de l'orientation de la tête
		switch (m_head.gettile())
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
	m_posSerpent.push_back(m_lastPosition); // On rajoute un élément Serpent à la dernière position de la queue pour allonger le Serpent
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

ElementSerpent *Serpent::getElement(int i)
{
    return &m_posSerpent[i];
}

int Serpent::sizeSerpent()
{
    return m_posSerpent.size();
}

bool Serpent::getAlive() const
{
	return m_alive;
}