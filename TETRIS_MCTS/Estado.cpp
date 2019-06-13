#include "Estado.h"

tetra::Estado::Estado()
{
	reiniciar();
}

tetra::Estado::~Estado() { }

bool tetra::Estado::terminarIteraciones()
{
	return data.final;
}

int tetra::Estado::agenteID()
{
	return data.puntos;
}

void tetra::Estado::aplicarAccion(const Accion &accion)
{
	//Validar que las posibles acciones se encuentren en el rango de posibilidades
	if (accion.mov < 0 || accion.mov>1 || accion.rotate < 0 || accion.rotate>0)
	{
		return;
	}

	//Mover la ficha
	switch (data.puntos)
	{
	case movDer:
		data.P.Origen;
		break;
	case movIzq:
		data.P.Origen;
		break;
	default:
		break;
	}
}

void tetra::Estado::obtenerAccion(vector<Accion> &acciones)
{
	//Mover la ficha
	switch (data.puntos)
	{
	case movDer:
		if (data.P.Origen.Pos[0]>=0)
		{
			acciones.push_back(Accion(movDer));
		}
		else if (data.P.Origen.Pos[0] <= 0)
		{
			acciones.push_back(Accion(movDer));
		}
		break;
	case movIzq:
		if (data.P.Origen.Pos[1] >= 0)
		{
			acciones.push_back(Accion(movIzq));
		}
		else if (data.P.Origen.Pos[1] <= 0)
		{
			acciones.push_back(Accion(movDer));
		}
		break;
	default:
		break;
	}
}

bool tetra::Estado::obtenerAccionAleatoria(Accion & accion)
{
	vector<Accion> acciones;
	obtenerAccion(acciones);

	// validacion de seguridad
	if (acciones.empty())
	{
		return false;
	}
	accion = acciones[floor(rand()% acciones.size())];
	return true;
}

const float tetra::Estado::evaluar() const
{
	float valor;
	valor = powf((1 / 3), data.puntos);
	if (valor != 0)
	{
		valor = valor;
	}
	return valor;
}

void tetra::Estado::reiniciar()
{
	data.final = false;
	data.lineaCompleta = false;
	data.puntos = 0;
}
