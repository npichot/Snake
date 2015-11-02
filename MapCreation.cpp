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
	bool mouseIsCliked = false;

	int xMouse0 = 0;
	int yMouse0 = 0;

	int xMouse = 0;
	int yMouse = 0;

	Map tempMap=map;

	while (window.isOpen())
	{
		window.clear();
		tempMap.drawField(window, true);
		tb.drawBar(window);
		vector<Tool*>  tools = tb.getTools();

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
				mouseIsCliked = true;
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				mouseIsCliked = false;
			}

			//Gestion des actions
			if (!mouseIsCliked)
			{
				map = tempMap;
			}
			else
			{
				tempMap = map;
				if (tb.getSelected() != NULL)
					if (tb.getSelected()->execute(xMouse0, yMouse0, xMouse, yMouse, tempMap))
						break;

				for (int i = 0; i < tools.size(); i++)
					if (tools[i]->getGlobalBounds().contains(xMouse, yMouse))
					{
						tools[i]->activate(!tools[i]->isActivated());
						if (tools[i]->isActivated())
						{
							tb.setSelected(tools[i]);
						}
						else
							tb.setSelected(NULL);
						break;
					}
			}

		}
		window.display();
	}
}
