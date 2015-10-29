#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "Tool.h" 
#include "Map.h"

class Toolbar
{
private:
	sf::RenderWindow & window;
	std::vector<Tool> tools;
public:
	Toolbar(sf::RenderWindow & window);
	~Toolbar();
	void drawBar();
};

#endif __TOOLBAR_H__
