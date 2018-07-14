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



void ABB::agregar_ABB(Nodo*& nodoAux, Flaite flaite)
{
	if (nodoAux == nullptr)  nodoAux = new Nodo(flaite); // Llegamos a un null
	else {
		if (nodoAux->getFlaite().getRUN() < flaite.getRUN()) agregar_ABB(nodoAux->getDer(), flaite);			
		else agregar_ABB(nodoAux->getIzq(), flaite);
	}
}

void ABB::eliminar_ABB(Nodo*& nodoAux, int RUN) {
	if (nodoAux == nullptr) return; // vacio
	else if (RUN < nodoAux->getFlaite().getRUN()) eliminar_ABB(nodoAux->getIzq(), RUN); // Izquierda
	else if (RUN > nodoAux->getFlaite().getRUN()) eliminar_ABB(nodoAux->getDer(), RUN); // Derecha
	else  eliminar_NodoABB(nodoAux); //Encontrado	
}

void ABB::eliminar_NodoABB(Nodo*& nodoAux) {
	if (nodoAux->getDer() && nodoAux->getIzq()) { // 2 hijos
		Nodo*& nodo_menor = minimo_masIzquierdo(nodoAux->getDer());
		nodoAux->setFlaite(nodo_menor->getFlaite());
		eliminar_NodoABB(nodo_menor);
	}
	else {
		Nodo* nodoEliminar = nodoAux;
		if (nodoAux->getIzq()) nodoAux = nodoAux->getIzq(); // 1 hijo izquierdo
		else if (nodoAux->getDer()) nodoAux = nodoAux->getDer(); // 1 hijo derecho
		else nodoAux = nullptr; // 0 hijos
		nodoEliminar->~Nodo();
	}
}
Nodo*& ABB::minimo_masIzquierdo(Nodo*& nodoAux) {
	if (nodoAux->getIzq()) minimo_masIzquierdo(nodoAux->getIzq());
	else return nodoAux;
}




bool ABB::existeFlaite(Nodo* nodoAux,int RUN) {
	if (nodoAux == nullptr) return false;
	if (nodoAux->getFlaite().getRUN() == RUN) return true;
	return existeFlaite(nodoAux->getIzq(), RUN) || existeFlaite(nodoAux->getDer(), RUN);
}

void ABB::buscarRUN(Nodo* nodoAux, int RUN, bool flag)
{
	if (nodoAux == nullptr) return;
	if (nodoAux->getFlaite().getRUN() == RUN ) {
		if(flag) this->imprimirFlaite(nodoAux->getFlaite(), false);
		return;
	}
	if (nodoAux->getFlaite().getRUN() < RUN)
		buscarRUN(nodoAux->getDer(), RUN, flag);
	buscarRUN(nodoAux->getIzq(), RUN, flag);
}

void ABB::buscarCategoria(Nodo* nodoAux, string delito, bool flag)
{
	if (nodoAux == nullptr) return;
	if (compararCategoria(nodoAux->getFlaite().getDelito(), delito))
		if(flag) this->imprimirFlaite(nodoAux->getFlaite(), true);
	buscarCategoria(nodoAux->getIzq(), delito, flag);
	buscarCategoria(nodoAux->getDer(), delito, flag);

}

bool ABB::compararCategoria(string del1, string del2)
{
	for (int i = 0;i < del1.length();i++) del1[i] = toupper(del1[i]);
	for (int i = 0;i < del2.length();i++) del2[i] = toupper(del2[i]);
	if (del1.compare(del2)) return false;
	return true;
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
Nodo *& ABB::getRaiz()
{
	return this->raiz;
}
