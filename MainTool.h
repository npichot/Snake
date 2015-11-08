#pragma once
#include "Tool.h"
class MainTool :
	public Tool
{
public:
	MainTool(sf::Texture t, std::string s);
	~MainTool();
	bool execute(int x0, int y0, int x, int y, Map & map) override;
	void saveMap();
};

