#include "Serpent.h"

//TODO definition de la classe
using namespace std;
using namespace sf;

Serpent::Serpent() 
	:alive(true)
{
	m_posSerpent.push_back(ElementSerpent(5, 4, HEAD_EAST));
	m_posSerpent.push_back(ElementSerpent(5, 3, BODY_EAST));
	m_posSerpent.push_back(ElementSerpent(5, 2, BODY_EAST));
	m_posSerpent.push_back(ElementSerpent(5, 1, BODY_EAST));
}

Serpent::~Serpent()
{
}

void Serpent::deplacementSerpent(Serpent &serpent)
{
	m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la dernière position de la queue

    for (int i = serpent.sizeSerpent()-1; i >= 2; --i)
        m_posSerpent[i]=m_posSerpent[i-1];

	//Remplace la tête précédente par un élément corps
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

void Serpent::fruit_action(Map & map)//On dŽfinit l'action sur le serpent en fonction du fruit mangŽ
{
    Tiles fruit;
    fruit = map.getTile(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn());
    switch (fruit) {
        case FRUIT:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un élément Serpent à la dernière position de la queue pour allonger le Serpent
            map.popFruit();
            break;
        default:
            break;
    }
}

void Serpent::setAlive(Map & map)
{
	switch (map.getTile(m_posSerpent[0].getLine(), m_posSerpent[0].getColumn()))
	{
		case BODY_NORTH:
		case BODY_EAST:
		case BODY_SOUTH:
		case BODY_WEST:
		case TREE:
			alive = false;
			break;
		default:
			break;
	}
}
