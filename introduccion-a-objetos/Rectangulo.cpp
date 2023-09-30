#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "Rectangulo.h"

Rectangulo::Rectangulo(double altura, double base)
{
  this->altura = altura;
  this->base = base;
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

  cout << "============================" << endl;
  cout << "INFORMACION DEL RECTANGULO" << endl;
  cout << "----------------------------" << endl;
  cout << left << setw(20) << "Base: " << setw(6) << right << base << endl;
  cout << left << setw(20) << "Altura: " << setw(6) << right << altura << endl;
  cout << left << setw(20) << "Area: " << setw(6) << right << area() << endl;
  cout << left << setw(20) << "Perimetro: " << setw(6) << right << perimetro() << endl;
  cout << "============================" << endl;
  return *this;
}