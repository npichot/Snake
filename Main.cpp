#include "Main.h"

using namespace std;

int main()
{
	// Chargement de la fenêtre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
	Map map;

	//Lancement de la boucle principale
	while (window.isOpen())
	{
		//Controle des inputs claviers 

		//Mise à jour du serpent 

		//Gestion des actions

		//dessin de la map 
		window.clear();
		map.drawField(&window);

		//Affichage
		window.display();
	}
	
	return 0;
}