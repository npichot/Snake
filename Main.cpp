#include "Main.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;


int highScore(0);

/*
Fonction principale du programme qui definit la fenêtre et 
lance le menu principale.
A partir du choix de l'utilisateur dans le menu, diverses action sont lancées
*/
int main()
{
	// Chargement de la fenetre
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Snake", Style::None);//For debug purpose
    window.setFramerateLimit(10);//Gere le nombre de FPS
	
	Menu menu(window,MAIN);

	//Ouverture du fichier de highscore
	highScore = 0;
	ifstream lectureScore("Highscore.txt"); 

	if (lectureScore) 
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
			play(window);
			break;
		}
        case HOWTO:
            displayHowTo(window);
            break;
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

/*
Cette fonction est au centre du jeu et permet de jouer au snake.
Les différents éléments du jeu comme le serpent et son affichage
sont manipulés dans cette fonction.
Après une initialisation, on rentre dans une boucle de jeu découpé en trois étapes :
- Acquisition des commandes
- Traitement
- Affichage
Enfin on sauve le higscore
*/
void play(RenderWindow & window)
{
	int score(0); 
	bool pause = false;
	bool robotOn = false;

	Menu mapMenu(window,MAP);

	string pathMap = mapMenu.loadMap();
	if (pathMap == "")
		return;
	Map map = Map(pathMap, window, false);
	map.popFruit();
	Map copie = *map.clone(map, window, false);

	Serpent serpent(true);
	if (!serpent.setHead(copie, false))
	{
		cout << "Erreur pas de tete trouvee sur la map" << endl;
		return;
	}

	Tiles head_tile = serpent.getHead();
	Serpent serpentBot(false);
	if (!serpentBot.setHead(copie, true))
	{
		cout << "Impossible de placer le bot" << endl;
		return;
	}

	while (window.isOpen())
	{    
		////////////////////////////////
        //Controle des inputs claviers//
		////////////////////////////////
        Event event;
        while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyReleased){
				switch (event.key.code){
                    case Keyboard::Up:
                        if (head_tile != HEAD_SOUTH && !pause && !serpent.isreverse())
                            head_tile = HEAD_NORTH;
                        else if (head_tile != HEAD_NORTH  && !pause && serpent.isreverse())
                            head_tile = HEAD_SOUTH;
                        break;
                    case Keyboard::Right:
                        if (head_tile != HEAD_WEST && !pause && !serpent.isreverse())
                            head_tile = HEAD_EAST;
                        else if (head_tile != HEAD_EAST  && !pause && serpent.isreverse())
                            head_tile = HEAD_WEST;
                        break;
                    case Keyboard::Left:
                        if (head_tile != HEAD_EAST && !pause && !serpent.isreverse())
                            head_tile = HEAD_WEST;
                        else if (head_tile != HEAD_WEST  && !pause && serpent.isreverse())
                            head_tile = HEAD_EAST;
                        break;
                    case Keyboard::Down:
                        if (head_tile != HEAD_NORTH && !pause && !serpent.isreverse())
                            head_tile = HEAD_SOUTH;
                        else if (head_tile != HEAD_SOUTH  && !pause && serpent.isreverse())
                            head_tile = HEAD_NORTH;
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
		if (!serpent.isAlive())
			continue;

		if (!pause)
		{
			if(!robotOn)
				serpent.run(map, head_tile,serpentBot, *map.clone(map, window, false));
			else
			{
				serpent.run(map, head_tile);
				serpentBot.runBot(map);
			}

			robotOn = serpentBot.isAlive();
		}
		
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
		ofstream ecritureScore("Highscore.txt", ofstream::trunc); 

		if (ecritureScore) 
		{
			ecritureScore << score; 
		}
		ecritureScore.close();
	}
}

/*
Fonction qui permet d'afficher les instructions du jeu.
*/
void displayHowTo(RenderWindow & window)
{
    Texture image;
    image.loadFromFile("Ressources/howtoplay.png");
    Sprite s;
    s.setTexture(image);
    s.setPosition(0, 0);
    while (window.isOpen()) {
        window.clear();
        window.draw(s);
        window.display();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed){
                play(window);
                return;
            }
        }
    }
}
