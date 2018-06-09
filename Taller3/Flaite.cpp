#include "stdafx.h"
#include "Flaite.h"


Flaite::Flaite()
{
}

Flaite::Flaite(string nombre, string alias, int RUN, string peligro, string delito)
{
	this->nombre = nombre;
	this->alias = alias;
	this->RUN = RUN;
	this->peligro = peligro;
	this->delito = delito;
}


Flaite::~Flaite()
{
}

string Flaite::getNombre()
{
	return this->nombre;
}

string Flaite::getAlias()
{
	return this->alias;
}

int Flaite::getRUN()
{
	return this->RUN;
}

string Flaite::getPeligro()
{
	return this->peligro;
}



string Flaite::getDelito()
{
	return this->delito;
}
