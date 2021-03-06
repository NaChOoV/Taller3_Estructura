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
#include <stdio.h>

using namespace std;
LARGE_INTEGER t_ini, t_fin;


Menu::Menu()
{
	this->arbolABB = ABB();
	this->arbolAVL = AVL();
	cargarArchivos();
	PlaySound(TEXT("ordenypatria.wav"),NULL,SND_ASYNC); // BGM
}


Menu::~Menu()
{
}

void Menu::menuPrincipal()
{

	desplegarMenu0(); // menu principal
	bool flag = false; // variable bool empleada para reconocer la salida del menu (rompe el ciclo while)
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
	double tiempo_ABB = 0, tiempo_AVL = 0; // almacenan el tiempo de recorrido

	if (arbolABB.getRaiz() == nullptr) {
		cout << "LOS ARBOLES SE ENCUENTRAN VACIOS." << endl;
		system("pause");
		return;
	}
	desplegarMenu1(); // subMenu desplegar
	bool flag = false;
	char opcion;
	while (true) {
		bool flag2 = true; // detecta el default case del switch
		fflush(stdin);
		cout << "[?] Ingrese una opcion: ";
		cin >> opcion;
		cin.clear();
		cin.ignore();
		switch (opcion)
		{
		case '1':
			cout << "\n::::::::::::::::ARBOL ABB PRE-ORDEN::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolABB.preOrden(arbolABB.getRaiz());
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 

			 // analogamente para el otro arbol
			cout << "\n..::::::::::::::ARBOL AVL PRE-ORDEN::::::::::::.." << endl;
			QueryPerformanceCounter(&t_ini); 
			arbolAVL.preOrden(arbolAVL.getRaiz());
			QueryPerformanceCounter(&t_fin); 
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini); 
			break;
			
		case '2':
			cout << "\n::::::::::::::::ARBOL ABB IN-ORDEN::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolABB.inOrden(arbolABB.getRaiz());
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 

			cout << "\n..::::::::::::::ARBOL AVL IN-ORDEN::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolAVL.inOrden(arbolAVL.getRaiz());
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini); // analogamente para el otro arbol
			break;
		case '3':
			cout << "\n::::::::::::::::ARBOL ABB POST-ORDEN::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolABB.postOrden(arbolABB.getRaiz());
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 

			cout << "\n::::::::::::::::ARBOL AVL POST-ORDEN::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolAVL.postOrden(arbolAVL.getRaiz());
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini); // analogamente para el otro arbol
			break;
		case '4':
			cout << "\n::::::::::::::::ARBOL ABB POR NIVEL::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolABB.porNivel();
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 

			cout << "\n::::::::::::::::ARBOL AVL POR NIVEL::::::::::::::" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolAVL.porNivel();
			QueryPerformanceCounter(&t_fin); // momento de termino
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini); // analogamente para el otro arbol
			break;
		case '5':
			flag = true;
			break;
		default:
			flag2 = false;
			cout << "\n Opcion invalida. " << endl;
			break;
		}
		if (flag) break;
		if (flag2) {
			cout << "\n:::::::::::::::::::::TIEMPO::::::::::::::::::::::::::\n" << endl;
			cout << "ABB: " << tiempo_ABB * 1000.0 << " milisegundos." << endl;
			cout << "AVL: " << tiempo_AVL * 1000.0 << " milisegundos." << endl;
			cout << "\n:::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;
		}
		desplegarMenu1();
	}
}

