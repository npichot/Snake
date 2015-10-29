#ifndef __MAPCREATION_H__
#define __MAPCREATION_H__

#include "Map.h"

/*
Classe permettant d'afficher tout l'environnement de creation et de le gerer par rapport aux inputs utilisateur
*/
class MapCreation
{
private:
	Map m;
public:
	MapCreation(Map m);
	~MapCreation();
	void launchInterface();
};

#endif // !__MAPCREATION_H__