#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "SFML/Graphics.hpp"
#include <iostream>;

#ifdef _WIN32
	#include <Windows.h>
	#include <strsafe.h>;
#else
	#include<dirent.h>
#endif

enum MenuChoice
{
	PLAY = 0,
	CREATION = 1,
	HOWTO = 2,
	QUIT = 3,
	NONE = 4,
};

enum MenuType
{
	MAIN,
	MAP,
};

class Menu
{
public:
	Menu(sf::RenderWindow & window, MenuType mt);
	~Menu();
	int getMenuChoice();
	std::string loadMap();

private:
	sf::RenderWindow & window; 
	std::vector<std::string> items;
	int curseur;
	sf::Font font;
	MenuType menuType;

	void drawMenu();
};

#endif // __MENU_H_INCLUDED__