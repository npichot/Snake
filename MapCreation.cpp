#include "MapCreation.h"
using namespace sf;
using namespace std;


MapCreation::MapCreation()
	:tb(Toolbar())
{
}


MapCreation::~MapCreation()
{
}

void MapCreation::executeInterface(RenderWindow & window, Map & map)
{
	bool mouseIsClicked = false;
	bool mouseJustClicked = false;

	int xMouse0 = 0;
	int yMouse0 = 0;

	int xMouse = 0;
	int yMouse = 0;

	Map tempMap=map;
	vector<DrawTool*>  drawTools = tb.getDrawTools();
	vector<MainTool*>  mainTools = tb.getMainTools();

	while (window.isOpen())
	{
		window.clear();
		tempMap.drawField(window);
		tb.drawBar(window);

		Event event;
		while (window.pollEvent(event))// on capte les evenements
		{
			//Gestion des inputs
			if (event.type == Event::MouseMoved)
			{
				xMouse = Mouse::getPosition(window).x;
				yMouse = Mouse::getPosition(window).y;
			}
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				xMouse0 = Mouse::getPosition(window).x;
				yMouse0 = Mouse::getPosition(window).y;
				mouseIsClicked = true;
				mouseJustClicked = true;
				break;
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				mouseIsClicked = false;
				break;
			}
		}

			//Gestion des actions
			if (!mouseIsClicked)
			{
				map = tempMap;
			}
			else
			{
				tempMap = map;
				if (tb.getSelected() != NULL)
					if (tb.getSelected()->execute(xMouse0, yMouse0, xMouse, yMouse, tempMap))
					{
						window.display();
						continue;
					}
			}

			if(mouseJustClicked)
			{
				for (int i = 0; i < mainTools.size(); i++)
					if (mainTools[i]->getGlobalBounds().contains(xMouse, yMouse))
					{
						if (!mainTools[i]->execute(xMouse0, yMouse0, xMouse, yMouse, tempMap))
							return;
						continue;
					}

				for (int i = 0; i < drawTools.size(); i++)
					if (drawTools[i]->getGlobalBounds().contains(xMouse, yMouse))
					{
						drawTools[i]->activate(!drawTools[i]->isActivated());
						for (int j = 0; j < drawTools.size(); j++)
						{
							if (i != j)
								drawTools[j]->activate(false);
						}

						if (drawTools[i]->isActivated())
						{
							tb.setSelected(drawTools[i]);
						}
						else
							tb.setSelected(NULL);
						break;
					}
				mouseJustClicked = false;
			}

		window.display();
	}
}
