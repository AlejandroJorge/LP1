#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "MetodoExacto.h"
#define BUFFSIZE 400

void cargaClientes(int *&cliDni, char **&cliNombre, char *&cliCategoria)
{
  ifstream arch("Clientes.csv", ios::in);
  if (!arch.is_open())
  {
    cout << "no se pudo abrir clientes" << endl;
    exit(1);
  }

  int bDni[BUFFSIZE]{};
  char *bNombre[BUFFSIZE]{};
  char *bCategoria[BUFFSIZE]{};
  int size = 0;

  int dni;
  char *cadena;
  while (arch >> dni)
  {
    // 29847168,ALDAVE ZEVALLOS ROSARIO A,6261108
    arch.get();
    cadena = leerCadena(arch, ',');
    while (arch.get() != '\n')
      ;

    bDni[size] = dni;
    bNombre[size] = extraerNombre(cadena);
    bCategoria[size] = extraerCategoria(cadena);
    size++;
  }
}

char *extraerNombre(const char *cadena)
{
  int len = strlen(cadena);
  char *cad;
  if (cadena[len - 2] == ' ')
  {
    cad = new char[len - 2];
    for (int i = 0; cadena[i]; i++)
      cad[i] = cadena[i];
    cad[len - 1] = 0;
  }
  return cad;
}

void reporteClientes(int *cliDni, char **cliNombre, char *cliCategoria)
{
  ofstream arch("ReporteClientes.txt", ios::out);
  if (!arch.is_open())
    exit(1);
  arch << left << fixed;
  arch << setw(15) << "DNI" << setw(40) << "NOMBRE"
       << "CATEGORIA" << endl;

  for (int i = 0; cliDni[i]; i++)
    arch << setw(15) << cliDni[i] << setw(40) << cliNombre[i]
         << cliCategoria[i] << endl;
}
