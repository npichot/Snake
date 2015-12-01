#include "Map.h"

using namespace sf;
using namespace std;

/*
Le constructeur de la map permet de definir le terrain (gameField) avec tous ses paramètres.
On définit ainsi sa taille par rapport à la fenêtre. Ensuite les textures qui vont servir à 
l'affichage sont chargées. Enfin on remplit le terrain avec des elements vides par defaut.
Ce remplissage est ensuite eventuellement ecrase par le chargement d'un fichier de configuration
de terrain.
*/
Map::Map(string filename, RenderWindow const & window, bool gridOn)
{
	int row_number, column_number;//Parametre de la map, nombre 
	column_number = floor((window.getSize().x - 3 * TILE_SIZE) / TILE_SIZE);//On prevoit une marge min de 3 tile (~100 px)
	row_number = floor((window.getSize().y - 3 * TILE_SIZE) / TILE_SIZE);

	//On initialise les parametres pour les sprites
	fieldWidth = TILE_SIZE * column_number;
	fieldHeight = TILE_SIZE * row_number;
	fieldMarginLeft = (window.getSize().x - fieldWidth) / 2;
	fieldMarginTop = (window.getSize().y - fieldHeight) / 2;

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
			tile.setPosition(fieldMarginLeft + j * TILE_SIZE + TILE_SIZE / 2, fieldMarginTop + i * TILE_SIZE + TILE_SIZE / 2);
			row.push_back(tile);
		}
		gameField.push_back(row);
	}

	if (!filename.empty())
		loadMapFromFile(filename);
}

/*
Ce constructeur est le constructeur par copie. Lorsqu'un copie d'une map est 
effectuée on lui affecte des nouveaux pointeurs pour les textures pour éviter
que celles-ci ne sont détruites à la destruction de la copie.
Cette fonction est uniquement appelé par la fonction clone.
*/
Map::Map(Map & map, sf::RenderWindow & window, bool gridOn)
	:Map("", window, gridOn)
{
	for (int i = 0; i < gameField.size(); ++i)
		for (int j = 0; j < gameField[i].size(); ++j)
			updateGameField(i, j, map.getTile(i, j));
}

Map::~Map()
{
}

/*
La fonction clone permet de renvoyer un pointeur vers une copie de la map
passée en paramètre.
*/
Map * Map::clone(Map & map, RenderWindow & window, bool gridOn)
{
	return new Map(map,window,gridOn);
}

/*
Cette fonction est utilisée par le constructeur pour remplir une map
à partir d'un fichier de configuration placé dans le dossier MapConfig.
Dans ce fichier chaque ligne represente une tile de la map. Les lignes 
sont définies sur le format suivant line_number column_number tile_number
*/
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
	while (is >> i >> j >> tile)
	{
		updateGameField(i, j, Tiles(tile));//On met a jour la map
	}

	// close the opened file.
	is.close();
}

/*
La fonction suivante met à jour une element du gameField de coordonnées
i et j avec la tile t.
*/
void Map::updateGameField(int i, int j, Tiles t)
{
	if (i >= 0 && i < gameField.size())
		if (j >= 0 && j < gameField[0].size())
		{
			gameField[i][j].setTexture(*textures[(int)floor(t / 10)]);
			gameField[i][j].setRotation((t - ((int)floor(t / 10)) * 10)*90);
			return;
		}
	printf("Error 1 : Can't update the tile because the coordinates are outside the field");
}

/*
Cette fonction permet de recuperer le type de tile qui se trouve 
aux coordonnees i et j du gameField.
*/
Tiles Map::getTile(int i, int j)
{
	if (i >= 0 && i < gameField.size())
	{
		if (j >= 0 && j < gameField[0].size())
		{
			for (int h = 0; h < sizeof(textures)/sizeof(Texture*); h++)
				if (gameField[i][j].getTexture() == textures[h])
					return static_cast<Tiles>(h * 10 + (int)floor(gameField[i][j].getRotation() / 90));
		}
			
	}
	else
	{
		printf("Error 2 : Can't get the tile because the coordinates are outside the field");
		return UNKNOWN;
	}
}

/*
Cette fonction permet de creer le rendu de la map dans la fenêtre passée
en paramètres. Tout les elements du gameField sont dessines dans la fenêtre.
*/
void Map::drawField(RenderWindow & window)
{
	//Chargement du fond

	//On construit le rectangle d'arriere plan qui permet de faire la grille dans le cas de création de map
	RectangleShape background;
	background.setPosition(fieldMarginLeft, fieldMarginTop);
	background.setSize(Vector2f(fieldWidth, fieldHeight));
	background.setFillColor(Color::Blue);
	window.draw(background);

	//On affiche les tiles du terrain
	for (int i = 0; i < gameField.size();++i)
		for (int j = 0; j < gameField[i].size(); ++j)
			window.draw(gameField[i][j]);
}

/*
Cette fonction prend en entree la position (x,y) de la souris sur la fenetre.
Si cette position correspond à une case du gameField, la fonction renvoie la 
ligne associée à cette case.
*/
int Map::getRowFromMouseCoordinate(int x, int y)
{
	if (floor((y - fieldMarginTop) / TILE_SIZE) < gameField.size() && (y - fieldMarginTop) >= 0)
		return floor((y - fieldMarginTop) / TILE_SIZE);

	return -1;//Row not found
}

/*
Cette fonction prend en entree la position (x,y) de la souris sur la fenetre.
Si cette position correspond à une case du gameField, la fonction renvoie la
colonne associée à cette case.
*/
int Map::getColumnFromMouseCoordinate(int x, int y)
{
	if (floor((x - fieldMarginLeft) / TILE_SIZE) < gameField[0].size() && (x - fieldMarginLeft) >= 0)
		return floor((x - fieldMarginLeft) / TILE_SIZE);

	return -1;//Row not found
}

/*
Cette fonction fait apparaitre les fruits sur le gameField dans des endroits
vides. 
A chaque fois que cette fonction est appelee une cerise est placee sur le terrain.
Avec une probilite de 20%, on place egalement un fruit aux effets negatifs.
*/
void Map::popFruit()
{
	//Apparition cerise
    int i(0), j(0);
	do
	{
		srand(time(NULL)); 
		i = rand() % (gameField.size() - 3) + 1;
		j = rand() % (gameField[0].size() - 3) + 1;
	} while (getTile(i, j) != EMPTY);
    updateGameField(i, j, CHERRY);
	setCherry(i, j);
    
	//Apparition eventuelle d'un autre fruit
	vector<Tiles> Fruits;
	Fruits.push_back(BANANA);
	Fruits.push_back(GRAPE);
	Fruits.push_back(LEMON);
	Fruits.push_back(STRAWBERRY);
	int k(rand() % 100 + 1), l(0), m(0);
    
    if( k < 80)
    {
        do
        {
            l = rand() % (gameField.size() - 3) + 1;
            m = rand() % (gameField[0].size() - 3) + 1;
        } while (getTile(l, m) != EMPTY);
        int n = rand() % (Fruits.size());
        updateGameField(l, m, Fruits[n]);
		badFruits.push_back({ l, m, 50 });
    }
		
}

/*
Cette fonction gere la duree d'affichage des fruits negatifs sur le terrain
en les reduisant de 1 a chaque tour de la boucle du jeu.
*/
void Map::decreaseLifetimeFruits()
{
    for (int i = 0; i < badFruits.size(); ++i) 
	{
        --badFruits[i][2];
		if (badFruits[i][2] == 0)
			updateGameField(badFruits[i][0], badFruits[i][1], EMPTY);
    }
}
