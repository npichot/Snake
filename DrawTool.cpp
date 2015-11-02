#include "DrawTool.h"
using namespace sf;


DrawTool::DrawTool(sf::Texture t, std::string s, bool b, Tiles tile)
	:Tool(t,s,b), t(tile)
{
}

DrawTool::~DrawTool()
{
}

bool DrawTool::execute(int xMouse, int yMouse, Map & map)
{
	int row, column;
	if ((row = map.getRowFromMouseCoordinate(xMouse, yMouse)) != -1)
		if ((column = map.getColumnFromMouseCoordinate(xMouse, yMouse)) != -1)
		{
			map.updateField(row, column, getTile());
			return true;
		}

	return false;//Nothing changed
}
