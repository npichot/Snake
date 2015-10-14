#include "Map.h"
#include "Main.h"


// La map prend la forme d'une matrice où chaque élément symbolise un élément du décor
Map::Map()
{
	int row, column;//Paramètre de la map, nombre 
	int tile_size = 32; //Chaque élement de la map est représenté par un carré de 32*32

	//Calcule des paramètres 
	column = floor((WINDOW_WIDTH - 3 * tile_size) / tile_size);//On prévoit une marge min de 3 tile (~100 px)
	row= floor((WINDOW_HEIGHT - 3 * tile_size) / tile_size);
	
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
