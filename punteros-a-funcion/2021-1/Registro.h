#ifndef REGISTRO_H
#define REGISTRO_H

#include <fstream>
using namespace std;

enum Registro
{
  R_LICENCIA,
  R_PLACA,
  R_FECHA,
  R_INFRACCION
};

void *leeregistro(ifstream &arch);

int cmpregistro(const void *ptrRegA, const void *ptrRegB);

void imprimeregistro(ofstream &arch, void *registro, int &bloquePrevio);

#endif /*REGISTRO_H*/