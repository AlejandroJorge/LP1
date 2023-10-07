#ifndef PILACONENTEROS_H
#define PILACONENTEROS_H

#include <fstream>
using namespace std;

void *leenumero(ifstream &arch);

double calculanumero(void *numero);

int cmpnumero(const void *ptrA, const void *ptrB);

void imprimenumero(ofstream &arch, void *numero);

#endif /*PILACONENTEROS_H*/