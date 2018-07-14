#include "stdafx.h"
#include "Nodo.h"
#include "Flaite.h"


Nodo::Nodo(Flaite flaite)
{
	this->flaite = flaite;
	this->hDer = nullptr;
	this->HIzq = nullptr;
	this->_fb = 0;
}

Nodo::~Nodo()
{
}

Nodo *& Nodo::getIzq()
{
	return this->HIzq ;
}

Nodo *& Nodo::getDer()
{
	return this->hDer;
}

int Nodo::getFB()
{
	return this->_fb;
}


void Nodo::setIzq(Nodo * nuevoNodo)
{
	this->HIzq = nuevoNodo;
}

void Nodo::setDer(Nodo * nuevoNodo)
{
	this->hDer = nuevoNodo;
}

void Nodo::setFlaite(Flaite flaite)
{
	this->flaite = flaite;
}

void Nodo::setFB(int fb)
{
	_fb = fb;
}


Flaite Nodo::getFlaite()
{
	return this->flaite;
}
