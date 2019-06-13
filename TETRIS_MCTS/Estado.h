#pragma once
#include "MCTS.h"
#include "Pieza.h"

using namespace dr;
using namespace mcts;
using namespace std;

namespace tetra 
{
	const enum mover { movDer = 0, movIzq};
	const enum rotar{rot=0};

	//Estructura que basa los movimientos de la ficha
	struct Accion
	{
		Accion(mover m=movDer):mov(m){}
		mover mov;

		Accion(rotar r = rot) :rotate() {}
		mover rotate;
	};

	class Estado
	{
	public:
		Estado();
		~Estado();

		//Funcion para terminar las iteraciones de ser que se termino el juego
		bool terminarIteraciones();

		//ID del agente, basado en 0, para la decisión que hará el agente
		int agenteID();

		//Funcion encargada de aplicar la accion
		void aplicarAccion(const Accion &accion);

		//Funcion que retorna las acciones posibles del estado
		void obtenerAccion(vector<Accion> &acciones);

		//Toma una acción al azar, retorna falso si no encuentran acciones
		bool obtenerAccionAleatoria(Accion &accion);

		//Evalua el estado y retorna un vector de recompensas para cada agente
		const float evaluar() const;

		//Funcion para reiniciar el sistema con las variables
		void reiniciar();

		//--------------------------------------------------------------
		//Implementación específica
		struct 
		{
			Pieza P; //Datos de la pieza para conocer sobre ella
			bool final;	        //Conocer cuando terminar las iteraciones
			int puntos;		//Conocer el puntaje que tiene para saber como pasar de nivel
			bool lineaCompleta;	//Saber si completo una línea
		} data;
	};
}


