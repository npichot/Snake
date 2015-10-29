#include "MapCreation.h"



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
		m.getParentWindow().display();
	}
}
