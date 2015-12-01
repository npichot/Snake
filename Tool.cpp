#include "Tool.h"
using namespace std;
using namespace sf;

/*
Constructeure de la classe qui initialise les propriétés des rectangles.
Cette classe est une classe abstraite
*/
Tool::Tool(Texture t, string s)
	: name(s)
{
	setTexture(new Texture(t));
	setOutlineColor(Color::Red);
	setSize(Vector2f(TILE_SIZE, TILE_SIZE));
}

Tool::~Tool()
{
}





