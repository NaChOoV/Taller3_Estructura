#pragma once
#include "Flaite.h"
class Nodo
{
public:
	Nodo(string nombre, string alias, int RUN, string peligro, string delito);
	~Nodo();

	Nodo* getIzq();
	Nodo* getDer();
	void setIzq(Nodo* nuevoNodo);
	void setDer(Nodo* nuevoNodo);
	Flaite getFlaite();


private:
	Flaite flaite;
	Nodo* hDer;
	Nodo* HIzq;

};

