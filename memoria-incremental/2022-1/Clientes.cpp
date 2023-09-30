// 91897732,GAMARRA ALCOCER VIRGINIA,954025615
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#define INCREMENTO 10

char *leerCadenaAux(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cadena = new char[strlen(buff) + 1];
  strcpy(cadena, buff);
  // FIX LINUX
  if (del == '\n')
    cadena[strlen(buff) - 1] = 0;
  // FIX LINUX
  return cadena;
}

void agregarElemento(int **&dniTelefono, int *tuplaDniTelefono, char ***&nombreCategoria,
                     char **tuplaNombreCategoria, int &capacidad, int &cantidad)
{
  if (capacidad == cantidad)
  {
    int **auxDniTelefono;
    char ***auxNombreCategoria;
    auxDniTelefono = new int *[capacidad + INCREMENTO + 1];
    auxNombreCategoria = new char **[capacidad + INCREMENTO + 1];

    if (capacidad > 0)
    {
      for (int i = 0; dniTelefono[i]; i++)
      {
        auxDniTelefono[i] = dniTelefono[i];
        auxNombreCategoria[i] = nombreCategoria[i];
      }
      delete dniTelefono;
      delete nombreCategoria;
    }

    dniTelefono = auxDniTelefono;
    nombreCategoria = auxNombreCategoria;

    capacidad += INCREMENTO;
  }
  dniTelefono[cantidad] = tuplaDniTelefono;
  nombreCategoria[cantidad] = tuplaNombreCategoria;
  cantidad++;
}

void separarNombreCategoria(char *cadena, char *&nombre, char *&categoria)
{
  int len = strlen(cadena);
  if (cadena[len - 2] == ' ')
  {
    nombre = new char[len - 1];
    for (int i = 0; i < len - 2; i++)
      nombre[i] = cadena[i];
    categoria = new char[2];
    categoria[0] = cadena[len - 1];
    categoria[1] = 0;
  }
  else
  {
    nombre = new char[len + 1];
    strcpy(nombre, cadena);
    categoria = new char[2];
    categoria[0] = '-';
    categoria[1] = 0;
  }
  delete cadena;
}

void CargaDeClientes(int **&dniTelefono, char ***&nombreCategoria, const char *nomArch)
{
  // ---------------------------------------------------------
  ifstream arch(nomArch, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  // ---------------------------------------------------------

  // ---------------------------------------------------------
  int cantidad = 0, capacidad = 0;
  dniTelefono = nullptr;
  nombreCategoria = nullptr;
  // ---------------------------------------------------------

  // ---------------------------------------------------------
  int dni, telefono;
  char *cadena;
  char *nombre, *categoria;

  int *tuplaDniTelefono;
  char **tuplaNombreCategoria;
  // ---------------------------------------------------------

  // ---------------------------------------------------------
  while (true)
  {
    arch >> dni;
    arch.get();
    cadena = leerCadenaAux(arch, ',');
    arch >> telefono >> ws;

    separarNombreCategoria(cadena, nombre, categoria);

    tuplaDniTelefono = new int[2];
    tuplaNombreCategoria = new char *[2];
    tuplaDniTelefono[0] = dni;
    tuplaDniTelefono[1] = telefono;
    tuplaNombreCategoria[0] = nombre;
    tuplaNombreCategoria[1] = categoria;

    agregarElemento(dniTelefono, tuplaDniTelefono, nombreCategoria, tuplaNombreCategoria, capacidad, cantidad);

    arch.peek();
    if (arch.eof())
      break;
  }
  // ---------------------------------------------------------
}

void imprimirDniTelefono(ofstream &arch, int *dniTelefono)
{
  arch << setw(15) << dniTelefono[0];
  arch << setw(15) << dniTelefono[1];
}
void imprimirNombreCategoria(ofstream &arch, char **nombreCategoria)
{
  arch << setw(40) << nombreCategoria[0];
  arch << nombreCategoria[1];
}

void ReporteDeClientes(int **dniTelefono, char ***nombreCategoria, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  arch << setw(15) << "DNI";
  arch << setw(15) << "TELEFONO";
  arch << setw(40) << "NOMBRE";
  arch << "CATEGORIA";
  arch << endl;

  for (int i = 0; dniTelefono[i]; i++)
  {
    imprimirDniTelefono(arch, dniTelefono[i]);
    imprimirNombreCategoria(arch, nombreCategoria[i]);
    arch << endl;
  }
}
