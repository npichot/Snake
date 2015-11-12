#include "Serpent.h"

//TODO definition de la classe
using namespace std;
using namespace sf;

Serpent::Serpent() 
{
    ElementSerpent head = {5, 4, HEAD_EAST};
    m_posSerpent.push_back(head);
    ElementSerpent body = {5, 3, BODY_EAST};
    m_posSerpent.push_back(body);
    ElementSerpent body2 = {5, 2, BODY_EAST};
    m_posSerpent.push_back(body2);
    ElementSerpent body3 = {5,1,BODY_EAST};
    m_posSerpent.push_back(body3);

   
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
		m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la derni�re position de la queue
        m_posSerpent[i]=m_posSerpent[i-1];
    }

	//Remplace la t�te pr�c�dente par un �l�ment corps
    m_posSerpent[1].setAttribut(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn(), convertHeadtoBody.at(m_posSerpent[0].gettile()));
    
}

void Serpent::deplacementTete(Serpent &serpent, Tiles head_tile)//G�re le d�placement de la t�te
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


void Serpent::allongerQueue()
{
	m_posSerpent.push_back(m_lastPosition); // On rajoute un �l�ment Serpent � la derni�re position de la queue pour allonger le Serpent
}

void Serpent::isAlive(Map & map)
{
	int i, j;
	Tiles element;
	element = map.getTile(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn());
	switch (element)
	{
	
	case BODY_NORTH:
	case BODY_EAST:
	case BODY_SOUTH:
	case BODY_WEST:
	case TREE:
		m_alive = false;
		break;
	case FRUIT:
		allongerQueue();
		map.popFruit();
		break;
	default:
		break;
		 
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