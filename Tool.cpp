#include "Tool.h"
using namespace std;
using namespace sf;


Tool::Tool(Texture t, string s, bool b)
	:texture(t), name(s), activated(b)
{
}


Tool::~Tool()
{
}


