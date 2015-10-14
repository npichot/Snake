#include "Map.h"
#include "Main.h"


// La map prend la forme d'une matrice où chaque élément symbolise un élément du décor
Map::Map()
{
	int row, column;//Paramètre de la map, nombre 

	//Calcule des paramètres 
	column = floor((WINDOW_WIDTH - 3 * TILE_SIZE) / TILE_SIZE);//On prévoit une marge min de 3 tile (~100 px)
	row= floor((WINDOW_HEIGHT - 3 * TILE_SIZE) / TILE_SIZE);
	
	//Remplissage de la map
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < column; ++j)
			field[i].push_back(EMPTY);
}

Map::~Map()
{
}

void Map::updateField()
{
}

void Map::draw(RenderWindow * window)
{
}
