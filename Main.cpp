#include "Main.h"

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

	while (window.isOpen())
	{
		Map map("MapConfig/Config1.dat",window);
        Serpent serpent;
        map.updateField(serpent.getElement(0).getLine(), serpent.getElement(0).getColumn(), HEAD_EAST);
		//Controle des inputs claviers 

		//Mise a jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField();
		window.display();
	}
}