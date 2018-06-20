#include "stdafx.h"
#include "ABB.h"
#include "Nodo.h"
#include<iostream>
#include <string>


ABB::ABB()
{
	this->raiz = nullptr;
}


ABB::~ABB()
{
}

void ABB::llamarOrden(int n) {

	switch (n)
	{
	case 1:
		this->preOrden(this->raiz);
		break;
	case 2:
		this->inOrden(this->raiz);
		break;
	case 3:
		this->postOrden(this->raiz);
		break;
	case 4:
		this->porNivel();
		break;
	default:
		break;
	}

}

void ABB::preOrden(Nodo* nodoAux)
{
	if (nodoAux == nullptr)
		return;
	this->imprimirFlaite(nodoAux->getFlaite(), false);
	this->preOrden(nodoAux->getIzq());
	this->preOrden(nodoAux->getDer());
}

void ABB::inOrden(Nodo* nodoAux)
{
	if (nodoAux == nullptr)
		return;
	this->inOrden(nodoAux->getIzq());
	this->imprimirFlaite(nodoAux->getFlaite(), false);
	this->inOrden(nodoAux->getDer());
}

void ABB::postOrden(Nodo* nodoAux)
{
	if (nodoAux == nullptr)
		return;
	this->postOrden(nodoAux->getIzq());	
	this->postOrden(nodoAux->getDer());
	this->imprimirFlaite(nodoAux->getFlaite(), false);
}

void ABB::porNivel()
{
	int nMax = nivelMasAlto(this->raiz, 0);
	for (int i = 0; i <= nMax; i++) {
		this->porNivelRecursivo(this->raiz, 0, i);
	}
}

void ABB::porNivelRecursivo(Nodo* nodoAux,int nActual,int nIdeal) 
{
	if (nActual == nIdeal) {
		this->imprimirFlaite(nodoAux->getFlaite(), false);
		return;
	}
	nActual++;
	if (nodoAux->getDer() == nullptr && nodoAux->getIzq() == nullptr) return;
	if (nodoAux->getDer() != nullptr && nodoAux->getIzq() != nullptr) {
		this->porNivelRecursivo(nodoAux->getIzq(), nActual, nIdeal);
		this->porNivelRecursivo(nodoAux->getDer(), nActual, nIdeal);
		return;
	}
	else if (nodoAux->getDer() != nullptr && nodoAux->getIzq() == nullptr) {
		this->porNivelRecursivo(nodoAux->getDer(), nActual, nIdeal);
		return;
	}
	this->porNivelRecursivo(nodoAux->getIzq(), nActual, nIdeal);
}

int ABB::nivelMasAlto(Nodo* nodoAux, int n)
{	
	if (nodoAux->getDer() == nullptr && nodoAux->getIzq() == nullptr) return n;
	n++;
	if (nodoAux->getDer() != nullptr && nodoAux->getIzq() != nullptr) {
		int n1 = nivelMasAlto(nodoAux->getDer(), n);
		int n2 = nivelMasAlto(nodoAux->getIzq(), n);
		return (n1 > n2) ? n1 : n2;
	}
	else if (nodoAux->getDer() != nullptr && nodoAux->getIzq() == nullptr)
		return nivelMasAlto(nodoAux->getDer(), n);
	return nivelMasAlto(nodoAux->getIzq(), n);

}

void ABB::agregarFlaite(Nodo* nodoAux, Nodo* nuevoNodo)
{
	if (nodoAux == nullptr) {
		nodoAux = nuevoNodo;
		return;
	}
	if (nodoAux->getFlaite().getRUN() == nuevoNodo->getFlaite().getRUN()){
		cout << "El flaite con el RUN " << nuevoNodo->getFlaite().getRUN() << " ya existe!" << endl;
		return;
	}
	if (nodoAux->getFlaite().getRUN() < nuevoNodo->getFlaite().getRUN()) agregarFlaite(nodoAux->getDer(), nuevoNodo);
	else agregarFlaite(nodoAux->getIzq(), nuevoNodo);
}

void ABB::llamarAgregar(Flaite flaite) 
{
	this->raiz = agregarRecursivoAux(flaite, this->raiz);
}
Nodo* ABB::agregarRecursivoAux(Flaite flaite, Nodo* nodoAux) 
{
	if (nodoAux == nullptr) return new Nodo(flaite);
	if (flaite.getRUN() == nodoAux->getFlaite().getRUN()) return nodoAux;
	if (nodoAux->getFlaite().getRUN() < flaite.getRUN()) nodoAux->setDer(this->agregarRecursivoAux(flaite, nodoAux->getDer()));
	else nodoAux->setIzq(this->agregarRecursivoAux(flaite, nodoAux->getIzq()));
	return nodoAux;
}

void ABB::capturarFlaite(Nodo* nodoAux, int RUN)
{
	if (nodoAux == nullptr) return;
	if (RUN > nodoAux->getFlaite().getRUN())
		capturarFlaite(nodoAux->getDer(), RUN);
	else if (RUN < nodoAux->getFlaite().getRUN())
		capturarFlaite(nodoAux->getIzq(), RUN);
	else {
		Nodo* nodo = nodoAux;
		nodoAux = this->unirNodo(nodoAux->getIzq(), nodoAux->getDer());
		delete nodo;
	}
}

Nodo* ABB::unirNodo(Nodo* nodoIzq, Nodo* nodoDer)
{
	if (nodoIzq == nullptr) return nodoDer;
	if (nodoDer == nullptr) return nodoIzq;
	Nodo* medio = unirNodo(nodoIzq->getDer(), nodoDer->getIzq());
	nodoIzq->setDer(medio);
	nodoDer->setIzq(nodoIzq);
	return nodoDer;
}

bool ABB::existeFlaite(Nodo* nodoAux,int RUN) {
	if (nodoAux == nullptr) return false;
	if (nodoAux->getFlaite().getRUN() == RUN) return true;
	if (nodoAux->getFlaite().getRUN() < RUN)
		buscarRUN(nodoAux->getIzq(), RUN);
	if (nodoAux->getFlaite().getRUN() > RUN)
		buscarRUN(nodoAux->getDer(), RUN);
	return false;
}

void ABB::buscarRUN(Nodo* nodoAux, int RUN)
{
	if (nodoAux->getFlaite().getRUN() == RUN ) {
		this->imprimirFlaite(nodoAux->getFlaite(), false);
		return;
	}
	if (nodoAux->getFlaite().getRUN() < RUN)
		buscarRUN(nodoAux->getDer(), RUN);
	buscarRUN(nodoAux->getIzq(), RUN);
}

void ABB::buscarCategoria(Nodo* nodoAux, string delito)
{
	// no se como comparar los string con uppercase
}

void ABB::imprimirFlaite(Flaite flaite, bool categ) 
{
	string aux = flaite.getNombre();
	int n = (int)aux.length();
	cout << "*Nombre: " << flaite.getNombre();
	for (int i = 0;i < 20 - n;i++) { cout << " "; }
	cout << "| *RUN: " << flaite.getRUN() << endl;
	aux = flaite.getAlias();
	n = (int)aux.length();
	cout << "*Alias: " << flaite.getAlias();                    
	for (int i = 0;i < 21 - n;i++) { cout << " "; }
	cout << "| *Peligrosidad: " << flaite.getPeligro() << endl;

	if (!categ) {cout << "*Delito: " << flaite.getDelito() << endl;}
}
Nodo * ABB::getRaiz()
{
	return this->raiz;
}
