#include "Tool.h"
using namespace std;
using namespace sf;


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





