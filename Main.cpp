#include "Main.h"

using namespace std;

int main()
{
	// Chargement de la fenetre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
	
	Menu menu;

	//Lancement de la boucle principale
	if (window.isOpen())
	{
		//Gestion du menu
		switch (menu.getMenuChoice(window))
		{
		case PLAY:
			play(window);
		}
	}
	return 0;
}

void play(RenderWindow & window)
{
	while (window.isOpen())
	{
		Map map("MapConfig/Config1.dat");
		//Controle des inputs claviers 

		//Mise a jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField(window);
		window.display();
	}
}