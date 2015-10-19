#pragma once
#include "Main.h"

typedef enum
{
	PLAY,
	HOWTO,
	QUIT,
	NONE,
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
	Retourne le choix de l'utilisateur dans le menu 
	*/
	MenuChoice getMenuChoice(RenderWindow & window);
private:
	vector<string> items; // Liste des �lements du menu
	int curseur;// determine l'�l�ment du menu qui est s�lectionner
	Font font; //Police du menu

	/*
	Dessine le menu
	*/
	void drawMenu(RenderWindow & window);
};

