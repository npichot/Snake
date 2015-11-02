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
	while (window.isOpen())
	{
		window.clear();
		map.drawField(window, true);
		tb.drawBar(window);
		vector<Tool*>  tools = tb.getTools();

		int xMouse = Mouse::getPosition(window).x;
		int yMouse = Mouse::getPosition(window).y;

		Event event;
		while (window.pollEvent(event))// on capte les evenements
		{
			if (event.type == Event::MouseMoved)
			{
				int xMouse = Mouse::getPosition(window).x;
				int yMouse = Mouse::getPosition(window).y;
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
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
				if (tb.getSelected() != NULL)
					tb.getSelected()->execute(event,xMouse,yMouse, map);
			}

		}
		window.display();
	}
}
