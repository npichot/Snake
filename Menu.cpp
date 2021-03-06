#include "Menu.h"

using namespace std;
using namespace sf;

/*
Initialisation du menu avec le remplissage de items en fonctions du type de menu.
Pour le menu map, on r�cup�re les fichiers dans le dossiers MapConfig.
L'implementation varie en fonction de l'OS (Windows ou Mac).
*/
Menu::Menu(RenderWindow & window, MenuType mt)
	:window(window), menuType(mt)
{
	//on initialise le curseur
	curseur = 0;


	//Chargement des items
	switch (mt)
	{
	case MAIN:
		items.push_back("Play");
		items.push_back("Create Map");
		items.push_back("How to play");
		items.push_back("Highscores");
		items.push_back("Quit");
		break;
	case MAP:
	{
#ifdef _WIN32
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		TCHAR szDir[MAX_PATH];
		HANDLE hFind = INVALID_HANDLE_VALUE;

		// Prepare string for use with FindFile functions.  First, copy the
		// string to a buffer, then append '\*' to the directory name.

		StringCchCopy(szDir, MAX_PATH, ".\\MapConfig");
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

		// Find the first file in the directory.

		hFind = FindFirstFile(szDir, &ffd);
		do
		{
			if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				string str = string(ffd.cFileName);
				string extension = ".dat";
				if (str.find(extension) != string::npos)
				{
					str.replace(str.find(extension), extension.length(), "");
					items.push_back(str);
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);
#else
		DIR *pDIR;
		struct dirent *entry;
		if (pDIR = opendir("./MapConfig")) {
			while (entry = readdir(pDIR)) {
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				{
					string str = string(entry->d_name);
					string extension = ".dat";
					if (str.find(extension) != string::npos)
					{
						str.replace(str.find(extension), extension.length(), "");
						items.push_back(str);
					}
				}
			}
			closedir(pDIR);
		}
#endif

		items.push_back("Return");
		break;
	}
	case HIGHSCORE:
	{
		Highscore hs;
		for (pair<string, int> p : hs.getScores())
		{
			items.push_back(p.first + " : " + to_string(p.second));
		}
		items.push_back("Return");
		curseur = items.size() - 1;
		break;
	}
	default:
		break;
	}

	//Chargement de la police
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}

	
}

Menu::~Menu()
{
}

/*
Dessine le menu dans la fen�tre
*/
void Menu::drawMenu()
{
	window.clear(Color(175, 182, 55, 255));
	int margin = 20;
	int characterSize = (items.size()*(margin + 50) - margin) < (window.getSize().y - 150) ? 50 : (window.getSize().y - 150 - margin * (items.size() - 1)) / items.size();

	for (int i = 0; i < items.size(); ++i)
	{

		Text text;
		text.setFont(font); // choix de la police a utiliser ; font est un sf::Font
		text.setString(items[i]);// choix de la chaine de caracteres a afficher
		text.setCharacterSize(characterSize); // choix de la taille des caracteres exprimee en pixels, pas en points !
		(curseur == i) ? text.setColor(sf::Color::Red) : text.setColor(sf::Color::White);// choix de la couleur du texte
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

/*
Retourne le choix de l'utilisateur dans le menu
*/
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
				(menuType == HIGHSCORE) ? curseur = items.size() - 1 : (curseur == 0) ? curseur = items.size() - 1 : curseur--;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
				(menuType == HIGHSCORE) ? curseur = items.size() - 1 : (curseur == items.size() - 1) ? curseur = 0 : curseur++;

			drawMenu();
			window.display();
		}
	}
	return result;
}

/*
Renvoie le nom du fichier associ� � la map s�lectionn� dans le menu 
de type MAP
*/
string Menu::loadMap()
{
	int choice = getMenuChoice();

	if (choice == items.size() - 1)
		return "";
	else
		return "MapConfig/" + items[choice] + ".dat";
}
