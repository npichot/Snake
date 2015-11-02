#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__
#include "Tool.h"

class DrawTool :
	public Tool
{
private:
	Tiles t;
public:
	DrawTool(sf::Texture t, std::string s, bool b, Tiles tile);
	~DrawTool();
	Tiles getTile() { return t; };
	bool execute(int x, int y, Map & map) override;
};

#endif __DRAWTOOL_H__
