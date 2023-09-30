#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <fstream>
using namespace std;

void abrirArchvo(ifstream &arch, const char *nombreArch);
void abrirArchvo(ofstream &arch, const char *nombreArch);

#endif /*ARCHIVOS_H*/