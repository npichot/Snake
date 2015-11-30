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
    m_lastPosition = m_posSerpent[m_posSerpent.size() - 1]; // Pour sauvegarder la derniËre position de la queue
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

void Serpent::fruit_action(Map & map)//On définit l'action sur le serpent en fonction du fruit mangé
{
	Tiles fruit;
    m_lastPosition = m_posSerpent[m_posSerpent.size()-1];
    int size_init = m_posSerpent.size();
	fruit = map.getTile(m_posSerpent[0].line, m_posSerpent[0].column);
	switch (fruit) {
        case CHERRY:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un ÈlÈment Serpent ‡ la derniËre position de la queue pour allonger le Serpent
            map.popFruit();
            break;
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
            for (int i= size_init-1; i > (size_init-1)/2; --i) {
                map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, EMPTY);
                m_posSerpent.pop_back();//On enlève la moitiÈ
            }
            break;
        case STRAWBERRY:
            m_posSerpent.push_back(m_lastPosition);// On rajoute un ÈlÈment Serpent ‡ la derniËre position de la queue pour allonger le Serpent
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
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		break;
	case HEAD_SOUTH:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		break;
	case HEAD_WEST:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line + 1, m_posSerpent[0].column);
		break;
	case HEAD_NORTH:
		futureTileCoord[0] = pair<int, int>(m_posSerpent[0].line - 1, m_posSerpent[0].column);
		futureTileCoord[1] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column + 1);
		futureTileCoord[2] = pair<int, int>(m_posSerpent[0].line, m_posSerpent[0].column - 1);
		break;
	default:
		break;
	}

	for (int i = 0; i < 3; i++)
	{
		if (map.getTile(futureTileCoord[i].first, futureTileCoord[i].second) >= 30)
			scores.push_back(pair<int, int>(abs(futureTileCoord[i].first - map.getCherry().first) + abs(futureTileCoord[i].second - map.getCherry().second), i == 2 ? -1 : i));
	}

	if (scores.size() == 0)//On choisit alÈatoirement une direction
		return Tiles(20 + (getHead() - 20 + (scores[(rand() % 3)].second + 4)) % 4);
	else
	{
		sort(scores.begin(), scores.end());
		scores[0].first = 3 * (2 * scores[scores.size() - 1].first - scores[0].first);
		for (int i = 1; i < scores.size(); i++)
			scores[i].first =  (2 * scores[scores.size() - 1].first - scores[i].first) + scores[i - 1].first;

		int h = rand()% scores[scores.size()-1].first;
		int l = 0;
		while (l<scores.size() && h > scores[l].first)
			l++;
			
		return Tiles(20 + (getHead() - 20 + (scores[l].second + 4)) % 4);//Sinon on tire au sort parmi les premiers ex aequo restants
	}


	return Tiles();
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
	setAlive(map);
    fruit_action(map);

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
	setAlive(map);
	fruit_action(map);

	for (int i = 0; i < m_posSerpent.size(); ++i)
	{
		map.updateField(m_posSerpent[i].line, m_posSerpent[i].column, m_posSerpent[i].tile);
	}
}

void Serpent::setAlive(Map & map)
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
		alive = false;
		break;
	default:
		break;
	}
}
