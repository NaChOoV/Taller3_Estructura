#include "stdafx.h"
#include "Menu.h"
#include "Nodo.h"
#include <Windows.h>
#include <MMSystem.h>
#include<fstream>
#include<sstream>
#include<cstring>
#include <string>
#include "ABB.h"
#include <iostream> 

using namespace std;


Menu::Menu()
{
	this->arbolABB = ABB();
	cargarArchivos();
	PlaySound(TEXT("ordenypatria.wav"),NULL,SND_ASYNC);
}


Menu::~Menu()
{
}

void Menu::menuPrincipal()
{

	desplegarMenu0();
	bool flag = false;
	char opcion;
	while (true) {
		fflush(stdin);
		cout << "[?]  Ingrese una opcion: ";
		cin >> opcion;
		cin.clear();
		cin.ignore();
		switch (opcion)
		{
		case '1':
			desplegarDelincuentes();
			break;
		case '2':
			modificarArbol();
			break;
		case '3':
			buscarDelincuentes();
			break;
		case '4':
			flag = true;
			break;

		default:
			cout << "\n Opcion invalida. " << endl;
			break;
		}
		if (flag) break;
		desplegarMenu0();
	}
}

void Menu::desplegarDelincuentes()
{
	if (arbolABB.getRaiz() == nullptr) {
		cout << "LOS ARBOLES SE ENCUENTRAN VACIOS." << endl;
		system("pause");
		return;
	}
	desplegarMenu1();
	bool flag = false;
	char opcion;
	while (true) {
		fflush(stdin);
		cout << "[?] Ingrese una opcion: ";
		cin >> opcion;
		cin.clear();
		cin.ignore();
		switch (opcion)
		{
		case '1':
			cout << "\n::::::::::::::::ARBOL ABB PRE-ORDEN::::::::::::::" << endl;
			arbolABB.preOrden(arbolABB.getRaiz());
			cout << "..::::::::::::::ARBOL AVL PRE-ORDEN::::::::::::.." << endl;
			// arbolAVL.preOrden(arbolABB.getRaiz())
			break;
			
		case '2':
			cout << "\n::::::::::::::::ARBOL ABB IN-ORDEN::::::::::::::" << endl;
			arbolABB.inOrden(arbolABB.getRaiz());
			cout << "..::::::::::::::ARBOL AVL IN-ORDEN::::::::::::::" << endl;
			// arbolAVL.inOrden(arbolABB.getRaiz())
			break;
		case '3':
			cout << "\n::::::::::::::::ARBOL ABB POST-ORDEN::::::::::::::" << endl;
			arbolABB.postOrden(arbolABB.getRaiz());
			cout << "::::::::::::::::ARBOL AVL POST-ORDEN::::::::::::::" << endl;
			// arbolAVL.postOrden(arbolABB.getRaiz())
			break;
		case '4':
			cout << "\n::::::::::::::::ARBOL ABB POR NIVEL::::::::::::::" << endl;
			arbolABB.porNivel();
			cout << "::::::::::::::::ARBOL AVL POR NIVEL::::::::::::::" << endl;
			// arbolAVL.inOrden(arbolABB.getRaiz())
			break;
		case '5':
			flag = true;
			break;
		default:
			cout << "\n Opcion invalida. " << endl;
			break;
		}
		if (flag) break;
		desplegarMenu1();
	}
}

void Menu::modificarArbol()
{
	desplegarMenu2();
	bool flag = false;
	int RUN;
	char opcion;
	while (true) {
		fflush(stdin);
		cout << "[?] Ingrese una opcion: ";
		cin >> opcion;
		cin.clear();
		cin.ignore();
		switch (opcion)
		{
		case '1': // Agregamos un delincuente en ambos arboles
			break;
		case '2': // Elimiamos un delincuente de ambos arboles
			cout << "\n Ingrese el RUN del flaite a eliminar: "; cin >> RUN;
			cout << endl;

			while (cin.fail()) {
				cout << " ERROR, el RUN ingresado no es valido!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << " Ingrese un nuevo RUN: "; cin >> RUN;
				cout << endl;
			}
			if (arbolABB.existeFlaite(arbolABB.getRaiz(), RUN)) {
				arbolABB.eliminar_ABB(arbolABB.getRaiz(), RUN);
				cout << "Flaite fusilado con exito!." << endl;
				break;
			}
			cout << "No existe flaite con el RUN ingresado." << endl;
			break;
		case '3': // Al menu principal
			flag = true;
			break;
		default:
			cout << "\n Opcion invalida. " << endl;
			break;
		}
		if (flag) break;
		desplegarMenu2();
	}
}

