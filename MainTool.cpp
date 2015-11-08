#include "MainTool.h"
using namespace std;
using namespace sf;

MainTool::MainTool(sf::Texture t, std::string s)
	:Tool(t, s)
{
}

MainTool::~MainTool()
{
}

bool MainTool::execute(int x0, int y0, int x, int y, Map & map)
{
	//Implement Save function
	if (getName() == "Save")
		saveMap();
	return true;
}

void MainTool::saveMap()
{
	RenderWindow saveWindow(VideoMode(400, 100, 32), "Save Map");
	while (saveWindow.isOpen())
	{
		saveWindow.clear(Color::White);
		saveWindow.display();
	}
}
