#pragma once
#include "Flaite.h"
class Nodo
{
public:
	Nodo(Flaite flaite);
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