void Menu::crearDelincuente() {
	string nombre, alias, peligro, delito;
	int RUN;
	cout << "\n Para ingresar un flaite rellene los siguientes campos: " << endl;
	cout << "Nombre: " << endl;
	cin

}

void Menu::buscarDelincuentes()
{
	if (arbolABB.getRaiz() == nullptr) {
		cout << "LOS ARBOLES SE ENCUENTRAN VACIOS." << endl;
		system("pause");
		return;
	}
	desplegarMenu3();
	bool flag = false;
	string categoria;
	int RUN;
	char opcion;
	while (true) {
		fflush(stdin);
		cout << "[?] Ingrese una opcion: ";
		cin >> opcion;
		cin.clear();
		cin.ignore();
		switch (opcion)
		{
		case '1': // Buscamos por RUN y se miden los tiempos
			cout << "\n Ingrese el RUN a consultar: "; cin >> RUN;
			cout << endl;
			
			while (cin.fail()) {
				cout << " ERROR, el RUN ingresado no es valido!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << " Ingrese un nuevo RUN: "; cin >> RUN;
				cout << endl;

			}
			
			if (!arbolABB.existeFlaite(arbolABB.getRaiz(), RUN)) {
				cout << "No existe flaite con el RUN ingresado." << endl;
				break;
			}
				
			arbolABB.buscarRUN(arbolABB.getRaiz(), RUN);
			break;
			
		case '2': // Buscamos por categoria y se miden los tiempos
			cout << "\n Ingrese la categoria a consultar: ";
			cin >> categoria;
			cout << "\n ||Los/el delincuentes son: \n" << endl;
			arbolABB.buscarCategoria(arbolABB.getRaiz(), categoria);
			break;
		case '3': // Al menu principal
			flag = true;
			break;
		default:
			cout << "\n Opcion invalida. " << endl;
			break;
		}
		if (flag) break;
		desplegarMenu3();
	}
}

void Menu::desplegarMenu0()
{	
	cout << "////////////////////////////////////////////////////" << endl;
	cout << ":::::::::::::::POR LA RAZON O LA FUERZA:::::::::::::" << endl;	
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	cout << "===============BASE DE DATOS DE FLAITES=============" << endl;
	cout << "[1]  Desplegar flaites                  " << endl;
	cout << "[2]  Modificar arboles                  " << endl;
	cout << "[3]  Busqueda en arbol                  " << endl;
	cout << "[4]  Salir                              " << endl;

}
void Menu::desplegarMenu1()
{
	cout << "\n================DESPLEGAR ARBOLES===================" << endl;
	cout << "[1]  Pre-Orden                  " << endl;
	cout << "[2]  In-Orden                   " << endl;
	cout << "[3]  Post-Orden                 " << endl;
	cout << "[4]  Por-Nivel                  " << endl;
	cout << "[5]  Regresar al menu           " << endl;

}
void Menu::desplegarMenu2()
{
	cout << "\n================MODIFICAR ARBOLES===================" << endl;
	cout << "[1]  Agregar delincuente        " << endl;
	cout << "[2]  Capturar delincuente       " << endl;
	cout << "[3]  Regresar al menu           " << endl;

}
void Menu::desplegarMenu3()
{
	cout << "\n================BUSQUEDA ARBOLES====================" << endl;
	cout << "[1]  Buscar delincuente dado un RUN      " << endl;
	cout << "[2]  Buscar delincuentes por categoria   " << endl;
	cout << "[3]  Regresar al menu                    " << endl;
}

void Menu::cargarArchivos()
{
	ifstream archivo;
	archivo.open("datos.txt",ios::in);
	string nombre, run, alias, peligro, delito, linea;
	if (archivo.fail()) {
		cout << "ERROR: No se pudo abrir el archivo datos.txt" << endl;
		system("pause");
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, linea);

		run = linea.substr(0, 8);
		linea = linea.substr(9);
		nombre = linea.substr(0, linea.find(","));
		linea = linea.substr(linea.find(",") + 1);
		alias = linea.substr(0, linea.find(","));
		linea = linea.substr(linea.find(",") + 1);
		peligro = linea.substr(0, linea.find(","));
		linea = linea.substr(linea.find(",") + 1);
		delito = linea;

		Flaite flaite(nombre, alias, stoi(run), peligro, delito);

		this->arbolABB.agregar_ABB(arbolABB.getRaiz(),flaite);
		// AGREGAMOS AL AVL

	}
	archivo.close();


}

