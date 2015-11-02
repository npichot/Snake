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
    m_alive=true; 
}

Serpent::~Serpent()
{
   
}

void Serpent::deplacementSerpent(Serpent &serpent)//A terminer
{
 /*   Event event;
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
        m_posSerpent[0].m_tile
   */
    int temp_line(0);
    int temp_column(0);
    Tiles temp_tile(HEAD_NORTH);
    
    for (int i = serpent.sizeSerpent()-1; i >= 0; --i)
    {
        //temp_line = serpent.getElement(i-1)->getLine();
        //serpent.getElement(i)->setLine(temp_line);
        temp_column = serpent.getElement(i)->getColumn();
        serpent.getElement(i+1)->setColumn(temp_column);
        //temp_tile = serpent.getElement(i-1)->gettile();
        //serpent.getElement(i)->setOrientationTile(temp_tile);
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