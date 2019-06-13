#pragma once

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <cstdlib>

namespace dr 
{
	using namespace std;
	class BucleTemp 
	{		
		typedef chrono::high_resolution_clock Reloj;
		typedef chrono::microseconds Unidades;
	public:
		bool salida_cmd;

		Reloj::time_point tiempo_inicial;
		Reloj::time_point tiempo_inicial_ciclo;

		Unidades promedio_duracion_ciclo;
		Unidades duracion_depuracion;

		BucleTemp() :salida_cmd(false) {}

		//--------------------------------------------------------------
		// inicializamos el temporalizador llamado antes de que inicie el ciclo
		void iniciar()
		{
			tiempo_inicial = Reloj::now();
			iteraciones = 0;
		}

		//--------------------------------------------------------------
		// indica el inicio del ciclo
		void iniciar_ciclo()
		{
			tiempo_inicial_ciclo = Reloj::now();
			iteraciones++;
		}

		//--------------------------------------------------------------
		// indica el final del ciclo
		void finalizar_ciclo()
		{
			auto tiempo_final_ciclo = Reloj::now();
			auto duracion_ciclo_actual = chrono::duration_cast<Unidades>(tiempo_final_ciclo - tiempo_inicial_ciclo);

			duracion_depuracion = chrono::duration_cast<Unidades>(tiempo_final_ciclo - tiempo_inicial);
			promedio_duracion_ciclo = chrono::duration_cast<Unidades>(duracion_depuracion / iteraciones);

			if (salida_cmd) {
				cout << iteraciones << ": ";
				cout << "duracion_depuracion: " << duracion_depuracion.count() << ", ";
				cout << "duracion_ciclo_actual: " << duracion_ciclo_actual.count() << ", ";
				cout << "promedio_duracion_ciclo: " << promedio_duracion_ciclo.count() << ", ";
				cout << endl;
			}
		}

		//--------------------------------------------------------------
		// verifica si la duración total actual de ejecución (desde iniciar()) excede max_milisegundos
		bool comprobar_duracion(unsigned int max_milisegundos) const
		{
			// estimar cuando el próximo ciclo terminará
			auto tiempo_final_sig_ciclo = Reloj::now() + promedio_duracion_ciclo;
			return tiempo_final_sig_ciclo > tiempo_inicial + chrono::milliseconds(max_milisegundos);
		}

		//--------------------------------------------------------------
		// retorna la duración promedio del ciclo
		unsigned int get_promedio_tiempo_duracion_ciclos() const
		{
			return chrono::duration_cast<Unidades>(promedio_duracion_ciclo).count();
		}

		//--------------------------------------------------------------
		// retorna la duración total de la carrera actual (desde el inicio)
		unsigned int get_duracion_depuracion() const
		{
			return chrono::duration_cast<Unidades>(duracion_depuracion).count();
		}

	private:
		unsigned int iteraciones;
	};
}