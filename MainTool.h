#pragma once
#include "Tool.h"
class MainTool :
	public Tool
{
private:
	sf::Font font;
	
	std::string checkMap(Map & map);
	void saveMap(Map map);
	bool isSaveClicked(int x, int y);
	bool isCancelClicked(int x, int y);
	void buildTheWindow(sf::RenderWindow & window);
	void writeConfig(std::string name, Map map);

public:
	MainTool(sf::Texture t, std::string s);
	~MainTool();
	bool execute(int x0, int y0, int x, int y, Map & map) override;
};

