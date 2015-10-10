#pragma once
using namespace std;

//Classe pour le controle des commandes claviers
class Input
{
public:
	Input();
	~Input();
};


const enum Button
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ESCAPE,
};