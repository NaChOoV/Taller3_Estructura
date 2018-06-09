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
	void porNivelRecursivo(Nodo* nodoAux, int n, int nMax);
	int nivelMasAlto(Nodo* nodoAux, int n);

	void agregarFlaite(Nodo* nodoAux, Nodo* nuevoNodo );
	void capturarFlaite(Nodo* nodoAux, int RUN);
	Nodo* unirNodo(Nodo* nodoIzq, Nodo* nodoDer);
	bool existeFlaite(Nodo* nodoAux,int RUN);
	void buscarRUN(Nodo* nodoAux, int RUN);
	
	void buscarCategoria(Nodo* nodoAux, string delito);
	
	void imprimirFlaite(Flaite flaite, bool categ);
	
	Nodo* getRaiz();

private:
	Nodo * raiz;
};

