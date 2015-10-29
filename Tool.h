#ifndef __TOOL_H__
#define __TOOL_H__

#include "SFML/Graphics.hpp"

class Tool
{
private:
	sf::Texture texture;
	std::string name;
	bool activated;
public:
	Tool();
	~Tool();
};

#endif // !__TOOL_H__