#include "Toolbar.h"

using namespace std;
using namespace sf;

Toolbar::Toolbar(RenderWindow & window)
	:window(window)
{
	//New tool tree added to the toolbar
	Texture textureTree; textureTree.loadFromFile("Ressources/tree.png");
	Tool toolTree(textureTree,"tree",false);
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
		RectangleShape button;
		button.setTexture(&(tools[i].getTexture()));
		button.setPosition(framework.getPosition().x + 10 + (TILE_SIZE + 2.5)*i, 5);
		button.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		if (tools[i].isActivated())
		{
			button.setOutlineColor(Color::Red);
			button.setOutlineThickness(2);
		}
		window.draw(button);
	}
}
