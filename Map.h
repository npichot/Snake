#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       

//Chaque element de la map est represente par un carre de 32*32
const int TILE_SIZE = 32;

enum Tiles //differentes tuiles du dessin
{
	//Element Fixes
	TREE=0,
	// Serpent
	BODY_NORTH=10,
	BODY_EAST=11,
	BODY_SOUTH=12,
	BODY_WEST=13,
	HEAD_NORTH=20,
	HEAD_EAST=21,
	HEAD_SOUTH=22,
	HEAD_WEST=23,
	//Autres
	EMPTY=30,
	UNKNOWN,
    //Fruits
    CHERRY=40,
    BANANA=50,
    GRAPE=60,
    LEMON=70,
    STRAWBERRY=80
};

class Map
{
private:
	//Attributs
	std::vector<std::vector<sf::Sprite> > gameField; 
	sf::Texture * textures[9];
	int fieldWidth, fieldHeight;
	double fieldMarginLeft, fieldMarginTop;
    std::vector<std::vector<int>> badFruits;
	std::pair<int, int> cherry;

	//Methodes
	void setCherry(int i, int j) { cherry = std::pair<int, int>(i, j); };
	void loadMapFromFile(std::string filename);
    
public:
	Map(std::string filename, sf::RenderWindow const & window, bool gridOn);
	Map(Map & map, sf::RenderWindow & window, bool gridOn);//Constructeur par copie
	~Map();
	Map * clone(Map & map, sf::RenderWindow & window, bool gridOn);

	void updateGameField(int i, int j, Tiles t);
	std::vector<std::vector<sf::Sprite>> getGameField() const { return gameField; };
	Tiles getTile(int i, int j);
	void drawField(sf::RenderWindow & window);
	
	int getRowFromMouseCoordinate(int x, int y);
	int getColumnFromMouseCoordinate(int x, int y);

	void popFruit();
    void decreaseLifetimeFruits();
	std::pair<int, int> getCherry() { return cherry; };
};

#endif


