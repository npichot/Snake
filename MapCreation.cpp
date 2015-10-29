#include "MapCreation.h"
using namespace sf;
using namespace std;


MapCreation::MapCreation(Map m)
	:m(m), tb(Toolbar(m.getParentWindow()))
{
}


MapCreation::~MapCreation()
{
}

void MapCreation::launchInterface()
{
	while (m.getParentWindow().isOpen())
	{
		m.getParentWindow().clear();
		m.drawField(true);
		tb.drawBar();
		vector<Tool> & tools = tb.getTools();

		Event event;
		while (m.getParentWindow().pollEvent(event))// on capte les evenements
		{
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				
				for (int i = 0; i < tools.size(); i++)
					if (tools[i].getGlobalBounds().contains(Mouse::getPosition(m.getParentWindow()).x, Mouse::getPosition(m.getParentWindow()).y))
					{
						tools[i].activate(!tools[i].isActivated());
						break;
					}
		}


		m.getParentWindow().display();
	}
}
