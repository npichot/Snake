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
    Tiles head_tile = serpent.getElement(0)->gettile();
    
    //Gestion des actions
	while (window.isOpen())
	{
		Map map("MapConfig/Config1.dat",window);
        for (int i = 0 ; i < serpent.sizeSerpent(); ++i)
        {
        map.updateField(serpent.getElement(i)->getLine(), serpent.getElement(i)->getColumn(), serpent.getElement(i)->gettile());
        }
        cout << serpent.getElement(0)->getLine() << endl;
        serpent.deplacementSerpent(serpent);

        
        //Controle des inputs claviers
        Event event;
        while (window.pollEvent(event)) {
            switch (event.key.code)
            {
                case Keyboard::Up:
                    head_tile = HEAD_NORTH;
                    break;
                case Keyboard::Right:
                    head_tile = HEAD_EAST;
                    break;
                case Keyboard::Down:
                    head_tile = HEAD_SOUTH;
                    break;
                case Keyboard::Left:
                    head_tile = HEAD_WEST;
                    break;
                case Keyboard::Escape:
                    window.close();
                default:
                    break;
            }
        }
        
        
        serpent.deplacementTete(serpent, head_tile);
        
            
		//Mise a jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField();
		window.display();
        
	}
}
