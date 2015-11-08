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
	return false;
}
