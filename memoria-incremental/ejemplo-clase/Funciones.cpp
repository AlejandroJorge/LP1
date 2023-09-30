#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Funciones.h"
#define INCREMENTO 5

void abrirArchL(ifstream &arch, const char *nombre)
{
  arch.open(nombre, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombre << endl;
    exit(1);
  }
}

void abrirArchE(ofstream &arch, const char *nombre)
{
  arch.open(nombre, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombre << endl;
    exit(1);
  }
}

void leerAlumnos(const char *archNombre, int *&codigo, char **&nombre)
{
  ifstream arch;
  abrirArchL(arch, archNombre);

  int capacidad = 0, cantidad = 0;

  int f;
  char *n;
  while (true)
  {
    // 20196975, Hijar Pairazaman Jenny Delicia
    arch >> f;
    arch.get();
    n = leerCadena(arch, '\n');
    arch >> ws;

    if (capacidad == cantidad)
    {
      int *auxcodigo = new int[capacidad + INCREMENTO + 1]{};
      char **auxNombre = new char *[capacidad + INCREMENTO + 1] {};
      for (int i = 0; i < cantidad; i++)
      {
        auxcodigo[i] = codigo[i];
        auxNombre[i] = nombre[i];
      }
      if (capacidad != 0)
      {
        delete codigo;
        delete nombre;
      }
      codigo = auxcodigo;
      nombre = auxNombre;
      capacidad += INCREMENTO;
    }

    codigo[cantidad] = f;
    nombre[cantidad] = n;
    cantidad++;

    arch.peek();
    if (arch.eof())
      break;
  }
}

void mostrarAlumnos(const char *nomArch, int *codigo, char **nombre)
{
  ofstream arch;
  abrirArchE(arch, nomArch);

  arch << fixed << left;

  arch << setw(15) << "CODIGO";
  arch << setw(50) << "NOMBRE";
  arch << endl;

  arch << setw(65) << setfill('-') << "" << setfill(' ') << endl;

  for (int i = 0; codigo[i]; i++)
  {
    arch << setw(15) << codigo[i];
    arch << setw(50) << nombre[i];
    arch << endl;
  }
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

void leerCursos(const char *nomArch, int *codigo, char ***&cursos)
{
  int len = 0;
  while (codigo[len])
    len++;
  cursos = new char **[len + 1];

  ifstream arch;
  abrirArchL(arch, nomArch);

  int cantidad[len + 1]{}, capacidad[len + 1]{};

  int cod;
  char *cur;
  int pos;
  while (true)
  {
    // 20189596,MEC289
    arch >> cod;
    arch.get();
    cur = leerCadena(arch, '\n');
    arch >> ws;

    pos = buscarCodigo(codigo, cod);
    if (pos != -1)
      agregarCurso(cursos[pos], cur, cantidad[pos], capacidad[pos]);

    arch.peek();
    if (arch.eof())
      break;
  }
}

int buscarCodigo(int *codigo, int cod)
{
  for (int i = 0; codigo[i]; i++)
    if (codigo[i] == cod)
      return i;
  return -1;
}

void agregarCurso(char **&cursos, char *curso, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    char **cursosAux = new char *[capacidad + INCREMENTO + 1] {};
    for (int i = 0; i < cantidad; i++)
      cursosAux[i] = cursos[i];
    if (capacidad != 0)
      delete cursos;
    cursos = cursosAux;
    capacidad += INCREMENTO;
  }
  cursos[cantidad] = curso;
  cantidad++;
}

void mostrarAlumnosCursos(const char *nomArch, int *codigo, char **nombre, char ***cursos)
{
  ofstream arch;
  abrirArchE(arch, nomArch);

  arch << fixed << left;

  arch << setw(15) << "CODIGO";
  arch << setw(50) << "NOMBRE";
  arch << "CURSOS";
  arch << endl;

  arch << setw(65) << setfill('-') << "" << setfill(' ') << endl;

  for (int i = 0; codigo[i]; i++)
  {
    arch << setw(15) << codigo[i];
    arch << setw(50) << nombre[i];
    imprimirCursos(arch, cursos[i]);
    arch
        << endl;
  }
}

void imprimirCursos(ofstream &arch, char **cursos)
{
  for (int i = 0; cursos[i]; i++)
    arch << cursos[i] << " ";
}