void Menu::modificarArbol()
{
	desplegarMenu2(); // subMenu modificar
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
			if (crearDelincuente()) cout << "\nFlaite agregado con exito!. " << endl;
			else cout << "\nERROR: El flaite ingresado ya existe!." << endl;
			break;
		case '2': // Elimiamos un delincuente de ambos arboles
			cout << "\n Ingrese el RUN del flaite a eliminar: "; cin >> RUN;
			cout << endl;

			while (cin.fail()) { // capta ingreso de caracteres no numericos en e RUN 
				cout << " ERROR, el RUN ingresado no es valido!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << " Ingrese un nuevo RUN: "; cin >> RUN;
				cout << endl;
			}
			if (arbolABB.existeFlaite(arbolABB.getRaiz(), RUN)) { // verifica que el delincuente exista para poder eliminarlo 
				arbolABB.eliminar_ABB(arbolABB.getRaiz(), RUN);
				arbolAVL.eliminar_AVL(arbolAVL.getRaiz(), RUN);
				cout << "Flaite fusilado con exito!." << endl;
				break;
			}
			cout << "No existe flaite con el RUN ingresado!" << endl;
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

bool Menu::crearDelincuente() {
	string nombre, alias, peligro, delito;
	int RUN;
	cout << "\n Para ingresar un flaite rellene los siguientes campos: \n" << endl;
	cout << "Nombre: ";
	getline(cin, nombre);
	cout << "Alias: ";
	getline(cin, alias);
	cout << "Nivel de peligro(baja/media/alta): ";
	getline(cin, peligro);
	cout << "Delito: ";
	getline(cin, delito);
	cout << "RUT(EJEM:12345678): ";
	cin >> RUN;
	cin.clear();
	cin.ignore();
	while (cin.fail()) { // capta ingreso de caracteres no numericos en e RUN 
		cout << " ERROR, el RUN ingresado no es valido!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << " Ingrese un nuevo RUN: "; cin >> RUN;
		cout << endl;
	}

	if (this->arbolABB.existeFlaite(arbolABB.getRaiz(), RUN)) return false; // valida que no se ingrese un delincuente existente segun RUN 


	Flaite flaite(nombre, alias, RUN, peligro, delito);
	
	double tiempo_ABB = 0, tiempo_AVL = 0;


	QueryPerformanceCounter(&t_ini);
	this->arbolABB.agregar_ABB(arbolABB.getRaiz(), flaite);
	QueryPerformanceCounter(&t_fin);
	tiempo_ABB = performancecounter_diff(&t_fin, &t_ini);

	QueryPerformanceCounter(&t_ini);
	this->arbolAVL.agregar_AVL(arbolAVL.getRaiz(), flaite);
	QueryPerformanceCounter(&t_fin);
	tiempo_AVL = performancecounter_diff(&t_fin, &t_ini);

	cout << "\n:::::::::::::::::::::TIEMPO::::::::::::::::::::::::::\n" << endl;
	cout << "ABB: " << tiempo_ABB * 1000.0 << " milisegundos." << endl;
	cout << "AVL: " << tiempo_AVL * 1000.0 << " milisegundos." << endl;
	cout << "\n:::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

	return true;
}

void Menu::buscarDelincuentes()
{
	if (arbolABB.getRaiz() == nullptr) {
		cout << "LOS ARBOLES SE ENCUENTRAN VACIOS." << endl;
		system("pause");
		return;
	}
	desplegarMenu3(); // subMenu buscar
	bool flag = false;
	double tiempo_ABB, tiempo_AVL; // almacenan el tiempo de busqueda
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
			
			while (cin.fail()) {  // capta ingreso de caracteres no numericos en e RUN 
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
			cout << "Encontrado!\n" << endl;
			QueryPerformanceCounter(&t_ini); // momento de inicio
			arbolABB.buscarRUN(arbolABB.getRaiz(), RUN, true);
			QueryPerformanceCounter(&t_fin); // momento de termino
			cout << "\n";
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 
			// analogamente para el otro arbol
			QueryPerformanceCounter(&t_ini);
			arbolAVL.buscarRUN(arbolAVL.getRaiz(), RUN, false);
			QueryPerformanceCounter(&t_fin);
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini);

			cout << "ABB: " << tiempo_ABB*1000.0 << " milisegundos." << endl;
			cout << "AVL: " << tiempo_AVL*1000.0 << " milisegundos." << endl;

			break;
			
		case '2': // Buscamos por categoria y se miden los tiempos
			cout << "\n Ingrese la categoria a consultar: ";
			cin >> categoria;
			cout << "\n ||Los/el delincuentes son: \n" << endl;

			QueryPerformanceCounter(&t_ini);  // momento de inicio
			arbolABB.buscarCategoria(arbolABB.getRaiz(), categoria, true);
			QueryPerformanceCounter(&t_fin); // momento de termino 
			tiempo_ABB = performancecounter_diff(&t_fin, &t_ini); // calcula la diferencia para determinar la duracion en milisegundos que tarda la busqueda 

			//analogamente para el otro arbol
			QueryPerformanceCounter(&t_ini);
			arbolAVL.buscarCategoria(arbolABB.getRaiz(), categoria, false);
			QueryPerformanceCounter(&t_fin);
			tiempo_AVL = performancecounter_diff(&t_fin, &t_ini);

			cout << "\nABB: " << tiempo_ABB * 1000.0 << " milisegundos." << endl;
			cout << "AVL: " << tiempo_AVL * 1000.0 << " milisegundos." << endl;


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

double Menu::performancecounter_diff(LARGE_INTEGER * a, LARGE_INTEGER * b) // retorna la diferencia en milisegundos 
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return ((double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart);
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
		this->arbolABB.agregar_ABB(arbolABB.getRaiz(), flaite);
		this->arbolAVL.agregar_AVL(arbolAVL.getRaiz(), flaite);

	}
	archivo.close();


}

