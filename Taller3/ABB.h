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

	Nodo* nuevoNodo(Flaite);
	void agregarFlaite(Nodo*& nodoAux, Flaite flaite );



	bool existeFlaite(Nodo* nodoAux,int RUN);
	void buscarRUN(Nodo* nodoAux, int RUN);
	
	void buscarCategoria(Nodo*, string );
	bool compararCategoria(string, string);
	
	void imprimirFlaite(Flaite, bool);
	
	Nodo*& getRaiz();

private:
	Nodo * raiz;
};

