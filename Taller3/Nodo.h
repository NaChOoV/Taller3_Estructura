#pragma once
#include "Flaite.h"
class Nodo
{
public:
	Nodo(Flaite);
	~Nodo();

	Nodo*& getIzq();
	Nodo*& getDer();
	int getFB();
	void setIzq(Nodo* nuevoNodo);
	void setDer(Nodo* nuevoNodo);
	void setFlaite(Flaite);
	void setFB(int);
	Flaite getFlaite();


private:
	Flaite flaite;
	Nodo* hDer;
	Nodo* HIzq;
	int _fb;



};

