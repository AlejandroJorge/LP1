#ifndef NUM_H
#define NUM_H

#include <fstream>
using namespace std;

void *leenum(ifstream &arch);

int cmpnum(const void *ptrA, const void *ptrB);

void imprimenum(ofstream &arch, void *dato, int &bloquePrevio);

#endif /* NUM_H*/