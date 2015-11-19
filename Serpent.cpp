#include "Serpent.h"

//TODO definition de la classe
using namespace std;
using namespace sf;

Serpent::Serpent()
	:alive(true)
{
}

Serpent::~Serpent()
{
}

void Serpent::deplacementSerpent(Serpent &serpent)
{
	m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la dernière position de la queue

	for (int i = serpent.sizeSerpent() - 1; i >= 2; --i)
		m_posSerpent[i] = m_posSerpent[i - 1];

	//Remplace la tête précédente par un élément corps
	if(m_posSerpent.size()>1)
		m_posSerpent[1] = { m_posSerpent[0].line, m_posSerpent[0].column, convertHeadtoBody.at(m_posSerpent[0].tile) };
}

void Serpent::deplacementTete(Serpent &serpent, Tiles head_tile)//Gre le dŽplacement de la tte
{
	switch (head_tile)
	{
	case HEAD_NORTH:
		*(serpent.getElement(0)) = { serpent.getElement(0)->line - 1, serpent.getElement(0)->column, HEAD_NORTH };
		break;
	case HEAD_EAST:
		*(serpent.getElement(0)) = { serpent.getElement(0)->line, serpent.getElement(0)->column + 1, HEAD_EAST };
		break;
	case HEAD_SOUTH:
		*(serpent.getElement(0)) = { serpent.getElement(0)->line + 1, serpent.getElement(0)->column, HEAD_SOUTH };
		break;
	case HEAD_WEST:
		*(serpent.getElement(0)) = { serpent.getElement(0)->line, serpent.getElement(0)->column - 1, HEAD_WEST };
		break;
	default:
		break;
	}

}

void Serpent::fruit_action(Map & map)//On dŽfinit l'action sur le serpent en fonction du fruit mangŽ
{
	Tiles fruit;
	fruit = map.getTile(m_posSerpent[0].line, m_posSerpent[0].column);
	switch (fruit) {
	case FRUIT:
		m_posSerpent.push_back(m_lastPosition);// On rajoute un élément Serpent à la dernière position de la queue pour allonger le Serpent
		map.popFruit();
		break;
	default:
		break;
	}
}

bool Serpent::getHead(Map map)
{
	for (int i = 0; i < map.getField().size(); ++i)
		for (int j = 0; j < map.getField()[i].size(); ++j)
			if (map.getTile(i, j) >= 20 && map.getTile(i, j) <= 23)
			{
				m_posSerpent.push_back({ i,j,map.getTile(i,j) });
				return true;
			}
	return false;
}

void Serpent::setAlive(Map & map)
{
	switch (map.getTile(m_posSerpent[0].line, m_posSerpent[0].column))
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