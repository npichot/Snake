#include "Toolbar.h"

using namespace std;
using namespace sf;

Toolbar::Toolbar(RenderWindow & window)
	:window(window)
{
	//New tool tree added to the toolbar
	Texture texture; texture.loadFromFile("Ressources/tree.png");
	Tool toolTree(texture,"tree",false);
	tools.push_back(toolTree);

}


Toolbar::~Toolbar()
{
}

void Toolbar::drawBar()
{
	int width = TILE_SIZE*tools.size() + 20 + 5 * (tools.size() - 1);

	//build framework
	RectangleShape framework;
	framework.setPosition((window.getSize().x - width) / 2, 0);
	framework.setSize(Vector2f(width, TILE_SIZE+10));
	framework.setFillColor(Color(140,140,140,255));
	window.draw(framework);

	//Add tools
	for (int i = 0; i < tools.size();i++)
	{
		Texture texture; texture.loadFromFile("Ressources/tree.png");
		tools[i].setTexture(&texture);//TODO optimiser en supprimant ca et en mettant le set texture dans Tool.cpp tout en évitant le pb du carré blanc
		tools[i].setPosition(framework.getPosition().x + 10 + (TILE_SIZE + 2.5)*i, 5);
		window.draw(tools[i]);
	}
}
