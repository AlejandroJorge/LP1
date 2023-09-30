#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Tareas.h"

enum
{
  CODIGO,
  NOMBRE,
};

void cargarAlumnos(void *&alumnos, const char *nomArch)
{
  // Abrir archivo
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  // Inicializar arreglo
  void **al = nullptr;
  int capacidad = 0, cantidad = 0;

  // Lectura
  void *reg;
  while (true)
  {
    reg = leerRegistro(arch);

    agregarRegistro(al, reg, cantidad, capacidad);

    arch.peek();
    if (arch.eof())
      break;
  }

  alumnos = al;
}

void agregarRegistro(void **&alumnos, void *alumno, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    void **auxAlumnos = new void *[capacidad + 5 + 1] {};

    if (capacidad != 0)
    {
      for (int i = 0; i < cantidad; i++)
        auxAlumnos[i] = alumnos[i];
      delete alumnos;
    }

    alumnos = auxAlumnos;
    capacidad += 5;
  }
  alumnos[cantidad] = alumno;
  cantidad++;
}

void *leerRegistro(ifstream &arch)
{
  // Inicializar
  void **registro = new void *[2];

  // Variables de lectura
  int cod;
  char *nombre;

  // Lectura a las variables de lectura
  // 20209347,Cabrera Canales Guillermo Edric
  arch >> cod;
  arch.get();
  nombre = leerCadena(arch, '\n');
  arch >> ws;

  // Asignar contenido al registro
  registro[CODIGO] = new int(cod);
  registro[NOMBRE] = nombre; // ya es un puntero (char*)

  return registro;
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  if (del == '\n')
    cad[strlen(buff) - 1] = 0;
  return cad;
}

void reporteAlumnos(void *alumnos, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  void **vv = (void **)alumnos;

  for (int i = 0; vv[i]; i++)
    imprimirAlumno(arch, vv[i]);
}

void imprimirAlumno(ofstream &arch, void *al)
{
  void **vv = (void **)al;

  char *nombre = (char *)vv[NOMBRE];
  int codigo = *(int *)vv[CODIGO];

  arch << "NOMBRE: " << nombre << endl;
  arch << "CODIGO: " << codigo << endl;
  arch << endl;
}