#ifndef __MAPCREATION_H__
#define __MAPCREATION_H__

#include "Toolbar.h"

/*
Classe permettant d'afficher tout l'environnement de creation et de le gerer par rapport aux inputs utilisateur
*/
class MapCreation
{
private:
	
	Toolbar tb;
public:
	MapCreation();
	~MapCreation();
	void executeInterface(sf::RenderWindow & window, Map & m);
};

#endif // !__MAPCREATION_H__