#pragma once
#include "ABB.h"
class AVL : public ABB
{
public:
	AVL();
	~AVL();
	int calcularFB(Nodo* nodoAux);
	void agregar_AVL(Nodo*&,Flaite);
	void rebalance(Nodo*&);
	void rotarSimpleDerecha(Nodo*&);
	void rotarSimpleIzquierda(Nodo*&);

	void eliminar_AVL(Nodo*& nodoAux, int RUN);

};

