#include <iostream>
#include <fstream>
using namespace std;
#include "FlotaGenerica.h"

enum Registro
{
  R_CODIGO,
  R_DNI,
  R_CANTIDAD,
  R_PESO,
  R_CANTCAMPOS
};

void *leeregistro(ifstream &arch)
{
  // CRU - 009, 50375303, 5, 200
  int dni, cantidad;
  double peso;
  char *codigo = new char[8];
  arch.getline(codigo, 9, ',');
  arch >> dni;
  arch.get();
  arch >> cantidad;
  arch.get();
  arch >> peso;
  arch >> ws;

  void **registro = new void *[R_CANTCAMPOS];
  registro[R_DNI] = new int(dni);
  registro[R_CODIGO] = codigo;
  registro[R_CANTIDAD] = new int(cantidad);
  registro[R_PESO] = new double(peso);

  return registro;
}

double calcularegistro(void *registro)
{
  void **reg = (void **)registro;
  return *(double *)reg[R_PESO] * *(int *)reg[R_CANTIDAD];
}

int cmpregistro(const void *ptrPilaA, const void *ptrPilaB)
{
  void **pilaA = *(void ***)ptrPilaA;
  void **pilaB = *(void ***)ptrPilaB;
  return *(double *)pilaB[P_PESO] - *(double *)pilaB[P_PESO];
}

void imprimeregistro(ofstream &arch, void *reg)
{
  void **registro = (void **)reg;
  arch << "CODIGO: " << (char *)registro[R_CODIGO] << endl;
  arch << "DNI: " << *(int *)registro[R_DNI] << endl;
  arch << "PESO: " << *(double *)registro[R_PESO] << endl;
  arch << "CANTIDAD: " << *(int *)registro[R_CANTIDAD] << endl;
}