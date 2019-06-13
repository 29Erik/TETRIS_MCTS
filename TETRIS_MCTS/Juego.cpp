#include "miniwin.h"
#include "Estado.h"
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace miniwin;
using namespace std;

//Tamaño de cada cuadrado del juego
const int Tamaño = 25;
const int Filas = 20;
const int Columnas = 10;
const int Margen = 20;

//Booleano para detectar que el juego ya finalizo
bool Termino = false;

//Matriz del tablero para jugar con sus dimensiones
typedef int Tablero[Columnas][Filas];

//------------------------------------------------------
//Función que se encarga de pintar cada cuadrado de
//las piezas del juego
void Cuadrado(int x, int y)
{
	int coord_x = x * Tamaño;
	int coord_y = y * Tamaño;
	int espacio = 1;//Espacio para mostrar diferentes cuadrados

	rectangulo_lleno(Margen + coord_x + espacio, Margen + coord_y + espacio, Margen + coord_x + Tamaño, Margen + coord_y + Tamaño);
}
//------------------------------------------------------

//------------------------------------------------------
//Funcion para pintar una pieza
void Pinta_Pieza(const Pieza &P)
{
	color(P.Color);
	for (int i = 0; i < 4; i++)
	{
		Coordenada C = P.Posicion(i);
		Cuadrado(C.Pos[0], C.Pos[1]);
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Función para rotar piezas a la derecha
void Rota_Derecha(Pieza &P)
{
	for (int i = 0; i < 3; i++)
	{
		P.Periferia[i] = P.rotarDerecha(P.Periferia[i]);
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Función para rotar piezas a la Izquierda
void Rota_Izquierda(Pieza &P)
{
	for (int i = 0; i < 3; i++)
	{
		P.Periferia[i] = P.rotarIzquierda(P.Periferia[i]);
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Función para llenar el tablero con 0
void Vacia_Tablero(Tablero &T)
{
	for (int i = 0; i < Columnas; i++)
	{
		for (int j = 0; j < Filas; j++)
		{
			T[i][j] = NEGRO;//Casillas vacias colocarlas
		}
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion para pintar el tablero
void Pinta_Tablero(Tablero &T)
{
	for (int i = 0; i < Columnas; i++)
	{
		for (int j = 0; j < Filas; j++)
		{
			color(T[i][j]);//Color de dicha  casilla
			Cuadrado(i, j);
		}
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion diseñada para fijar la pieza al tablero en el fondo
void Incrustar_Pieza(Tablero &T, const Pieza &P)
{
	int OX = P.Origen.Pos[0];
	int OY = P.Origen.Pos[1];
	T[OX][OY] = P.Color;
	for (int i = 0; i < 4; i++)
	{
		Coordenada C = P.Posicion(i);
		T[C.Pos[0]][C.Pos[1]] = P.Color;
	}
	
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion que detecta la colision de la ficha con los bordes
bool Tablero_Colision(const Tablero &T, const Pieza &P)
{
	bool Colision = false;
	for (int i = 0; i < 4; i++)
	{
		Coordenada C = P.Posicion(i);
		//Comprobar límites
		if (C.Pos[0]<0 || C.Pos[0]>=Columnas)
		{
			return true;
		}
		if (C.Pos[1] < 0 || C.Pos[1] >= Filas)
		{
			return true;
		}
		//Mirar residuos en el tablero
		if (T[C.Pos[0]][C.Pos[1]] != NEGRO)
		{
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Matriz que almacena los blosuqe periféricos de cada figura del tetris
const Coordenada Perifericos[7][3] = {
	{{1,0},{0,1},{1,1}},//Figura Cuadrado
	{{1,0},{-1,1},{0,1}},//Figura S
	{{0,1},{1,1},{-1,0}},//Figura Z
	{{0,-1},{0,1},{1,1}},//Figura L
	{{0,-1},{0,1},{-1,1}},//Figura L revés
	{{0,-1},{0,1},{0,2}},//Figura Línea
	{{-1,0},{1,0},{0,1}},//Figura T
};
//-------------------------------------------------------

//-------------------------------------------------------
//Generar piezas al azar
void Pieza_Nueva(Pieza &P)
{
	P.Color = 1 + rand() % 6;
	P.Origen.Pos[0] = 13;
	P.Origen.Pos[1] = 2;

	int r = rand() % 7;
	for (int i = 0; i < 3; i++)
	{
		P.Periferia[i] = Perifericos[r][i];
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion para validar si una fila ya esta llena
bool Tablero_Fila_Llena(const Tablero &T, int Fila)
{
	for (int i = 0; i < Columnas; i++)
	{
		if (T[i][Fila] == NEGRO)
		{
			return false;
		}
	}
	return true;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion para generar la re posicion cuando se elimina fila
void Tablero_Colapsa(Tablero &T, int Fila)
{
	//Copiar en la fila de abajo, lo que tiene la fila de arriba
	for (int i =Fila; i > 0; i--)
	{
		for (int j = 0; j < Columnas; j++)
		{
			T[j][i] = T[j][i - 1];
		}
	}
	//Vaciar la de arriba
	for (int j = 0; j < Columnas; j++)
	{
		T[j][0] = NEGRO;
	}
}
//-------------------------------------------------------

//-------------------------------------------------------
//
int Tablero_Cuenta_Lineas(Tablero &T)
{
	int fila = Filas - 1;
	int cont = 0;
	while (fila>=0)
	{
		if (Tablero_Fila_Llena(T, fila))
		{
			Tablero_Colapsa(T, fila);
			cont++;
		}
		else
		{
			fila--;
		}
	}
	return cont;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion para validar puntos y volverlos string
string A_String(int Puntos)
{
	stringstream sout;
	sout << Puntos;
	return sout.str();
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion encargada de graficar
void Repinta(Tablero &T, const Pieza &P, const Pieza &Sig, int Pts, int level)
{
	const int Ancho = Tamaño * Columnas;
	const int Alto = Tamaño * Filas;
	//Borrar el rastro de movimiento
	borra();

	//Pintar tablero
	Pinta_Tablero(T);

	//Borde del tablero
	color_rgb(156,20,241);
	linea(Margen, Margen, Margen, Margen + Alto);
	linea(Margen, Margen + Alto, Margen + Ancho, Margen + Alto);
	linea(Margen + Ancho, Margen + Alto, Margen + Ancho, Margen);
	linea(Margen, Margen, Margen + Ancho, Margen);

	color(BLANCO);
	texto(40+ Ancho, 20, "Pieza Siguiente");
	texto(40 + Ancho, 150, "Nivel");
	texto(40 + Ancho, 170, A_String(level + 1));
	texto(40 + Ancho, 250, "Puntos");
	texto(40 + Ancho, 270, A_String(Pts));

	Pinta_Pieza(P);
	Pinta_Pieza(Sig);
	refresca();
}
//-------------------------------------------------------

//-------------------------------------------------------
//Variable que almacena los puntajes para subir de nivel
const int Puntos_Nivel[11] = { 40, 80,120, 160, 200, 240, 280, 320, 360, 400, 440 };
//-------------------------------------------------------

//-------------------------------------------------------
//Variable para aumentar la dificultad disminuyendo el tiempo de acción
const int tics_nivel[11] = {45, 40, 35, 30, 27, 23, 25, 20, 16, 10, 6};
//-------------------------------------------------------

//-------------------------------------------------------
//Función que genera el Game Over
void Game_Over()
{
	color(BLANCO);
	rectangulo_lleno(0, 100, 450, 450);
	color(NEGRO);
	texto(160, 270, "GAME OVER LOSER");
	refresca();
	espera(3000);
	vcierra();
}
//-------------------------------------------------------

int main()
{
	//Tamaño de a ventana del juego
	vredimensiona(Tamaño * Columnas + 200, Tamaño * Filas + 50);
	srand(time(0));//Inicializamos la semilla para los números random

	int tic = 0;
	int Puntos = 0;
	int Nivel = 0;

	//Creación del tablero
	Tablero T;
	Vacia_Tablero(T);

	//Lectura de la tecla
	int Key = tecla();

	//Crear la pieza
	Pieza O ;
	Pieza_Nueva(O);
	O.Origen.Pos[0] = 13;

	Pieza Next;
	Pieza_Nueva(Next);

	Repinta(T, O, Next, Puntos, Nivel);

	//Actualización de la posición mediante las flechas
	while (Key != ESCAPE)
	{
		//-------------------------------------------------------
		//Variables que guardan la pieza actual
		Pieza Copia = O;
		//-------------------------------------------------------

		//-------------------------------------------------------
		//Generar la caida de la ficha simultaneamente
		if (Key==NINGUNA && tic> tics_nivel[Nivel])
		{
			tic = 0;
			Key = ABAJO;
		}
		//--------------------------------------------------------

		if (Key==int('N'))
		{
			Nivel++;
		}

		//-------------------------------------------------------
		//Mover las fichas
		if (Key == ABAJO)
		{
			O.Origen.Pos[1]++;
		}
		else if (Key == ARRIBA)
		{
			Rota_Derecha(O);
		}
		else if (Key == IZQUIERDA)
		{
			O.Origen.Pos[0]--;
		}
		else if (Key == DERECHA)
		{
			O.Origen.Pos[0]++;
		}
		//-------------------------------------------------------

		//-------------------------------------------------------
		//Mirar si hay colision
		if (Tablero_Colision(T, O))
		{
			//De existir colisión, deja los valores anteriores
			O = Copia;
			//-------------------------------------------------------
			//Incrustar la ficha en el tablero
			if (Key == ABAJO)
			{
				Incrustar_Pieza(T, O);
				int K = Tablero_Cuenta_Lineas(T);
				Puntos += K * K;

				if (Puntos>Puntos_Nivel[Nivel])
				{
					Nivel++;
				}

				O = Next;
				Pieza_Nueva(Next);
				O.Origen.Pos[0] = 5;
				if (Tablero_Colision(T, O))
				{
					Game_Over();
				}
			}
			//-------------------------------------------------------
		}
		//-------------------------------------------------------	

		//-------------------------------------------------------
		//Pintar la info
		if (Key != NINGUNA)
		{
			Repinta(T, O, Next, Puntos, Nivel);
		}
		//-------------------------------------------------------
		espera(30);
		tic++;
		Key = tecla();
	}

	//Cierra la ventana
	vcierra();
	return 0;
}