#include "stdafx.h"
#include "AVL.h"
#include <algorithm> 

AVL::AVL() : ABB() // la clase AVL es extencion de ABB
{
	this->getRaiz() = nullptr;
}


AVL::~AVL()
{	
}

int AVL::calcularFB(Nodo * nodoAux) // calcula el fartor de balance 
{
	if (nodoAux == nullptr) return 0;
	else if (nodoAux->getIzq() && !nodoAux->getDer()) return calcularFB(nodoAux->getIzq()) + 1;
	else if (!nodoAux->getIzq() && nodoAux->getDer()) return calcularFB(nodoAux->getDer()) + 1;
	else if (!nodoAux->getIzq() && !nodoAux->getDer()) return 1;
	else return max(calcularFB(nodoAux->getDer()), calcularFB(nodoAux->getIzq())) + 1;

}
void AVL::agregar_AVL(Nodo*& nodoAux,Flaite flaite)
{
	if (nodoAux == nullptr) nodoAux = new Nodo(flaite);	// agrega el nodo
	else {// busca la pocicion de forma recurciba
		if (nodoAux->getFlaite().getRUN() < flaite.getRUN()) agregar_AVL(nodoAux->getDer(), flaite);
		else agregar_AVL(nodoAux->getIzq(), flaite);
	}
	nodoAux->setFB(calcularFB(nodoAux->getIzq()) - calcularFB(nodoAux->getDer()));// actualiza el factor de balance
	rebalance(nodoAux);// aplica las rotacione que correspondan
}

void AVL::rebalance(Nodo *& nodoAux)
{
	int _FB = nodoAux->getFB();
	if (_FB == 2) {
		if (nodoAux->getIzq()->getFB() > 0) rotarSimpleDerecha(nodoAux);
		else {
			rotarSimpleIzquierda(nodoAux->getIzq());
			rotarSimpleDerecha(nodoAux);
		}
	}
	else if (_FB == -2) {
		if (nodoAux->getDer()->getFB() < 0) rotarSimpleIzquierda(nodoAux);
		else {
			rotarSimpleDerecha(nodoAux->getDer());
			rotarSimpleIzquierda(nodoAux);
		}
	}
}

void AVL::rotarSimpleDerecha(Nodo *& nodoAux)
{
	Nodo* auxIzq = nodoAux->getIzq();
	nodoAux->setIzq(auxIzq->getDer());
	auxIzq->setDer(nodoAux);
	nodoAux = auxIzq;
}
void AVL::rotarSimpleIzquierda(Nodo *& nodoAux)
{
	Nodo* auxDer = nodoAux->getDer();
	nodoAux->setDer(auxDer->getIzq());
	auxDer->setIzq(nodoAux);
	nodoAux = auxDer;
}

void AVL::eliminar_AVL(Nodo *& nodoAux, int RUN)
{
	if (nodoAux == nullptr) return; // vacio
	else if (RUN < nodoAux->getFlaite().getRUN()) eliminar_ABB(nodoAux->getIzq(), RUN); // Izquierda
	else if (RUN > nodoAux->getFlaite().getRUN()) eliminar_ABB(nodoAux->getDer(), RUN); // Derecha
	else {
		eliminar_NodoABB(nodoAux); //Encontrado	
		nodoAux->setFB(calcularFB(nodoAux->getIzq()) - calcularFB(nodoAux->getDer()));
		rebalance(nodoAux);
	}
}


