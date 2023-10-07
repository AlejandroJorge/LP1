#include <fstream>
using namespace std;
#include "FlotaGenerica.h"

void *leenumero(ifstream &arch)
{
  int num;
  arch >> num >> ws;
  if (arch.eof())
    return nullptr;
  return new int(num);
}

double calculanumero(void *numero)
{
  int num = *(int *)numero;
  return num * 1.0;
}

int cmpnumero(const void *ptrPilaA, const void *ptrPilaB)
{
  void **pilaA = *(void ***)ptrPilaA;
  void **pilaB = *(void ***)ptrPilaB;
  return *(double *)pilaB[P_PESO] - *(double *)pilaA[P_PESO];
}

void imprimenumero(ofstream &arch, void *numero)
{
  int num = *(int *)numero;
  arch << num << endl;
}