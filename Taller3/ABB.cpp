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


void ABB::preOrden(Nodo* nodoAux) //metodo recurcivo que recorre el arbol en preOrden
{
	if (nodoAux == nullptr)
		return;
	this->imprimirFlaite(nodoAux->getFlaite(), false);
	this->preOrden(nodoAux->getIzq());
	this->preOrden(nodoAux->getDer());
}

void ABB::inOrden(Nodo* nodoAux) //metodo recurcivo que recorre el arbol en inOrden
{
	if (nodoAux == nullptr)
		return;
	this->inOrden(nodoAux->getIzq());
	this->imprimirFlaite(nodoAux->getFlaite(), false);
	this->inOrden(nodoAux->getDer());
}

void ABB::postOrden(Nodo* nodoAux) // metodo recurcivo que recorre el arbol en postOrden
{
	if (nodoAux == nullptr)
		return;
	this->postOrden(nodoAux->getIzq());	
	this->postOrden(nodoAux->getDer());
	this->imprimirFlaite(nodoAux->getFlaite(), false);
}

void ABB::porNivel()
{
	int nMax = nivelMasAlto(this->raiz, 0);// metodo recurcivo que cuenta los niveles del arbol
	for (int i = 0; i <= nMax; i++) {
		this->porNivelRecursivo(this->raiz, 0, i); // metodo recurcivo que avanza hasta el nivel i e imprime el nodo 
	}
}

void ABB::porNivelRecursivo(Nodo* nodoAux,int nActual,int nIdeal) 
{
	if (nActual == nIdeal) { // si el nodo actual se encuentra en el nivel que se busca se impreme el nodo
		this->imprimirFlaite(nodoAux->getFlaite(), false);
		return;
	}
	nActual++; // se incrementa el nivel actual
	if (nodoAux->getDer() == nullptr && nodoAux->getIzq() == nullptr) return; // si es hoja y no esta en el nivel buscado retorna
	if (nodoAux->getDer() != nullptr && nodoAux->getIzq() != nullptr) { // si tiene dos hijos avanza en forma recurciba
		this->porNivelRecursivo(nodoAux->getIzq(), nActual, nIdeal);
		this->porNivelRecursivo(nodoAux->getDer(), nActual, nIdeal);
		return;
	}
	else if (nodoAux->getDer() != nullptr && nodoAux->getIzq() == nullptr) {// avanza con un hijo, el derecho
		this->porNivelRecursivo(nodoAux->getDer(), nActual, nIdeal);
		return;
	}
	this->porNivelRecursivo(nodoAux->getIzq(), nActual, nIdeal);// avanza con un hijo, el izquierdo
}

int ABB::nivelMasAlto(Nodo* nodoAux, int n)
{	
	if (nodoAux->getDer() == nullptr && nodoAux->getIzq() == nullptr) return n; // si es hoja retorna el nivel
	n++; // incrementa el contador del nivel
	if (nodoAux->getDer() != nullptr && nodoAux->getIzq() != nullptr) { // si hay dos hijos 
		int n1 = nivelMasAlto(nodoAux->getDer(), n); // analiza por la derecha 
		int n2 = nivelMasAlto(nodoAux->getIzq(), n); // analiza por la izquierda
		return (n1 > n2) ? n1 : n2; // retorna el mayor
	}
	else if (nodoAux->getDer() != nullptr && nodoAux->getIzq() == nullptr) // si solo tiene un hijo, el derecho 
		return nivelMasAlto(nodoAux->getDer(), n);
	return nivelMasAlto(nodoAux->getIzq(), n); // si solo tiene un hijo, el izquierdo
}



void ABB::agregar_ABB(Nodo*& nodoAux, Flaite flaite)
{
	if (nodoAux == nullptr)  nodoAux = new Nodo(flaite); // Llegamos a un null
	else { // baja por la izquierda o la derecha segun el RUN como clave 
		if (nodoAux->getFlaite().getRUN() < flaite.getRUN()) agregar_ABB(nodoAux->getDer(), flaite);			
		else agregar_ABB(nodoAux->getIzq(), flaite);
	}
}

void ABB::eliminar_ABB(Nodo*& nodoAux, int RUN) { // busca el nodo a eliminar de forma recurciva
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
Nodo*& ABB::minimo_masIzquierdo(Nodo*& nodoAux) { // metodo recurcivo que retorna nodo mas a la izquierda apartir del nodo dado
	if (nodoAux->getIzq()) minimo_masIzquierdo(nodoAux->getIzq());
	else return nodoAux;
}




bool ABB::existeFlaite(Nodo* nodoAux,int RUN) {
	if (nodoAux == nullptr) return false;
	if (nodoAux->getFlaite().getRUN() == RUN) return true;
	return (RUN < nodoAux->getFlaite().getRUN() ? existeFlaite(nodoAux->getIzq(), RUN) : existeFlaite(nodoAux->getDer(), RUN));
}

void ABB::buscarRUN(Nodo* nodoAux, int RUN, bool flag)
{
	if (nodoAux == nullptr) return;
	if (nodoAux->getFlaite().getRUN() == RUN ) {
		if(flag) this->imprimirFlaite(nodoAux->getFlaite(), false); // dado que el metodo se ejecuta para ambos arboles la flag impide que se duplique la salida por consola
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
		if(flag) this->imprimirFlaite(nodoAux->getFlaite(), true);// dado que el metodo se ejecuta para ambos arboles la flag impide que se duplique la salida por consola
	buscarCategoria(nodoAux->getIzq(), delito, flag);
	buscarCategoria(nodoAux->getDer(), delito, flag);

}

bool ABB::compararCategoria(string del1, string del2)
{
	for (int i = 0;i < del1.length();i++) del1[i] = toupper(del1[i]);
	for (int i = 0;i < del2.length();i++) del2[i] = toupper(del2[i]);
	
	return (del1.compare(del2) == 0);
	
}

void ABB::imprimirFlaite(Flaite flaite, bool categ) 
{
	string aux = flaite.getNombre();
	int n = (int)aux.length();
	cout << "\n*Nombre: " << flaite.getNombre();
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
