#pragma once
using namespace std;

class Map
{
public:
	Map();
	~Map();
};

const enum Tiles //differentes tuiles dessin
{
	//Element Fixes
	BUSHES,
	GRASS,
	// Serpent
	BODY_NORTH,
	BODY_SOUTH,
	BODY_EAST,
	BODY_WEST,
	HEAD_NORTH,
	HEAD_SOUTH,
	HEAD_EAST,
	HEAD_WEST,
	//Autres
	FRUIT,
	EMPTY,
};

