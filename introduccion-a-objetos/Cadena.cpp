#include <iostream>
#include <cstring>
using namespace std;
#include "Cadena.h"

Cadena::Cadena()
{
  longitud = 0;
  cad = nullptr;
}

Cadena::~Cadena()
{
  if (cad != nullptr)
    delete cad;
}

int Cadena::getLongitud() const
{
  return this->longitud;
}
void Cadena::setCad(const char *cad)
{
  if (cad != nullptr)
    delete cad;
  this->cad = new char[strlen(cad) + 1];
  strcpy(this->cad, cad);
  longitud = strlen(cad);
}
void Cadena::getCad(char *cad) const
{
  if (cad == nullptr)
    cad[0] = 0;
  strcpy(cad, this->cad);
}

void Cadena::imprimir() const
{
  cout << "Cadena: " << cad << ", longitud: " << longitud << endl;
}

void Cadena::copia(const class Cadena &cad)
{
  longitud = cad.getLongitud();
  this->cad = new char[longitud + 1];
  cad.getCad(this->cad);
}