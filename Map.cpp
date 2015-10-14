#include "Map.h"
#include "Main.h"


// La map prend la forme d'une matrice o� chaque �l�ment symbolise un �l�ment du d�cor
Map::Map()
{
	int row, column;//Param�tre de la map, nombre 
	int tile_size = 32; //Chaque �lement de la map est repr�sent� par un carr� de 32*32

	//Calcule des param�tres 
	column = floor((WINDOW_WIDTH - 3 * tile_size) / tile_size);//On pr�voit une marge min de 3 tile (~100 px)
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
