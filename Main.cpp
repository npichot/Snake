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
        serpent.getElement(0)->setLine(1);
        
        //Controle des inputs claviers
        //cout << serpent.getElement(0) << endl;
		//Mise a jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField();
		window.display();
        sleep(2);
	}
}