#include "Map.h"

using namespace sf;
using namespace std;

// La map prend la forme d'une matrice où chaque element symbolise un element du decor
Map::Map(string filename, RenderWindow & window)
	:window(window)
{
	int row_number, column_number;//Parametre de la map, nombre 

	//Calcule des parametres 
	column_number = floor((window.getSize().x - 3 * TILE_SIZE) / TILE_SIZE);//On prevoit une marge min de 3 tile (~100 px)
	row_number= floor((window.getSize().y - 3 * TILE_SIZE) / TILE_SIZE);
	
	//Remplissage de la map
	for (int i = 0; i < row_number; ++i)
	{
		vector<Tiles> row;
		for (int j = 0; j < column_number; ++j)
			row.push_back(EMPTY);
		field.push_back(row);
	}

	if (!filename.empty())
		loadMapFromFile(filename);

}

Map::~Map()
{
}

void Map::updateField(int i, int j, Tiles t)
{
	if (i >= 0 && i < field.size())
		if (j >= 0 && j < field[0].size())
		{
			field[i][j] = t;
			return;
		}
	printf("Error 1 : Can't update the tile because the coordinates are outside the field");
}

Tiles Map::getTile(int i, int j)
{
	if (i >= 0 && i < field.size())
	{
		if (j >= 0 && j < field[0].size())
			return field[i][j];
	}
	else
	{
		printf("Error 2 : Can't get the tile because the coordinates are outside the field");
		return UNKNOWN;
	}
}

void Map::drawField()
{
	//Chargement du fond
		//On initialise les parametres
	int width = TILE_SIZE* field[0].size();
	int height = TILE_SIZE* field.size();
	double marginLeft = (window.getSize().x - width) / 2;
	double marginTop = (window.getSize().y - height) / 2;

		//On construit le rectangle d'arriere plan
	RectangleShape background;
	background.setPosition(marginLeft, marginTop);
	background.setSize(Vector2f(width, height));
	background.setFillColor(Color::Green);
	window.draw(background);

	//On affiche les tiles du terrain
	Texture texture;
	Texture headTexture; headTexture.loadFromFile("Ressources/head.png");
	Texture bodyTexture; bodyTexture.loadFromFile("Ressources/body.png");


	for (int i = 0; i < field.size();++i)
		for (int j = 0; j < field[i].size(); ++j)
		{
			//On debute la construction du rectangle
			Sprite tile;
			tile.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
			tile.setPosition(marginLeft + j * TILE_SIZE + TILE_SIZE / 2, marginTop + i * TILE_SIZE + TILE_SIZE / 2);

			//On initialise le fond en fonction de la nature de la tile
			switch (getTile(i,j))
			{
			case BUSHES :
				if (texture.loadFromFile("Ressources/tree.png"))
					tile.setTexture(texture);
				break;
			case HEAD_NORTH:
				tile.setTexture(headTexture);
				break;
			case HEAD_SOUTH:
				tile.setTexture(headTexture);
				tile.setRotation(180);
				break;
			case HEAD_EAST:
				tile.setTexture(headTexture);
				tile.setRotation(90);
				break;
			case HEAD_WEST:
				tile.setTexture(headTexture);
				tile.setRotation(270);
				break;
			case BODY_NORTH:
			case BODY_SOUTH:
				tile.setTexture(bodyTexture);
				break;
			case BODY_EAST:
			case BODY_WEST:
				tile.setTexture(bodyTexture);
				tile.setRotation(90);
				break;
			case FRUIT:
				if (texture.loadFromFile("Ressources/cherry.png"))
					tile.setTexture(texture);
				break;
			default:
				if (texture.loadFromFile("Ressources/grass.png"))
					tile.setTexture(texture);
				break;
			}

			//On ajoute la tile a la fenetre
			window.draw(tile);
		}
}

void Map::loadMapFromFile(string filename)
{		
		//on essaye d'ouvrir le fichier en lecture
		ifstream is(filename);
		if (!is)
		{
			printf("Fichier introuvable");
		}
		int i, j;
		string tile;

		//On lit les lignes une par une 
		while (is >> i>> j>> tile)
		{
			updateField(i, j, getEnumValue.at(tile));//On met a jour la map
		}

		// close the opened file.
		is.close();

}



