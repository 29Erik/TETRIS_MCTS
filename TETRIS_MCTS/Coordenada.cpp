#include "Coordenada.h"

Coordenada::Coordenada()
{
	Pos[0] = 0;
	Pos[1] = 0;
}

Coordenada::Coordenada(int x, int y)
{
	Pos[0] = x;
	Pos[1] = y;
}

Coordenada::~Coordenada() { }
