#ifndef HEROE_H
#define HEROE_H

#include <fstream>
using namespace std;

enum Heroe
{
  H_CODIGO,
  H_NOMBRE,
  H_ROL,
  H_CATEGORIA,
  H_PUNTAJE,
  H_CANTCAMPOS
};

void *leerHeroe(ifstream &arch);

int cmpHeroeQsort(void *ptrA, void *ptrB);

void imprimirHeroe(ofstream &arch, void *heroe);

void eliminarHeroe(void *heroe);

#endif /*HEROE_H*/