#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__
#include "Tool.h"
#include <iostream>

class DrawTool :
	public Tool
{
private:
	Tiles t;
	bool activated;
public:
	DrawTool(sf::Texture t, std::string s, bool b, Tiles tile);
	~DrawTool();
	bool isActivated() { return activated; };
	bool execute(int x0, int y0, int x, int y, Map & map) override;
	void activate(bool b);
};

#endif // !__DRAWTOOL_H__
