#ifndef __INPUT_H_INCLUDED__
#define __INPUT_H_INCLUDED__

//Classe pour le controle des commandes claviers
class Input
{
public:
	Input();
	~Input();
};


enum Button
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ESCAPE,
};

#endif