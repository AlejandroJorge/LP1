#include <iostream>
#include <fstream>
using namespace std;

void *leenum(ifstream &arch)
{
  int licencia, fecha, infraccion, d, m, a;
  char placa[30];
  arch >> licencia;

  if (arch.eof())
    return nullptr;

  arch.get();
  arch.getline(placa, 30, ',');
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;
  arch.get();
  arch >> infraccion;

  fecha = d + m * 100 + a * 10000;

  return new int(fecha);
}

int cmpnum(const void *ptrA, const void *ptrB)
{
  int a = *(int *)ptrA;
  int b = *(int *)ptrB;
  return a - b;
}

void imprimenum(ofstream &arch, void *dato, int &bloquePrevio)
{
  int num = *(int *)dato;
  arch << "Numero: " << num << endl;
}