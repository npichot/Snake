#include "Main.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;


int highScore(0);

int main()
{
	// Chargement de la fenetre
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Snake", Style::None);//For debug purpose
    window.setFramerateLimit(10);//Gere le nombre de FPS
	
	Menu menu(window,MAIN);

	//Ouverture du fichier de highscore
	highScore = 0;
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

void play(RenderWindow & window)
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
