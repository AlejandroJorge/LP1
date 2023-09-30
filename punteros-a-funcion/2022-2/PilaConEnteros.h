#ifndef PILACONENTEROS_H
#define PILACONENTEROS_H

#include <fstream>
using namespace std;

void imprimenumero(void *ptrNum, ofstream &arch);

int cmpnumero(const void *ptrNumA, const void *ptrNumB);

void *leenumero(ifstream &arch);

#endif /*PILACONENTEROS_H*/