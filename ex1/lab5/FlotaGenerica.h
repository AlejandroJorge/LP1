#ifndef FLOTAGENERICA_H
#define FLOTAGENERICA_H

#include <fstream>
using namespace std;

enum Pila
{
  P_CIMA,
  P_PESO,
  P_CANTCAMPOS
};

enum Nodo
{
  N_DATO,
  N_SIG,
  N_CANTCAMPOS
};

void cargacamiones(void *&flota, int numcamiones, double pesomaximo,
                   void *(*leeelemento)(ifstream &arch), double (*calculaelemento)(void *num), const char *nomArch);

void muestracamiones(void *flota, int numcamiones, void (*imprimenumero)(ofstream &arch, void *num), const char *nomArch);

#endif /*FLOTAGENERICA_H*/