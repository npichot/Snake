#include "Map.h"

using namespace sf;
using namespace std;

// La map prend la forme d'une matrice o� chaque element symbolise un element du decor
Map::Map(string filename, RenderWindow const & window, bool gridOn)
{
	int row_number, column_number;//Parametre de la map, nombre 
	column_number = floor((window.getSize().x - 3 * TILE_SIZE) / TILE_SIZE);//On prevoit une marge min de 3 tile (~100 px)
	row_number = floor((window.getSize().y - 3 * TILE_SIZE) / TILE_SIZE);

	//On initialise les parametres pour les sprites
	width = TILE_SIZE * column_number;
	height = TILE_SIZE * row_number;
	marginLeft = (window.getSize().x - width) / 2;
	marginTop = (window.getSize().y - height) / 2;

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
	t3.loadFromFile("Ressources/grass.png");
	textures[3] = new Texture(t3);
    Texture t4;
    t4.loadFromFile("Ressources/cherry.png");
    textures[4] = new Texture(t4);
    Texture t5;
    t5.loadFromFile("Ressources/banana.png");
    textures[5] = new Texture(t5);
    Texture t6;
    t6.loadFromFile("Ressources/grape.png");
    textures[6] = new Texture(t6);
    Texture t7;
    t7.loadFromFile("Ressources/lemon.png");
    textures[7] = new Texture(t7);
    Texture t8;
    t8.loadFromFile("Ressources/strawberry.png");
    textures[8] = new Texture(t8);
	
	//Remplissage de la map
	Sprite tile;
	if (gridOn)
		tile.setScale(0.95, 0.95);
	tile.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	tile.setTexture(*textures[3]);
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
}

Map::Map(Map & map, sf::RenderWindow & window, bool gridOn)
	:Map("", window, gridOn)
{
	for (int i = 0; i < field.size(); ++i)
		for (int j = 0; j < field[i].size(); ++j)
			updateField(i, j, map.getTile(i, j));
}

Map * Map::clone(Map & map, RenderWindow & window, bool gridOn)
{
	return new Map(map,window,gridOn);
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

void Map::drawField(RenderWindow & window)
{
	//Chargement du fond

	//On construit le rectangle d'arriere plan qui permet de faire la grille dans le cas de cr�ation de map
	RectangleShape background;
	background.setPosition(marginLeft, marginTop);
	background.setSize(Vector2f(width, height));
	background.setFillColor(Color::Blue);
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
		int i, j, tile;

		//On lit les lignes une par une 
		while (is >> i>> j>> tile)
		{
			updateField(i, j, Tiles(tile));//On met a jour la map
		}

		// close the opened file.
		is.close();
}

int Map::getRowFromMouseCoordinate(int x, int y)
{
	if (floor((y - marginTop) / TILE_SIZE) < field.size() && (y - marginTop) >= 0)
		return floor((y - marginTop) / TILE_SIZE);

	return -1;//Row not found
}

int Map::getColumnFromMouseCoordinate(int x, int y)
{
	if (floor((x - marginLeft) / TILE_SIZE) < field[0].size() && (x - marginLeft) >= 0)
		return floor((x - marginLeft) / TILE_SIZE);

	return -1;//Row not found
}

void Map::popFruit()
{
    vector<Tiles> Fruits;
    Fruits.push_back(CHERRY);
    Fruits.push_back(BANANA);
    Fruits.push_back(GRAPE);
    Fruits.push_back(LEMON);
    Fruits.push_back(STRAWBERRY);
    int i(0), j(0);
	do
	{
		srand(time(NULL)); //Initialisation du timer
		i = rand() % (field.size() - 3) + 1;
		j = rand() % (field[0].size() - 3) + 1;
	} while (getTile(i, j) != EMPTY);
    updateField(i, j, CHERRY);
	setCherry(i, j);
    
    //Faire apparaitre un fruit mauvais random avec une probabilit� de 20%
    
    int k(rand()%100+1),l(0), m(0);
    vector<int> BadFruit;//On cr�e un vecteur avec les informations du fruit mauvais
    
    if( k < 80)//G�re la probabilit� de 20%
    {
        do
        {
            l = rand() % (field.size() - 3) + 1;
            m = rand() % (field[0].size() - 3) + 1;
        } while (getTile(l, m) != EMPTY);
        int n = rand() % (Fruits.size()-1)+1;
        updateField(l, m, Fruits[n]);
        BadFruit.push_back(l);//On stock la ligne du fruit qui est amen� � disparaitre
        BadFruit.push_back(m);//On stock la colonne du fruit amen� � disparaitre
        BadFruit.push_back(50);//Nombre de cycles pendant lequel le fruit sera visible
        BadFruits.push_back(BadFruit);
        
    }
		
}

void Map::decreaseLifetimeFruits()
{
    for (int i = 0; i < BadFruits.size(); ++i) {
        --BadFruits[i][2];
    }
}

void Map::deleteFruits()
{
    for (int i = 0; i < BadFruits.size(); ++i) {
        if (BadFruits[i][2] == 0)
            updateField(BadFruits[i][0], BadFruits[i][1], EMPTY);
    }
    
}

