#ifndef __TOOL_H__
#define __TOOL_H__

#include "SFML/Graphics.hpp"
#include "Map.h"

class Tool: public sf::RectangleShape
{
private:
	sf::Texture & texture;
	std::string name;
	bool activated;
public:
	Tool(sf::Texture t, std::string s, bool b);
	~Tool();
	void activate(bool b);
	bool isActivated() { return activated; };
	sf::Texture * getTheTexture() { return &texture; };
};

#endif // !__TOOL_H__