#include "Main.h"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
	// Chargement de la fenetre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
	
	Menu menu(window);

	//Lancement de la boucle principale
	if (window.isOpen())
	{
		//Gestion du menu
		switch (menu.getMenuChoice())
		{
		case PLAY:
			play(window);
		}
	}
	return 0;
}

void play(RenderWindow & window)
{
    //Initialisation du serpent
        Serpent serpent;
	while (window.isOpen())
	{
		Map map("MapConfig/Config1.dat",window);
        for (int i = 0 ; i < serpent.sizeSerpent(); ++i)
        {
        map.updateField(serpent.getElement(i)->getLine(), serpent.getElement(i)->getColumn(), serpent.getElement(i)->gettile());
        }
        cout << serpent.getElement(0)->getLine() << endl;
        serpent.deplacementSerpent(serpent);
        //serpent.getElement(0)->setColumn(serpent.getElement(0)->getColumn()+1);
        //serpent.deplacementTete(serpent);
        
        //Controle des inputs claviers
        Event event;
        while (window.pollEvent(event)) {
            switch (event.key.code)
            {
                case Keyboard::Up:
                    serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine()-1, serpent.getElement(0)->getColumn(), HEAD_NORTH);
                    break;
                case Keyboard::Right:
                    serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine(), serpent.getElement(0)->getColumn()+1, HEAD_EAST);
                    break;
                case Keyboard::Down:
                    serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine()+1, serpent.getElement(0)->getColumn(), HEAD_SOUTH);
                    break;
                case Keyboard::Left:
                    serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine(), serpent.getElement(0)->getColumn()-1, HEAD_WEST);
                    break;
                default:
                    break;
            }
        }
            /*if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Up)
            {
                serpent.getElement(0)->setAttribut(serpent.getElement(0)->getLine()-1, serpent.getElement(0)->getColumn(), HEAD_NORTH);
            }}
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
        }*/
            serpent.deplacementTete(serpent);
		//Mise a jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField();
		window.display();
        sleep(Time(milliseconds(200)));
	}
}
