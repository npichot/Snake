#include "DrawTool.h"

using namespace sf;
using namespace std;


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
					map.updateField(i, j, getTile());
				}
			return true;
		}
		else
		{
			map.updateField(row0, column0, getTile());
			return true;
		}

	return false;//Nothing changed
}

void DrawTool::activate(bool b)
{
	activated = b;
	if (activated)
		setOutlineThickness(2);
	else
		setOutlineThickness(0);
}
