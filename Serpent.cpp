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

void Serpent::deplacementSerpent()
{
    for (int i = m_posSerpent.size() - 1; i >= 2; --i)
		m_posSerpent[i] = m_posSerpent[i - 1];

	//Remplace la tÍte prÈcÈdente par un ÈlÈment corps
	if(m_posSerpent.size()>1)
		m_posSerpent[1] = { m_posSerpent[0].line, m_posSerpent[0].column, convertHeadtoBody.at(m_posSerpent[0].tile) };
}

void Serpent::deplacementTete(Tiles head_tile, const Map & map)//Gère le déplacement de la tête
{
	switch (head_tile)
    {
	case HEAD_NORTH:
		m_posSerpent[0] = { (m_posSerpent[0].line - 1) < 0 ? (int)map.getField().size() - 1 : (m_posSerpent[0].line - 1) , m_posSerpent[0].column, HEAD_NORTH };
            break;
	case HEAD_EAST:
		m_posSerpent[0] = { m_posSerpent[0].line, (m_posSerpent[0].column + 1) > (int)map.getField()[0].size() - 1 ? 0 : (m_posSerpent[0].column + 1) ,  HEAD_EAST };
            break;
	case HEAD_SOUTH:
		m_posSerpent[0] = { (m_posSerpent[0].line + 1) > (int)map.getField().size()-1 ? 0 : (m_posSerpent[0].line + 1) , m_posSerpent[0].column, HEAD_SOUTH };
            break;
	case HEAD_WEST:
		m_posSerpent[0] = { m_posSerpent[0].line, (m_posSerpent[0].column - 1) < 0 ? (int)map.getField()[0].size() - 1 : (m_posSerpent[0].column - 1) , HEAD_WEST };
		break;
	default:
            break;
    }

}

bool Serpent::fruit_action(Map & map, Tiles & head_tile)//On définit l'action sur le serpent en fonction du fruit mange
{
	Tiles fruit;
    m_lastPosition = m_posSerpent[m_posSerpent.size()-1];
    int size_init = m_posSerpent.size();
	fruit = map.getTile(m_posSerpent[0].line, m_posSerpent[0].column);
	switch (fruit) {
        case CHERRY:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un ÈlÈment Serpent ‡ la derniËre position de la queue pour allonger le Serpent
            map.popFruit();
			return true;
        case BANANA:
            if (m_posSerpent.size()!=1) { //On ne retire un élément que si le serpent peut le supporter
                map.updateField(m_posSerpent[m_posSerpent.size()-1].line, m_posSerpent[m_posSerpent.size()-1].column, EMPTY);//On affiche EMTPY à la places du body
                m_posSerpent.pop_back();//On enlève un élément au serpent
            }
            break;
        case GRAPE:
            for (int i = m_posSerpent.size()-1; i > 0; --i) {
                map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);
                m_posSerpent.pop_back();//On enlève tout saauf la tete
            }
            break;
        case LEMON:
            if (m_posSerpent.size()>1) {
                reverse(m_posSerpent.begin(), m_posSerpent.end());
				m_posSerpent[0].tile = Tiles(((m_posSerpent[0].tile - 10) + 2) % 4 + 20);
				m_posSerpent[m_posSerpent.size() - 1].tile = Tiles(((m_posSerpent[m_posSerpent.size() - 1].tile - 20) + 2) % 4 + 10);
                head_tile = getHead();
            }
            break;
        case STRAWBERRY:
            reverse_input = !reverse_input;
            break;
        default:
            break;
	}
	return false;
}

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
		direction = rand() % 100 < 80 ? 0 : -1; //On privilÈgie ‡ 80% la direction tout droit et ‡ 20% -1
	
	printf("%d\n", direction);

	for (int h = 0; h < 3; h++)
	{
		printf("%d %d\n", direction, map.getTile(futureTileCoord[direction + 1].first, futureTileCoord[direction + 1].second));
		if (map.getTile(futureTileCoord[direction + 1].first, futureTileCoord[direction + 1].second) >= 30)
			return Tiles(20 + (getHead() - 20 + (direction + 4)) % 4);
		direction++;
		direction = (direction + 1) % 3 - 1;//on dÈcale d'une position
	}

	//Si aucun chemin n'est possible on tire au sort
	printf("bye\n");
	return Tiles(20 + (getHead() - 20 + (rand() % -1 + 4)) % 4);
}

bool Serpent::setHead(Map map, bool bot)
{
	if (!bot)
	{
		for (int i = 0; i < map.getField().size(); ++i)
			for (int j = 0; j < map.getField()[i].size(); ++j)
				if (map.getTile(i, j) >= 20 && map.getTile(i, j) <= 23)
				{
					m_posSerpent.push_back({ i,j,map.getTile(i,j) });
					return true;
				}
	}
	else
	{
		if (m_posSerpent.size()>0 && map.getTile(m_posSerpent[0].line, m_posSerpent[0].column) != EMPTY)//On regarde si la valeur prÈchargÈ est valide
			return true;
		else
		{
			m_posSerpent.clear();
			int i(0), j(0);
			do
			{
				srand(time(NULL)); //Initialisation du timer
				i = rand() % (map.getField().size() - 3) + 1;
				j = rand() % (map.getField()[0].size() - 3) + 1;
			} while (map.getTile(i, j) != EMPTY);
			m_posSerpent.push_back({ i,j,HEAD_EAST });
			return true;
		}
	}
	return false;
}

void Serpent::run(Map & map, Tiles & head_tile, Serpent & serpentBot, Map copie)
{
	if(run(map, head_tile))
		if (rand() % 100 > 80) //20% de chance que la cerise qu'on vient de manger entraine l'apparition du bot
		{
			copie.updateField(map.getCherry().first, map.getCherry().second, CHERRY);
			if (!serpentBot.setHead(copie, true))
			{
				cout << "Impossible de placer le bot" << endl;
				return;
			}
			else
				serpentBot.setAlive(map, true);
		}
}

bool Serpent::run(Map & map, Tiles & head_tile)
{
	map.updateField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	deplacementTete(head_tile, map);
	setAlive(map, false);
	bool cherryEaten = fruit_action(map, head_tile);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);
	}

	map.decreaseLifetimeFruits();
	map.deleteFruits();
	return cherryEaten;
}

void Serpent::runBot(Map & map)
{
	map.updateField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	Tiles head_tile = calculateNextHeadMove(map);
	deplacementTete(head_tile, map);
	setAlive(map, true);
	fruit_action(map, head_tile);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);
	}
}

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
			m_posSerpent[0] = m_posSerpent[m_posSerpent.size() - 1];//On prÈcharge une valeur intiale de la tÍte pour le prochain bot
			for (int i = m_posSerpent.size() - 1; i = 1; i--)
			{
				map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);//On enlËve le corps du bot
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
