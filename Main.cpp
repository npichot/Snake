#include "Main.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

int main()
{
	// Chargement de la fenetre
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Snake", Style::None);//For debug purpose
    window.setFramerateLimit(10);//Gere le nombre de FPS
	
	Menu menu(window,MAIN);

	//Ouverture du fichier de highscore
	int highScore = 0;
	ifstream lectureScore("Highscore.txt");  //Ouverture d'un fichier en lecture

	if (lectureScore) // Si le fichier a bien été ouvert, et qu'il existe donc
	{
		lectureScore >> highScore;
	}
	lectureScore.close();


	//Lancement de la boucle principale
	while (window.isOpen())
	{
		//Gestion du menu
		switch (menu.getMenuChoice())
		{
		case PLAY:
		{
			play(window, highscore);
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

void play(RenderWindow & window, int highscore)
{
	int score(0); // On initialise le score
	bool pause = false;

	Menu mapMenu(window,MAP);

	string pathMap = mapMenu.loadMap();
	if (pathMap == "")
		return;
	Map map = Map(pathMap, window, false);
	

	Serpent serpent;
	if (!serpent.setHead(*map.clone(map, window, false)))
	{
		cout << "Erreur pas de tÃªte trouvÃ©e sur la map" << endl;
		return;
	}
	Tiles head_tile = serpent.getHead();
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
			serpent.run(map, head_tile);
		
		////////////////////
		//dessin de la map//
		////////////////////
		window.clear();
		map.drawField(window);
		if (!serpent.isAlive() || pause)
		{
			Font font;
			font.loadFromFile("Police/arial.ttf");
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
	
	if (score > highScore)
	{
		ofstream ecritureScore("Highscore.txt", ofstream::trunc);  //Ouverture du fichier, et suppression de la ligne existante

		if (ecritureScore) // Si le fichier a bien été ouvert, et qu'il existe donc
		{
			ecritureScore << score; // Le score actuel devient le nouveau highscore
		}
		ecritureScore.close();
	}
}
