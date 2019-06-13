#pragma once
#include "Coordenada.h"
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace std;
class Pieza
{
public:
	Pieza();
	Pieza(Coordenada Perifericos[7][3]);
	~Pieza();

	Coordenada Origen;//Bloque central {posicion absoluta}
	Coordenada Periferia[3];//Bloque de alrededor {posicion relativa al origen}
	int Color;

	Coordenada Posicion(int n) const;//Posicion de determinado bloque, entre 0 y 3, 0 es origen, 1 - 3 periféricos
	Coordenada rotarDerecha(const Coordenada &Posi);
	Coordenada rotarIzquierda(const Coordenada &Posi);
};

