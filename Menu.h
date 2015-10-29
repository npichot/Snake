#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "SFML/Graphics.hpp"

enum MenuChoice
{
	PLAY,
	MAPCREATION,
	HOWTO,
	QUIT,
	NONE,
};

class Menu
{
public:
	/*
	Initialisation du menu avec le remplissage de items
	*/
	Menu(sf::RenderWindow & window);
	~Menu();
	/*
	Retourne le choix de l'utilisateur dans le menu 
	*/
	MenuChoice getMenuChoice();
private:
	sf::RenderWindow & window; // reference sur la fenetre active dans laquelle le menu est dessine
	std::vector<std::string> items; // Liste des elements du menu
	int curseur;// determine l'element du menu qui est selectionner
	sf::Font font; //Police du menu

	/*
	Dessine le menu
	*/
	void drawMenu();
};

#endif // __MENU_H_INCLUDED__