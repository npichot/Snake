#include "Serpent.h"

using namespace std;
using namespace sf;

Serpent::Serpent(bool alive)
	:alive(alive), reverse_input(false)
{
}

Serpent::~Serpent()
{
}

//Gestion du deplacement du corps du serpent
void Serpent::deplacementSerpent()
{
    //Chaque element du corps remplace l'element precedent
    for (int i = m_posSerpent.size() - 1; i >= 2; --i)
		m_posSerpent[i] = m_posSerpent[i - 1];

	//Remplace la t�te pr�c�dente par un �l�ment corps
	if(m_posSerpent.size()>1)
		m_posSerpent[1] = { m_posSerpent[0].line, m_posSerpent[0].column, Tiles(m_posSerpent[0].tile-10) };
}

//Gestion du deplacement de la tete
void Serpent::deplacementTete(Tiles head_tile, const Map & map)
{
	switch (head_tile)
    {
	case HEAD_NORTH:
		m_posSerpent[0] = { (m_posSerpent[0].line - 1) < 0 ? (int)map.getGameField().size() - 1 : (m_posSerpent[0].line - 1) , m_posSerpent[0].column, HEAD_NORTH };
            break;
	case HEAD_EAST:
		m_posSerpent[0] = { m_posSerpent[0].line, (m_posSerpent[0].column + 1) > (int)map.getGameField()[0].size() - 1 ? 0 : (m_posSerpent[0].column + 1) ,  HEAD_EAST };
            break;
	case HEAD_SOUTH:
		m_posSerpent[0] = { (m_posSerpent[0].line + 1) > (int)map.getGameField().size()-1 ? 0 : (m_posSerpent[0].line + 1) , m_posSerpent[0].column, HEAD_SOUTH };
            break;
	case HEAD_WEST:
		m_posSerpent[0] = { m_posSerpent[0].line, (m_posSerpent[0].column - 1) < 0 ? (int)map.getGameField()[0].size() - 1 : (m_posSerpent[0].column - 1) , HEAD_WEST };
		break;
	default:
            break;
    }

}

//Gestion des differents fruits manges
bool Serpent::fruit_action(Map & map, Tiles & head_tile)
{
	Tiles fruit;
    m_lastPosition = m_posSerpent[m_posSerpent.size()-1];
	fruit = map.getTile(m_posSerpent[0].line, m_posSerpent[0].column);
	switch (fruit) {
        case CHERRY://Agrandit le serpent
            m_posSerpent.push_back(m_lastPosition);// On rajoute un �l�ment Serpent � la derni�re position de la queue pour allonger le Serpent
            map.popFruit();
			return true;
        case BANANA://Reduit le serpent d'une unite
            if (m_posSerpent.size()!=1) { //On ne retire un �l�ment que si le serpent peut le supporter
                map.updateGameField(m_posSerpent[m_posSerpent.size()-1].line, m_posSerpent[m_posSerpent.size()-1].column, EMPTY);//On affiche EMTPY � la places du body
                m_posSerpent.pop_back();//On enl�ve un �l�ment au serpent
            }
            break;
        case GRAPE://Reduit le serpent a la t�te
            for (int i = m_posSerpent.size()-1; i > 0; --i) {
                map.updateGameField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);
                m_posSerpent.pop_back();
            }
            break;
        case LEMON://Change l'orientation du serpent
            if (m_posSerpent.size()>1) {
                reverse(m_posSerpent.begin(), m_posSerpent.end());
				m_posSerpent[0].tile = Tiles(((m_posSerpent[0].tile - 10) + 2) % 4 + 20);
				m_posSerpent[m_posSerpent.size() - 1].tile = Tiles(((m_posSerpent[m_posSerpent.size() - 1].tile - 20) + 2) % 4 + 10);
                head_tile = getHead();
            }
            break;
        case STRAWBERRY://Echange les inputs
            reverse_input = !reverse_input;
            break;
        default:
            break;
	}
	return false;
}

