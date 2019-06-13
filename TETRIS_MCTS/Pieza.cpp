#include "Pieza.h"

Pieza::Pieza()
{
	Color = 1 + rand() % 6;
	Origen.Pos[0] = 13;
	Origen.Pos[1] = 2;
}

Pieza::Pieza(Coordenada Perifericos[7][3])
{
	Color = 1 + rand() % 6;
	Origen.Pos[0] = 13;
	Origen.Pos[1] = 2;

	int r = rand() % 7;
	for (int i = 0; i < 3; i++)
	{
		Periferia[i] = Perifericos[r][i];
	}
}


Pieza::~Pieza() { }

//-----------------------------------------------------
//Función de la estructura pieza para hallar la posicion de dado bloque
Coordenada Pieza::Posicion(int n) const
{
	Coordenada R = { Origen.Pos[0], Origen.Pos[1] };

	if (n != 0)
	{
		R.Pos[0] += Periferia[n - 1].Pos[0];
		R.Pos[1] += Periferia[n - 1].Pos[1];
	}

	return R;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Función para rotar coordenadas a la derecha
Coordenada Pieza::rotarDerecha(const Coordenada & Posi)
{
	Coordenada R = { -Posi.Pos[1], Posi.Pos[0] };
	return R;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Función para rotar coordenadas a la derecha
Coordenada Pieza::rotarIzquierda(const Coordenada & Posi)
{
	Coordenada R = { Posi.Pos[1], -Posi.Pos[0] };
	return R;
}
//-----------------------------------------------------
