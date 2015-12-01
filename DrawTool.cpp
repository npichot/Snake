#include "DrawTool.h"

using namespace sf;
using namespace std;

/*
Le constructeur initialise les attributs de la classe. 
Si l'outil est actif on rajoute une bordure autour de 2px
*/
DrawTool::DrawTool(sf::Texture t, std::string s, bool b, Tiles tile)
	:Tool(t,s), t(tile), activated(b)
{
	if (activated)
		setOutlineThickness(2);
	else
		setOutlineThickness(0);
}

DrawTool::~DrawTool()
{
}

/*
Cette fonction est le coeur de la classe. Elle correspond au traitement effectué sur
la map en fonction du déplacement de la souris et ce, lorsque l'outil est actif.
On met à jour avec la tile (correspondant à l'outil en cours) toutes les cases 
de la map dans le rectangle dont la diagonale est défini par les deux point suivants:
(xMouse0,yMouse0) et (xMouse,yMouse)
*/
bool DrawTool::execute(int xMouse0, int yMouse0, int xMouse, int yMouse, Map & map)
{
	int row0, column0, row, column;
	if (((row0 = map.getRowFromMouseCoordinate(xMouse0, yMouse0)) != -1) &&
		((column0 = map.getColumnFromMouseCoordinate(xMouse0, yMouse0)) != -1))
		if (((row = map.getRowFromMouseCoordinate(xMouse, yMouse)) != -1) &&
			((column = map.getColumnFromMouseCoordinate(xMouse, yMouse)) != -1))
		{
			for (int i = min(row0, row); i <= max(row0, row); i++)
				for (int j = min(column0, column); j <= max(column0, column); j++)
				{
					map.updateGameField(i, j, t);
				}
			return true;
		}
		else
		{
			map.updateGameField(row0, column0, t);
			return true;
		}

	return false;//Nothing changed
}

/*
Cette fonction active ou désactive l'outils.
L'outils active possede une bordure rouge de 2px.
*/
void DrawTool::activate(bool b)
{
	activated = b;
	if (activated)
		setOutlineThickness(2);
	else
		setOutlineThickness(0);
}
