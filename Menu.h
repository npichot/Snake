#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "SFML\Graphics.hpp"
#include <Windows.h>
#include <iostream>;
#include <strsafe.h>;

enum MenuChoice
{
	PLAY=0,
	CREATION=1,
	HOWTO=2,
	QUIT=3,
	NONE=4,
};

enum MenuType
{
	MAIN,
	MAP,
};

class Menu
{
public:
	/*
	Initialisation du menu avec le remplissage de items
	*/
	Menu(sf::RenderWindow & window, MenuType mt);
	~Menu();
	/*
	Retourne le choix de l'utilisateur dans le menu 
	*/
	int getMenuChoice();
	std::string loadMap();
private:
	sf::RenderWindow & window; // reference sur la fenetre active dans laquelle le menu est dessine
	std::vector<std::string> items; // Liste des elements du menu
	int curseur;// determine l'element du menu qui est selectionner
	sf::Font font; //Police du menu
	MenuType menuType;

	/*
	Dessine le menu
	*/
	void drawMenu();
};

#endif // __MENU_H_INCLUDED__