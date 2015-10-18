#pragma once
#include "SFML\Graphics.hpp"

using namespace std;
using namespace sf;

typedef enum
{
	PLAY,
	QUIT,
}MenuChoice;

class Menu
{
public:
	/*
	Initialisation du menu avec le remplissage de items
	*/
	Menu();
	~Menu();
	/*
	Dessine le menu
	*/
	void drawMenu(RenderWindow & window);
	/*
	Retourne le choix de l'utilisateur dans le menu 
	*/
	MenuChoice getMenuChoice();
private:
	vector<string> items; // Liste des élements du menu

};

