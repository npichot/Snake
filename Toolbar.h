#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__

#include "DrawTool.h" 
#include "MainTool.h" 

class Toolbar
{
private:
	std::vector<DrawTool*> drawTools;
	std::vector<MainTool*> mainTools;
	DrawTool * selected;
public:
	Toolbar();
	~Toolbar();
	void drawBar(sf::RenderWindow & window);
	std::vector<DrawTool*>  getDrawTools() { return drawTools; };
	std::vector<MainTool*>  getMainTools() { return mainTools; };
	DrawTool * getSelected() { return selected; };
	void setSelected(DrawTool * t) { selected = t; };
};

#endif //__TOOLBAR_H__
