#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Transformaciones.h"

#define LONGITUDLINEA 70

void imprimirLinea(ofstream &arch, char caracter)
{
  for (int i = 0; i < LONGITUDLINEA; i++)
    arch.put(caracter);
  arch << endl;
}

char *leerCadena(ifstream &arch)
{
  char buff[50]{};
  arch.getline(buff, 50);
  char *cadenaExacta = new char[strlen(buff) + 1];
  strcpy(cadenaExacta, buff);
  cadenaExacta[strlen(buff) - 1] = 0; // Fix for linux I guess
  return cadenaExacta;
}

int buscarDni(int *dnis, int dniLeido)
{
  for (int i = 0; dnis[i]; i++)
    if (dnis[i] == dniLeido)
      return i;
  return -1;
}

void agregarCurso(char **cursos, int &cantidad, char *cadena)
{
  cursos[cantidad] = cadena;
  cantidad++;
}

void reasignarMemoria(char **&cursos, int cantidad)
{
  if (cantidad == 0)
  {
    cursos = nullptr;
    return;
  }
  char **aux = new char *[cantidad + 1];
  for (int i = 0; i < cantidad; i++)
    aux[i] = cursos[i];
  aux[cantidad] = nullptr;
  delete cursos;
  cursos = aux;
}