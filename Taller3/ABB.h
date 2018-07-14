#pragma once
#include "Nodo.h"
class ABB
{
public:
	ABB();
	~ABB();

	void preOrden(Nodo* nodoAux);
	void inOrden(Nodo* nodoAux);
	void postOrden(Nodo* nodoAux);
	void porNivel();
	void porNivelRecursivo(Nodo* nodoAux, int n, int n2);
	int nivelMasAlto(Nodo* nodoAux, int n);

	void agregar_ABB(Nodo*& nodoAux, Flaite flaite);

	void eliminar_ABB(Nodo*&, int);
	void eliminar_NodoABB(Nodo*&);
	Nodo*& minimo_masIzquierdo(Nodo*&);

	bool existeFlaite(Nodo* nodoAux,int RUN);
	void buscarRUN(Nodo* nodoAux, int RUN, bool);
	
	void buscarCategoria(Nodo*, string, bool );
	bool compararCategoria(string, string);
	
	void imprimirFlaite(Flaite, bool);
	
	Nodo*& getRaiz();

private:
	Nodo * raiz;
};

