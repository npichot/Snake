#include "Toolbar.h"

using namespace std;
using namespace sf;

/*
Ce constructeur permet d'ajouter à la Toolbar les différents Tools.
*/
Toolbar::Toolbar()
	:selected(NULL)
{
	//New tool tree added to the toolbar
	Texture texture; texture.loadFromFile("Ressources/tree.png");
	drawTools.push_back(new DrawTool(texture, "Tree", false, TREE));

	//New tool grass added to the toolbar
	texture.loadFromFile("Ressources/grass.png");
	drawTools.push_back(new DrawTool(texture, "Grass", false, EMPTY));

	//New tool Head_E added to the toolbar
	texture.loadFromFile("Ressources/head_E.png");
	drawTools.push_back(new DrawTool(texture, "Head_E", false, HEAD_EAST));

	//New tool Save added to the toolbar
	texture.loadFromFile("Ressources/save.png");
	mainTools.push_back(new MainTool(texture, "Save"));

	//New tool Quit added to the toolbar
	texture.loadFromFile("Ressources/quit.png");
	mainTools.push_back(new MainTool(texture, "Quit"));
}

Toolbar::~Toolbar()
{
}

/*
Cette fonction est en charge de dessiner la Toolbar dans la fenêtre window.
*/
void Toolbar::drawBar(RenderWindow & window)
{
	int width = TILE_SIZE*(drawTools.size()+ mainTools.size()) + 40 + 5 * (drawTools.size() - 1);

	//build framework
	RectangleShape framework;
	framework.setPosition((window.getSize().x - width) / 2, 0);
	framework.setSize(Vector2f(width, TILE_SIZE+10));
	framework.setFillColor(Color(140,140,140,255));
	window.draw(framework);

	//Add tools
	for (int i = 0; i < drawTools.size()+mainTools.size();i++)
	{
		if (i < drawTools.size())
		{
			drawTools[i]->setPosition(framework.getPosition().x + 10 + (TILE_SIZE + 5)*i, 5);
			window.draw(*drawTools[i]);
		}
		else
		{
			mainTools[i- drawTools.size()]->setPosition(framework.getPosition().x + 30 + (TILE_SIZE + 5)*i, 5);
			window.draw(*mainTools[i - drawTools.size()]);
		}
	}
}
