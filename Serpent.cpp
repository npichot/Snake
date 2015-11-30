#include "Serpent.h"

using namespace std;
using namespace sf;

Serpent::Serpent()
	:alive(true)
{
}

Serpent::~Serpent()
{
}

void Serpent::deplacementSerpent()
{
    m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la derni�re position de la queue
    for (int i = m_posSerpent.size() - 1; i >= 2; --i)
		m_posSerpent[i] = m_posSerpent[i - 1];

	//Remplace la t�te pr�c�dente par un �l�ment corps
	if(m_posSerpent.size()>1)
		m_posSerpent[1] = { m_posSerpent[0].line, m_posSerpent[0].column, convertHeadtoBody.at(m_posSerpent[0].tile) };
}

void Serpent::deplacementTete(Tiles head_tile, const Map & map)//G�re le d�placement de la t�te
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

void Serpent::fruit_action(Map & map)//On d�finit l'action sur le serpent en fonction du fruit mang�
{
	Tiles fruit;
    m_lastPosition = m_posSerpent[m_posSerpent.size()-1];
    int size_init = m_posSerpent.size();
	fruit = map.getTile(m_posSerpent[0].line, m_posSerpent[0].column);
	switch (fruit) {
        case CHERRY:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un �l�ment Serpent � la derni�re position de la queue pour allonger le Serpent
            map.popFruit();
            break;
        case BANANA:
            if (m_posSerpent.size()!=1) { //On ne retire un �l�ment que si le serpent peut le supporter
                map.updateField(m_posSerpent[m_posSerpent.size()-1].line, m_posSerpent[m_posSerpent.size()-1].column, EMPTY);//On affiche EMTPY � la places du body
                m_posSerpent.pop_back();//On enl�ve un �l�ment au serpent
            }
            break;
        case GRAPE:
            for (int i = m_posSerpent.size()-1; i > 0; --i) {
                map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);
                m_posSerpent.pop_back();//On enl�ve tout saauf la tete
            }
            break;
        case LEMON:
            for (int i= size_init-1; i > (size_init-1)/2; --i) {
                map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);
                m_posSerpent.pop_back();//On enl�ve la moiti�
            }
            break;
        case STRAWBERRY:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un �l�ment Serpent � la derni�re position de la queue pour allonger le Serpent
            break;
        
        default:
            break;
	}
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
	return false;
}

void Serpent::run(Map & map, Tiles head_tile)
{
	map.updateField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	deplacementTete(head_tile, map);
	fruit_action(map);
	setAlive(map, false);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);
	}
	
	
    map.decreaseLifetimeFruits();
    map.deleteFruits();
}

void Serpent::runBot(Map & map)
{
	map.updateField(m_posSerpent[m_posSerpent.size() - 1].line, m_posSerpent[m_posSerpent.size() - 1].column, EMPTY);//Suppression du derniere element sur la map avant deplacement
	deplacementSerpent();
	Tiles head_tile = calculateNextHeadMove(map);
	deplacementTete(head_tile, map);
	fruit_action(map);
	setAlive(map, true);

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
			for (int i = 1; i < m_posSerpent.size(); ++i)
				map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);//On enl�ve le bot de la map
			m_posSerpent.clear();//on le tue
		}
		alive = false;
		break;
	default:
		break;
	}
}
