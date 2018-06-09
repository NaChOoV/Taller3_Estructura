#pragma once
#include<string>
using namespace std;

class Flaite
{
public:
	Flaite();
	Flaite(string nombre, string alias, int RUN, string peligro, string delito);
	~Flaite();

	string getNombre();
	string getAlias();
	int getRUN();
	string getPeligro();
	string getDelito();
private:
	string nombre;
	string alias;
	int RUN;
	string peligro;
	string delito;

};

