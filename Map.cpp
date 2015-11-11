#include "Map.h"

using namespace sf;
using namespace std;

// La map prend la forme d'une matrice où chaque element symbolise un element du decor
Map::Map(string filename, RenderWindow & window)
	:window(window)
{
	int row_number, column_number;//Parametre de la map, nombre 
	column_number = floor((window.getSize().x - 3 * TILE_SIZE) / TILE_SIZE);//On prevoit une marge min de 3 tile (~100 px)
	row_number = floor((window.getSize().y - 3 * TILE_SIZE) / TILE_SIZE);

	//On initialise les parametres pour les sprites
	int width = TILE_SIZE * column_number;
	int height = TILE_SIZE * row_number;
	double marginLeft = (window.getSize().x - width) / 2;
	double marginTop = (window.getSize().y - height) / 2;

	//Chargement des textures
	Texture t0;
	t0.loadFromFile("Ressources/tree.png");
	textures[0] = new Texture(t0);
	Texture t1;
	t1.loadFromFile("Ressources/body.png");
	textures[1] = new Texture(t1);
	Texture t2;
	t2.loadFromFile("Ressources/head.png");
	textures[2] = new Texture(t2);
	Texture t3;
	t3.loadFromFile("Ressources/cherry.png");
	textures[3] = new Texture(t3);
	Texture t4;
	t4.loadFromFile("Ressources/grass.png");
	textures[4] = new Texture(t4);
	
	//Remplissage de la map
	Sprite tile;
	tile.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	tile.setTexture(*textures[4]);
	for (int i = 0; i < row_number; ++i)
	{
		vector<Sprite> row;
		for (int j = 0; j < column_number; ++j)
		{
			tile.setPosition(marginLeft + j * TILE_SIZE + TILE_SIZE / 2, marginTop + i * TILE_SIZE + TILE_SIZE / 2);
			row.push_back(tile);
		}
		field.push_back(row);
	}

	if (!filename.empty())
		loadMapFromFile(filename);
}

Map::~Map()
{
	for (int i = 0; i < sizeof(textures) / sizeof(Texture*); i++)
		textures[i]->~Texture();
}

void Map::updateField(int i, int j, Tiles t)
{
	if (i >= 0 && i < field.size())
		if (j >= 0 && j < field[0].size())
		{
			field[i][j].setTexture(*textures[(int)floor(t / 10)]);
			field[i][j].setRotation((t - ((int)floor(t / 10)) * 10)*90);
			return;
		}
	printf("Error 1 : Can't update the tile because the coordinates are outside the field");
}

Tiles Map::getTile(int i, int j)
{
	if (i >= 0 && i < field.size())
	{
		if (j >= 0 && j < field[0].size())
		{
			for (int h = 0; h < sizeof(textures)/sizeof(Texture*); h++)
				if (field[i][j].getTexture() == textures[h])
					return static_cast<Tiles>(h * 10 + (int)floor(field[i][j].getRotation() / 90));
		}
			
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
	for (int i = 0; i < field.size();++i)
		for (int j = 0; j < field[i].size(); ++j)
			window.draw(field[i][j]);
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



