#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "DrawTool.h" 

class Toolbar
{
private:
	std::vector<Tool*> tools;
	Tool * selected;
public:
	Toolbar();
	~Toolbar();
	void drawBar(sf::RenderWindow & window);
	std::vector<Tool*>  getTools() { return tools; };
	Tool * getSelected() { return selected; };
	void setSelected(Tool * t) { selected = t; };
};

#endif __TOOLBAR_H__
