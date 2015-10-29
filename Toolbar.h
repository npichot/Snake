#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "Tool.h" 

class Toolbar
{
private:
	sf::RenderWindow & window;
	std::vector<Tool> tools;
public:
	Toolbar(sf::RenderWindow & window);
	~Toolbar();
	void drawBar();
	std::vector<Tool> & getTools() { return tools; };
};

#endif __TOOLBAR_H__
