#ifndef PILACONREGISTROS_H
#define PILACONREGISTROS_H

#include <fstream>
using namespace std;

void imprimeregistro(void *registro, ofstream &arch);

int cmpregistro(const void *ptrRegA, const void *ptrRegB);

void *leeregistro(ifstream &arch);

#endif /*PILACONREGISTROS_H*/