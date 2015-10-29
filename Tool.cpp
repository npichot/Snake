#include "Tool.h"
using namespace std;
using namespace sf;


Tool::Tool(Texture t, string s, bool b)
	: texture(t), name(s), activated(b)
{
	
	setTexture(&texture);

	setOutlineColor(Color::Red);
	if (activated)
		setOutlineThickness(2);
	else
		setOutlineThickness(0);

	setSize(Vector2f(TILE_SIZE, TILE_SIZE));

}


Tool::~Tool()
{
}

void Tool::activate(bool b)
{
	activated = b;
	if (activated)
		setOutlineThickness(2);
	else
		setOutlineThickness(0);
}


