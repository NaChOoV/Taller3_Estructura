#pragma once
#include "ABB.h"
#include "Nodo.h"
class Menu
{
public:
	Menu();
	~Menu();

	void menuPrincipal();
private:
	ABB arbolABB;

	void desplegarDelincuentes();
	void modificarArbol();
	void buscarDelincuentes();
	void cargarArchivos();
	void desplegarMenu0();
	void desplegarMenu1();
	void desplegarMenu2();
	void desplegarMenu3();

};
