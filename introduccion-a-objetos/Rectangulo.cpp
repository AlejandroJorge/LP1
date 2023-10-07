#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "Rectangulo.h"

Rectangulo::Rectangulo()
{
  cout << "He sido instanciado" << endl;
  this->altura = 0;
  this->base = 0;
  this->nombre = nullptr;
}

Rectangulo::Rectangulo(double altura, double base, const char *nombre)
{
  cout << "He sido instanciado" << endl;
  this->altura = altura;
  this->base = base;
  this->nombre = new char[strlen(nombre) + 1];
  strcpy(this->nombre, nombre);
}

Rectangulo::Rectangulo(const char *nombre)
{
  cout << "He sido instanciado" << endl;
  this->altura = 0;
  this->base = 0;
  this->nombre = new char[strlen(nombre) + 1];
  strcpy(this->nombre, nombre);
}

Rectangulo &Rectangulo::setAltura(double altura)
{
  this->altura = altura;
  return *this;
}

Rectangulo &Rectangulo::setBase(double base)
{
  this->base = base;
  return *this;
}

double Rectangulo::getAltura()
{
  return altura;
}

double Rectangulo::getBase()
{
  return base;
}

double Rectangulo::area()
{
  return altura * base;
}

double Rectangulo::perimetro()
{
  return (altura + base) * 2;
}

Rectangulo &Rectangulo::mostrarPropiedades()
{
  cout << fixed;
  cout.precision(2);

  cout << "=============================================" << endl;
  cout << "INFORMACION DEL RECTANGULO" << endl;
  cout << "---------------------------------------------" << endl;
  cout << left << setw(20) << "Nombre: " << setw(20) << right << nombre << endl;
  cout << left << setw(20) << "Base: " << setw(20) << right << base << endl;
  cout << left << setw(20) << "Altura: " << setw(20) << right << altura << endl;
  cout << left << setw(20) << "Area: " << setw(20) << right << area() << endl;
  cout << left << setw(20) << "Perimetro: " << setw(20) << right << perimetro() << endl;
  cout << "=============================================" << endl;
  return *this;
}

Rectangulo::~Rectangulo()
{
  cout << "He sido destruido" << endl;
}

void Rectangulo::getNombre(char *nom) const
{
}

void Rectangulo::setNombre(const char *nombre)
{
  if (this->nombre != nullptr)
    delete this->nombre;
  this->nombre = new char[strlen(nombre) + 1];
  strcpy(this->nombre, nombre);
}

void f()
{
  class Rectangulo rect("Rectangulo RF");
}