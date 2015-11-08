#ifndef __TOOL_H__
#define __TOOL_H__

#include "Map.h"

class Tool: public sf::RectangleShape
{
private:
	std::string name;
public:
	Tool(sf::Texture t, std::string s);
	~Tool();
	std::string getName() { return name; }
	virtual bool execute(int x0, int y0, int x, int y, Map & map)=0;
};

#endif // !__TOOL_H__