//Gestion de la position de la nouvelle t�te du bot
Tiles Serpent::calculateNextHeadMove(Map & map)
{
	vector<pair<int, int>> scores;
	pair<int, int> futureTileCoord[3];
	switch (getHead())
	{
	case HEAD_EAST:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		break;
	case HEAD_SOUTH:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		break;
	case HEAD_WEST:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		break;
	case HEAD_NORTH:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		break;
	default:
		break;
	}

	int direction;
	//On recherche si le fruit n'est pas dans la direction -1 ou 1
	if (map.getCherry().first == futureTileCoord[0].first && map.getCherry().first == futureTileCoord[2].first) //meme ligne
		direction = abs(map.getCherry().first - futureTileCoord[0].first) < abs(map.getCherry().first - futureTileCoord[2].first) ? -1 : 1;
	else if (map.getCherry().second == futureTileCoord[0].second && map.getCherry().second == futureTileCoord[2].second) //meme colonne
		direction = abs(map.getCherry().first - futureTileCoord[0].first) < abs(map.getCherry().first - futureTileCoord[2].first) ? -1 : 1;
	else if (map.getCherry().first == futureTileCoord[1].first || map.getCherry().second == futureTileCoord[1].second)
		direction = 0;//Si on fonce vers la cerise on continue
	else
		direction = rand() % 100 < 80 ? 0 : -1; //On privil�gie � 80% la direction tout droit et � 20% -1
	
	printf("%d\n", direction);

	for (int h = 0; h < 3; h++)
	{
		printf("%d %d\n", direction, map.getTile(futureTileCoord[direction + 1].first, futureTileCoord[direction + 1].second));
		if (map.getTile(futureTileCoord[direction + 1].first, futureTileCoord[direction + 1].second) >= 30)
			return Tiles(20 + (getHead() - 20 + (direction + 4)) % 4);
		direction++;
		direction = (direction + 1) % 3 - 1;//on d�cale d'une position
	}

	//Si aucun chemin n'est possible on tire au sort
	printf("bye\n");
	return Tiles(20 + (getHead() - 20 + (rand() % -1 + 4)) % 4);
}

//Definition de la tete
bool Serpent::setHead(Map map, bool bot)
{
	if (!bot)
	{
		for (int i = 0; i < map.getGameField().size(); ++i)
			for (int j = 0; j < map.getGameField()[i].size(); ++j)
				if (map.getTile(i, j) >= 20 && map.getTile(i, j) <= 23)
				{
					m_posSerpent.push_back({ i,j,map.getTile(i,j) });
					return true;
				}
	}
	else
	{
		if (m_posSerpent.size()>0 && map.getTile(m_posSerpent[0].line, m_posSerpent[0].column) != EMPTY)//On regarde si la valeur pr�charg� est valide
			return true;
		else
		{
			m_posSerpent.clear();
			int i(0), j(0);
			do
			{
				srand(time(NULL)); //Initialisation du timer
				i = rand() % (map.getGameField().size() - 3) + 1;
				j = rand() % (map.getGameField()[0].size() - 3) + 1;
			} while (map.getTile(i, j) != EMPTY);
			m_posSerpent.push_back({ i,j,HEAD_EAST });
			return true;
		}
	}
	return false;
}


void Serpent::run(Map & map, Tiles & head_tile, Serpent & serpentBot, Map copie)
{
	if (run(map, head_tile))
	{
		srand(time(NULL));
		if (rand() % 100 > 80) //20% de chance que la cerise qu'on vient de manger entraine l'apparition du bot
		{
			copie.updateGameField(map.getCherry().first, map.getCherry().second, CHERRY);
			if (!serpentBot.setHead(copie, true))
			{
				cout << "Impossible de placer le bot" << endl;
				return;
			}
			else
				serpentBot.setAlive(map, true);
		}
	}
}

//Definition les differentes actions par tour
bool Serpent::run(Map & map, Tiles & head_tile)
{
	map.updateGameField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	deplacementTete(head_tile, map);
	setAlive(map, false);
	bool cherryEaten = fruit_action(map, head_tile);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateGameField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);//On update les tiles de la map
	}

	map.decreaseLifetimeFruits();
	return cherryEaten;
}

//Definition des differentes actions du bot par tour
void Serpent::runBot(Map & map)
{
	map.updateGameField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	Tiles head_tile = calculateNextHeadMove(map);
	deplacementTete(head_tile, map);
	setAlive(map, true);
	fruit_action(map, head_tile);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateGameField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);
	}
}

//Gestion des collisions avec les elements du decor
void Serpent::setAlive(Map & map, bool bot)
{
	switch (map.getTile(m_posSerpent[0].line, m_posSerpent[0].column))
	{
	case BODY_NORTH:
	case BODY_EAST:
	case BODY_SOUTH:
	case BODY_WEST:
	case HEAD_NORTH:
	case HEAD_EAST:
	case HEAD_SOUTH:
	case HEAD_WEST:
	case TREE:
		if (bot)
		{
			m_posSerpent[0] = m_posSerpent[m_posSerpent.size() - 1];//On pr�charge une valeur intiale de la t�te pour le prochain bot
			for (int i = m_posSerpent.size() - 1; i = 1; i--)
			{
				map.updateGameField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);//On enl�ve le corps du bot
				m_posSerpent.pop_back();
			}
		}
		alive = false;
		break;
	default:
		alive = true;
		break;
	}
}
