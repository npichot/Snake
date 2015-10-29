#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "Tool.h" 


class Toolbar
{
private:
	sf::RenderWindow & window;
	std::vector<Tool> tools;
public:
	Toolbar();
	~Toolbar();
	void drawBar();
};

#endif __TOOLBAR_H__
