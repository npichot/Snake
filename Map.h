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
	std::vector < std::vector <sf::Sprite> > field; // Le terrain ne peut pas etre modifie directement. Notamment sa taille est calculee et fixee une fois au debut.
	sf::Texture * textures[9];
	//Parameters of the game area
	int width, height;
	double marginLeft, marginTop;
    std::vector<std::vector<int>> BadFruits;
	std::pair<int, int> cherry;
	/*
	Setter pour cherry
	*/
	void setCherry(int i, int j) { cherry = std::pair<int, int>(i, j); };
    
public:
	/*
	Initialisation de la map en fonction de la taille de l'ecran
	*/
	Map(std::string filename, sf::RenderWindow const & window, bool gridOn);
	~Map();
	Map(Map & map, sf::RenderWindow & window, bool gridOn);
	
	/*
	Utilis� par le constructeur par copie
	*/
	Map * clone(Map & map, sf::RenderWindow & window, bool gridOn);

	/*
	Methode pour modifier indirectement les elements de la map
	On modifie l'element a la position (i,j) par la Tile t
	*/
	void updateField(int i, int j, Tiles t);

	/*
	Recuperer la tile a l'emplacement (i, j)
	*/
	Tiles getTile(int i, int j);

	/*
	Methode pour dessiner la map dans la fenetre
	*/
	void drawField(sf::RenderWindow & window);

	/*
	Methode pour intitialiser la map a partir d'un fichier
	*/
	void loadMapFromFile(std::string filename);

	/*
	Methode pour la ligne potentielle correspondant � une position de la souris
	*/
	int getRowFromMouseCoordinate(int x, int y);

	/*
	Methode pour la colonne potentielle correspondant � une position de la souris
	*/
	int getColumnFromMouseCoordinate(int x, int y);

	/*
	Methode pour renvoyer une copie du field
	*/
	std::vector<std::vector<sf::Sprite>> getField() const { return field; };
	
	/*
	Methode pour faire apparaitre un fruit aleatoirement
	*/
	void popFruit();
    
    /*
     Methodes pour supprimer les mauvais fruits
     */
    void decreaseLifetimeFruits();

	/*
	Getter pour cherry
	*/
	std::pair<int, int> getCherry() { return cherry; };
    
    void deleteFruits();
};

#endif


