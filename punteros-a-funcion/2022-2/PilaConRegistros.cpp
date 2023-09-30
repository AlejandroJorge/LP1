#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

enum Registro
{
  RE_CODIGO,
  RE_NOMBRE,
  RE_PESO
};

void imprimeregistro(void *registro, ofstream &arch)
{
  void **reg = (void **)registro;
  arch << setw(15) << *(int *)reg[RE_CODIGO];
  arch << setw(50) << (char *)reg[RE_NOMBRE];
  arch << setw(15) << *(double *)reg[RE_PESO];
  arch << endl;
}

int cmpregistro(const void *ptrRegA, const void *ptrRegB)
{
  void *ptrA = *(void **)ptrRegA;
  void *ptrB = *(void **)ptrRegB;

  void **regA = (void **)ptrA;
  void **regB = (void **)ptrB;

  double pesoA = *(double *)regA[RE_PESO];
  double pesoB = *(double *)regB[RE_PESO];

  return pesoB - pesoA;
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  return cad;
}

void *leeregistro(ifstream &arch)
{
  void **registro;
  char *nombre;
  int codigo;
  double peso;

  arch >> codigo;
  if (arch.eof())
    return nullptr;
  arch.get();
  nombre = leerCadena(arch, ',');
  arch >> peso >> ws;

  registro = new void *[3];
  registro[RE_CODIGO] = new int(codigo);
  registro[RE_NOMBRE] = nombre;
  registro[RE_PESO] = new double(peso);

  return registro;
}