#ifndef BIBLIOTECAPILAGENERICA_H
#define BIBLIOTECAPILAGENERICA_H

#include <fstream>
using namespace std;

enum Nodo
{
  N_ELEMENTO,
  N_SIGUIENTE
};

enum Pila
{
  P_CABEZA,
  P_LONGITUD
};

void cargaarreglo(void *&arreglo, int cmp(const void *ptrA, const void *ptrB), void *lee(ifstream &arch), const char *nomArch);
void cargapila(void *&pila, void *arreglo);
void muevepila(void *&pilaini, void *&pilafin);
void imprimepila(void *pilafin, void imprime(void *ptr, ofstream &arch), const char *nomArch);

#endif /*BIBLIOTECAPILAGENERICA_H*/