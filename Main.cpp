#include "Main.h"

using namespace std;
using namespace sf;

int main()
{
	// Chargement de la fenetre
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Snake");
    window.setFramerateLimit(10);//Gere le nombre de FPS
	
	Menu menu(window,MAIN);

	//Lancement de la boucle principale
	while (window.isOpen())
	{
		//Gestion du menu
		switch (menu.getMenuChoice())
		{
		case PLAY:
		{
			play(window);
			break;
		}
		case CREATION:
		{
			MapCreation mc;
			Map emptyMap("", window, true);
			mc.executeInterface(window,emptyMap);
			break;
		}
		case QUIT:
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

void play(RenderWindow & window)
{
	bool pause = false;

    Serpent serpent;
    Tiles head_tile = serpent.getElement(0)->tile;

	Menu mapMenu(window,MAP);

	string pathMap = mapMenu.loadMap();
	if (pathMap == "")
		return;
	Map map = Map(pathMap, window, false);
	map.popFruit();

	while (window.isOpen())
	{    
		////////////////////////////////
        //Controle des inputs claviers//
		////////////////////////////////
        Event event;
        while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case Keyboard::Up:
					if (head_tile != HEAD_SOUTH && !pause)
					{
						head_tile = HEAD_NORTH;
					}
					break;
				case Keyboard::Right:
					if (head_tile != HEAD_WEST && !pause)
					{
						head_tile = HEAD_EAST;
					}
					break;
				case Keyboard::Left:
					if (head_tile != HEAD_EAST && !pause)
					{
						head_tile = HEAD_WEST;
					}
					break;
				case Keyboard::Down:
					if (head_tile != HEAD_NORTH && !pause)
					{
						head_tile = HEAD_SOUTH;
					}
					break;

				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::Return:
					if (!serpent.isAlive())
						return;
					break;
				case Keyboard::Space:
					pause = !pause;
					break;
				default:
					break;
				}
				break;// Autoriser qu'une prise de touche à la fois
			}
        }

		//////////////
		//Traitement//
		//////////////
		if (!serpent.isAlive())//On attend le retour au menu par enter
			continue;

		if (!pause)
		{
			map.updateField(serpent.getElement(serpent.sizeSerpent() - 1)->line, serpent.getElement(serpent.sizeSerpent() - 1)->column, EMPTY);//Suppression du derniere element sur la map avant deplacement
			serpent.deplacementSerpent(serpent);
			serpent.deplacementTete(serpent, head_tile);
			serpent.setAlive(map);
            serpent.fruit_action(map);

			for (int i = 0; i < serpent.sizeSerpent(); ++i)
			{
				map.updateField(serpent.getElement(i)->line, serpent.getElement(i)->column, serpent.getElement(i)->tile);
			}
		}
		
		////////////////////
		//dessin de la map//
		////////////////////
		window.clear();
		map.drawField(window);
		if (!serpent.isAlive() || pause)
		{
			Font font;
			if (!font.loadFromFile("Police/arial.ttf"))
			{
				// TODO erreur...
			}
			Text additionnalText;
			additionnalText.setFont(font);
			if (!pause)
				additionnalText.setString("GAME OVER");
			else
				additionnalText.setString("PAUSE");
			additionnalText.setCharacterSize(80);
			additionnalText.setColor(Color::White);
			FloatRect fr = additionnalText.getLocalBounds();
			additionnalText.setOrigin(fr.width / 2, fr.height / 2);
			additionnalText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			window.draw(additionnalText);
		}
		window.display();
	}
}