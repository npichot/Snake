#pragma once
using namespace std;

//Classe pour le controle des commandes claviers
class Input
{
public:
	Input();
	~Input();
};


typedef enum 
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ESCAPE,
}Button;