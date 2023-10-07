#ifndef PILACONREGISTROS_H
#define PILACONREGISTROS_H

#include <fstream>
using namespace std;

void *leeregistro(ifstream &arch);

double calcularegistro(void *numero);

int cmpregistro(const void *ptrA, const void *ptrB);

void imprimeregistro(ofstream &arch, void *numero);

#endif /*PILACONREGISTROS_H*/