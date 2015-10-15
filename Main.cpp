#include "Main.h"

using namespace std;

int main()
{
	// Chargement de la fenêtre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
	Map map;

	//Error
	map.updateField(-1, 2, HEAD_WEST);
	map.updateField(100, 3, BODY_WEST);
	map.updateField(10, -5, BODY_WEST);
	map.updateField(11, 40, BODY_NORTH);

	//Lancement de la boucle principale
	while (window.isOpen())
	{
		//Controle des inputs claviers 

		//Mise à jour du serpent 

		//Gestion des actions

		//Test de l'affichage
		map.updateField(0, 0, BUSHES);
		map.updateField(3, 6, FRUIT);
		map.updateField(10, 2, HEAD_WEST);
		map.updateField(10, 3, BODY_WEST);
		map.updateField(10, 4, BODY_WEST);
		map.updateField(11, 4, BODY_NORTH);

		//dessin de la map 
		window.clear();
		map.drawField(&window);

		//Affichage
		window.display();
	}
	
	return 0;
}