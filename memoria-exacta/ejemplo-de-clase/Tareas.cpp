#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Tareas.h"
#include "Transformaciones.h"
#include "Archivos.h"

#define BUFFSIZE 200

void cargarAlumnos(int *&dnis, char **&nombres)
{
  // Buffers
  int dnisBuff[BUFFSIZE]{};
  char *nombresBuff[BUFFSIZE]{};
  int size = 0;

  // Archivo
  ifstream arch;
  abrirArchvo(arch, "Alumnos.csv");

  // Lectura
  int dniLeido;
  char *nombreLeido;
  while (true)
  {
    // 20196975,Hijar Pairazaman Jenny Delicia
    arch >> dniLeido;
    if (arch.eof())
      break;
    arch.get();
    nombreLeido = leerCadena(arch);

    dnisBuff[size] = dniLeido;
    nombresBuff[size] = nombreLeido;
    size++;
  }
  size++;

  // Memoria
  dnis = new int[size];
  nombres = new char *[size];

  // Copiado
  for (int i = 0; i < size; i++)
  {
    dnis[i] = dnisBuff[i];
    nombres[i] = nombresBuff[i];
  }
}

void cargarCursos(int *dnis, char ***&cursos)
{
  // Archivo
  ifstream arch;
  abrirArchvo(arch, "Cursos.csv");

  // Memoria
  int len = 0;
  while (dnis[len])
    len++;
  cursos = new char **[len];
  cursos[len - 1] = nullptr;

  int cantidadCursos[len]{};
  for (int i = 0; i < len; i++)
    cursos[i] = new char *[BUFFSIZE];

  // Lectura
  int dniLeido, pos;
  char *codigoLeido;
  while (true)
  {
    // 20187490,MAT219
    arch >> dniLeido;
    if (arch.eof())
      break;
    arch.get();
    codigoLeido = leerCadena(arch);
    pos = buscarDni(dnis, dniLeido);
    if (pos != -1)
      agregarCurso(cursos[pos], cantidadCursos[pos], codigoLeido);
  }

  // Reasignacion de memoria
  for (int i = 0; i < len; i++)
    reasignarMemoria(cursos[i], cantidadCursos[i]);
}

void imprimirReporte(int *dnis, char **nombres, char ***cursos)
{
  ofstream arch;
  abrirArchvo(arch, "Reporte.txt");

  arch << fixed << left;
  arch.precision(2);

  for (int i = 0; dnis[i]; i++)
  {
    imprimirLinea(arch, '-');
    arch << setw(15) << "DNI"
         << ":" << setw(20) << dnis[i] << endl;
    arch << setw(15) << "NOMBRE"
         << ":" << setw(50) << nombres[i] << endl;
    arch << setw(15) << "CURSOS"
         << ":" << endl;
    for (int j = 0; cursos[i][j]; j++)
      arch << "  *) " << cursos[i][j] << endl;
    imprimirLinea(arch, '-');
  }
}