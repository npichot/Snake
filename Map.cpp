#include "Map.h"
#include "Main.h"


// La map prend la forme d'une matrice où chaque élément symbolise un élément du décor
Map::Map()
{
	int row_number, column_number;//Paramètre de la map, nombre 

	//Calcule des paramètres 
	column_number = floor((WINDOW_WIDTH - 3 * TILE_SIZE) / TILE_SIZE);//On prévoit une marge min de 3 tile (~100 px)
	row_number= floor((WINDOW_HEIGHT - 3 * TILE_SIZE) / TILE_SIZE);
	
	//Remplissage de la map
	for (int i = 0; i < row_number; ++i)
	{
		vector<Tiles> row;
		for (int j = 0; j < column_number; ++j)
			row.push_back(EMPTY);
		field.push_back(row);
	}
}

Map::~Map()
{
}

void Map::updateField(int i, int j, Tiles t)
{
	if (i >= 0 && i < field.size())
	{
		if (j >= 0 && j < field[0].size())
			field[i][j] = t;
	}
	else
	{
		printf("Error 1 : Can't update the tile because the coordinates are outside the field");
	}
}

Tiles Map::getTile(int i, int j, Tiles t)
{
	if (i >= 0 && i < field.size())
	{
		if (j >= 0 && j < field[0].size())
			return field[i][j];
	}
	else
	{
		printf("Error 2 : Can't get the tile because the coordinates are outside the field");
	}
}

void Map::drawField(RenderWindow * window)
{
	//Chargement du fond
		//On initialise les paramètres
	int width = TILE_SIZE* field[0].size();
	int height = TILE_SIZE* field.size();
	double marginLeft = (WINDOW_WIDTH - width) / 2;
	double marginTop = (WINDOW_HEIGHT - height) / 2;

		//On construit le rectangle d'arrière plan
	RectangleShape background;
	background.setPosition(marginLeft, marginTop);
	background.setSize(Vector2f(width, height));
	background.setFillColor(Color::Green);
	background.setOutlineColor(Color::Red);
	background.setOutlineThickness(5);
	window->draw(background);
}
