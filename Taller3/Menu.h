#pragma once
#include "ABB.h"
#include "AVL.h"
#include "Nodo.h"
#include <stdio.h>
#include <windows.h>
class Menu
{
public:
	Menu();
	~Menu();

	void cargarArchivos();
	void menuPrincipal();
private:
	ABB arbolABB;
	AVL arbolAVL;

	void desplegarDelincuentes();
	void modificarArbol();
	bool crearDelincuente();
	void buscarDelincuentes();
	void desplegarMenu0();
	void desplegarMenu1();
	void desplegarMenu2();
	void desplegarMenu3();

	double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b);

};

