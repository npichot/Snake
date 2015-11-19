#include "Menu.h"

using namespace std;
using namespace sf;


Menu::Menu(RenderWindow & window, MenuType mt) 
	:window(window), menuType(mt)
{
	//Chargement des items
	switch (mt)
	{
	case MAIN:
		items.push_back("Play");
		items.push_back("Create Map");
		items.push_back("How to play");
		items.push_back("Quit");
		break;
	case MAP:
	{
		ifstream is("MapConfig/list.txt");
		if (!is)
		{
			cout << "Fichier introuvable : MapConfig/list.txt" << endl;
		}
		string it;

		//On lit les lignes une par une 
		while (is >> it)
		{
			items.push_back(it);
		}

		// close the opened file.
		is.close();
		items.push_back("Return");
		break;
	}
	default:
		break;
	}

	//Chargement de la police
	font.loadFromFile("Police/arial.ttf");

	//on initialise le curseur
	curseur = 0;
}

Menu::~Menu()
{
}

void Menu::drawMenu()
{
	window.clear(Color(175,182,55,255));
	int margin = 20;
	int characterSize = (items.size()*(margin + 50) - margin) < (window.getSize().y - 150) ? 50 : (window.getSize().y - 150 - margin * (items.size() - 1)) / items.size();
		
	for (int i = 0; i < items.size(); ++i)
	{
		
		Text text;
		text.setFont(font); // choix de la police a utiliser ; font est un sf::Font
		text.setString(items[i]);// choix de la chaine de caracteres a afficher
		text.setCharacterSize(characterSize); // choix de la taille des caracteres exprimee en pixels, pas en points !
		(curseur==i) ? text.setColor(sf::Color::Red): text.setColor(sf::Color::White);// choix de la couleur du texte
		//Centrer le texte sur la fenetre
		FloatRect fr = text.getLocalBounds();
		text.setPosition((window.getSize().x - fr.width) / 2, (window.getSize().y - (margin + characterSize)*items.size() + margin) / 2 + (margin + characterSize) * i); //chaque element a une hauteur de 50 et on laisse 100 entre chaque element
		window.draw(text);
	}

	if (menuType == MAP)
	{
		Text text;
		text.setFont(font); // choix de la police a utiliser ; font est un sf::Font
		text.setString("( Choose your map : )");// choix de la chaine de caracteres a afficher
		text.setCharacterSize(25); // choix de la taille des caracteres exprimee en pixels, pas en points !
		text.setColor(sf::Color::White);// choix de la couleur du texte
										//Centrer le texte en bas de la fenetre
		FloatRect fr = text.getLocalBounds();
		text.setPosition((window.getSize().x - fr.width) / 2, 25); //On laisse un marge de 25 en bas
		window.draw(text);
	}

	Text text;
	text.setFont(font); // choix de la police a utiliser ; font est un sf::Font
	text.setString("( Use arrows to navigate in the menu and press Enter to validate )");// choix de la chaine de caracteres a afficher
	text.setCharacterSize(25); // choix de la taille des caracteres exprimee en pixels, pas en points !
	text.setColor(sf::Color::White);// choix de la couleur du texte
	//Centrer le texte en bas de la fenetre
	FloatRect fr = text.getLocalBounds();
	text.setPosition((window.getSize().x - fr.width) / 2, (window.getSize().y - 50)); //On laisse un marge de 25 en bas
	window.draw(text);

	
}

int Menu::getMenuChoice()
{
	int result = items.size();
	drawMenu();
	window.display();
	while (result == items.size())
	{
		Event event;
		while (window.pollEvent(event))// on capte les evenements
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				result = curseur;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
				(curseur == 0) ? curseur = items.size() - 1 : curseur--;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
				(curseur == items.size() - 1) ? curseur = 0 : curseur++;

			drawMenu();
			window.display();
		}
	}
	return result;
}

string Menu::loadMap()
{
	int choice = getMenuChoice();

	if (choice == items.size() - 1)
		return "";
	else
		return "MapConfig/" + items[choice] + ".dat";
}
