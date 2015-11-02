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
 /*   Event event;
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
        m_posSerpent[0].m_tile
   */
    for (int i = serpent.sizeSerpent()-1; i >= 2; --i)
    {
        m_posSerpent[i]=m_posSerpent[i-1];
    }
    m_posSerpent[1].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn(), convertHeadtoBody.at(m_posSerpent[0].gettile()));
    
}

void Serpent::deplacementTete(Serpent &serpent)
{
    /*Event event;
    if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Up)
    {
        m_posSerpent[0].setAttribut(m_posSerpent[0].getLine()-1, m_posSerpent[0].getColumn(), HEAD_NORTH);
    }
    else if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Right)
    {
        m_posSerpent[0].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn()+1, HEAD_EAST);
    }
    else if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Down)
    {
        m_posSerpent[0].setAttribut(m_posSerpent[0].getLine()+1, m_posSerpent[0].getColumn(), HEAD_SOUTH);
    }
    else if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Left)
    {
        m_posSerpent[0].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn()-1, HEAD_WEST);
    }
    else
    {*/
        if (m_posSerpent[0].gettile() == HEAD_NORTH)
        {
            m_posSerpent[0].setAttribut(m_posSerpent[0].getLine()-1, m_posSerpent[0].getColumn(), HEAD_NORTH);
        }
        
        else if (m_posSerpent[0].gettile() == HEAD_EAST)
        {
            m_posSerpent[0].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn()+1, HEAD_EAST);
        }
        
         else if (m_posSerpent[0].gettile() == HEAD_SOUTH)
        {
            m_posSerpent[0].setAttribut(m_posSerpent[0].getLine()+1, m_posSerpent[0].getColumn(), HEAD_SOUTH);
        }
        
        else
        {
            m_posSerpent[0].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn()-1, HEAD_WEST);
        }
    }
    
    
//}

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
    /*ElementSerpent res;
    res = this->m_posSerpent[i];
    */
    return &m_posSerpent[i];
}

int Serpent::sizeSerpent()
{
    return m_posSerpent.size();
}