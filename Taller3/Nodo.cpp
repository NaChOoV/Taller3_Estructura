#include "stdafx.h"
#include "Nodo.h"
#include "Flaite.h"


Nodo::Nodo(string nombre, string alias, int RUN, string peligro, string delito)
{
	this->flaite = Flaite(nombre, alias, RUN, peligro, delito);
	this->hDer = nullptr;
	this->HIzq = nullptr;
}

Nodo::~Nodo()
{
}

Nodo * Nodo::getIzq()
{
	return this->HIzq ;
}

Nodo * Nodo::getDer()
{
	return this->hDer;
}

void Nodo::setIzq(Nodo * nuevoNodo)
{
	this->HIzq = nuevoNodo;
}

void Nodo::setDer(Nodo * nuevoNodo)
{
	this->hDer = nuevoNodo;
}

Flaite Nodo::getFlaite()
{
	return this->flaite;
}
