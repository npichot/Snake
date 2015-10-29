#include "Menu.h"

using namespace std;
using namespace sf;


Menu::Menu(RenderWindow & window) 
	:window(window)
{
	//Chargement des items
	items.push_back("Play");
	items.push_back("Create Map");
	items.push_back("How to play");
	items.push_back("Quit");

	//Chargement de la police
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}

	//on initialise le curseur
	curseur = 0;
}

Menu::~Menu()
{
}

void Menu::drawMenu()
{
	window.clear(Color(175,182,55,255));
	
	for (int i = 0; i < items.size(); ++i)
	{
		
		Text text;
		text.setFont(font); // choix de la police a utiliser ; font est un sf::Font
		text.setString(items[i]);// choix de la chaine de caracteres a afficher
		text.setCharacterSize(50); // choix de la taille des caracteres exprimee en pixels, pas en points !
		(curseur==i) ? text.setColor(sf::Color::Red): text.setColor(sf::Color::White);// choix de la couleur du texte
		//Centrer le texte sur la fenetre
		FloatRect fr = text.getLocalBounds();
		text.setPosition((window.getSize().x - fr.width) / 2, (window.getSize().y -100*items.size()+50)/2+100* i); //chaque element a une hauteur de 50 et on laisse 100 entre chaque element
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

MenuChoice Menu::getMenuChoice()
{
	MenuChoice mc = NONE;
	while (mc == NONE)
	{
		Event event;
		while (window.pollEvent(event))// on capte les evenements
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				mc = static_cast<MenuChoice>(curseur);
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
				(curseur == 0) ? curseur = items.size() - 1 : curseur--;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
				(curseur == items.size() - 1) ? curseur = 0 : curseur++;

			drawMenu();
			window.display();
		}
	}
	return mc;
}
