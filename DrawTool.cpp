#include "DrawTool.h"
using namespace sf;


DrawTool::DrawTool(sf::Texture t, std::string s, bool b, Tiles tile)
	:Tool(t,s,b), t(tile)
{
}

DrawTool::~DrawTool()
{
}

bool DrawTool::execute(sf::Event & event, int xMouse, int yMouse, Map & map)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
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
}
