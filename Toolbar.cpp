#include "Toolbar.h"

using namespace std;
using namespace sf;

Toolbar::Toolbar()
	:selected(NULL)
{
	//New tool tree added to the toolbar
	Texture texture; texture.loadFromFile("Ressources/tree.png");
	tools.push_back(new DrawTool(texture, "Tree", false, TREE));

	//New tool grass added to the toolbar
	texture.loadFromFile("Ressources/grass.png");
	tools.push_back(new DrawTool(texture, "Grass", false, EMPTY));

	//New tool Head_E added to the toolbar
	texture.loadFromFile("Ressources/head_E.png");
	tools.push_back(new DrawTool(texture, "Head_E", false, HEAD_EAST));
}


Toolbar::~Toolbar()
{
}

void Toolbar::drawBar(RenderWindow & window)
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
		tools[i]->setPosition(framework.getPosition().x + 10 + (TILE_SIZE + 5)*i, 5);
		window.draw(*tools[i]);
	}
}
