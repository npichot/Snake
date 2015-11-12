#include "Main.h"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
	// Chargement de la fenetre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
    window.setFramerateLimit(10);//Gere le nombre de FPS
	
	Menu menu(window);

	//Lancement de la boucle principale
	while (window.isOpen())
	{
		//Gestion du menu
		switch (menu.getMenuChoice())
		{
		case PLAY:
			play(window);
			break;
		}
	}
	return 0;
}

void play(RenderWindow & window)
{
    //Initialisation du serpent

    Serpent serpent;
    Tiles head_tile = serpent.getElement(0)->gettile();

	Map map("MapConfig/Config1.dat", window);
	map.popFruit();

	while (window.isOpen())
	{    
		////////////////////////////////
        //Controle des inputs claviers//
		////////////////////////////////
        Event event;
        while (window.pollEvent(event)) 
		{
            switch (event.key.code)
            {
                case Keyboard::Up:
					if (head_tile != HEAD_SOUTH)
					{
						head_tile = HEAD_NORTH;
						break;
					}
					break;
				case Keyboard::Right:
					if (head_tile != HEAD_WEST)
					{
						head_tile = HEAD_EAST;
						break;
					}
					break;
				case Keyboard::Left:
					if (head_tile != HEAD_EAST)
					{
						head_tile = HEAD_WEST;
						break;
					}
					break;
				case Keyboard::Down:
					if (head_tile != HEAD_NORTH)
					{
						head_tile = HEAD_SOUTH;
						break;
					}
					break;

                case Keyboard::Escape:
                    window.close();
					break;
				case Keyboard::Return:
					if (!serpent.isAlive())
						return;
                default:
                    break;
            }
        }

		
		

		//////////////
		//Traitement//
		//////////////
		if (!serpent.isAlive())//On attend le retour au menu par enter
			continue;

		map.updateField(serpent.getElement(serpent.sizeSerpent() - 1)->getLine(), serpent.getElement(serpent.sizeSerpent() - 1)->getColumn(), EMPTY);//Suppression du derniere element sur la map avant deplacement
		serpent.deplacementSerpent(serpent);
		serpent.deplacementTete(serpent, head_tile);
		serpent.setAlive(map);

		for (int i = 0; i < serpent.sizeSerpent(); ++i)
		{
			map.updateField(serpent.getElement(i)->getLine(), serpent.getElement(i)->getColumn(), serpent.getElement(i)->gettile());
		}
		
		////////////////////
		//dessin de la map//
		////////////////////
		window.clear();
		map.drawField();
		if (!serpent.isAlive())
		{
			Font font;
			if (!font.loadFromFile("Police/arial.ttf"))
			{
				// TODO erreur...
			}
			Text gameOver;
			gameOver.setFont(font);
			gameOver.setString("GAME OVER");
			gameOver.setCharacterSize(80);
			gameOver.setColor(Color::White);
			FloatRect fr = gameOver.getLocalBounds();
			gameOver.setOrigin(fr.width/ 2, fr.height / 2);
			gameOver.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
			window.draw(gameOver);
		}
		window.display();
	}
	
}
