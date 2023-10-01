#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;
#include "PunterosGenericos.h"
#define BUFF 300
#define FECHAACTUAL 20211019

void cargalibros(void *&stock)
{
  void *buffLibros[BUFF]{};
  int size = 0;

  ifstream arch("Libros2.csv");
  if (!arch)
  {
    cout << "No se pudo abrir Libros2.csv" << endl;
    exit(1);
  }

  void **libro;
  char *codigo, *titulo, *autor;
  int edicion, stk;
  double precio;

  void **arrDetalles;
  void **detalle;

  while (true)
  {
    // PT00038,El_nino_perdido,Giovana/Mejia/Zegarra,2008,15,80.23
    codigo = leerCadena(arch, ',');
    if (arch.eof())
      break;
    titulo = leerCadena(arch, ',');
    autor = leerCadena(arch, ',');
    arch >> edicion;
    arch.get();
    arch >> stk;
    arch.get();
    arch >> precio;
    arch >> ws;

    libro = new void *[LI_CANTCAMPOS];
    libro[LI_AUTOR] = autor;
    libro[LI_CODIGO] = codigo;
    libro[LI_TITULO] = titulo;
    libro[LI_STOCK] = new int(stk);
    libro[LI_PRECIO] = new double(precio);
    libro[LI_COPIAS] = new int(stk);
    libro[LI_DETALLES] = new void *[stk];

    arrDetalles = (void **)libro[LI_DETALLES];

    for (int i = 0; i < stk; i++)
    {
      detalle = new void *[DE_CANTCAMPOS];
      detalle[DE_NUMCOPIA] = new int(i + 1);
      detalle[DE_FECHA] = new int(0);
      detalle[DE_VALOR] = new double(0);
      detalle[DE_ESTADO] = new int(DISPONIBLE);

      arrDetalles[i] = detalle;
    }

    buffLibros[size] = libro;
    size++;
  }
  size++;

  void **arrExacto = new void *[size];
  for (int i = 0; i < size; i++)
    arrExacto[i] = buffLibros[i];
  stock = arrExacto;
}

void actualiza(void *stock)
{
  ifstream arch("RegistroDePrestamos2.csv");
  if (!arch)
  {
    cout << "No se pudo abrir RegistroDePrestamos2.csv" << endl;
    exit(1);
  }

  void **libro, **detalle, **detalles;
  char *codigo, *cad;
  int num, fecha;
  while (true)
  {
    // 81082011D,FY25192,11,12/09/2021
    cad = leerCadena(arch, ',');
    delete cad;
    codigo = leerCadena(arch, ',');
    if (arch.eof())
      break;
    arch >> num;
    arch.get();
    fecha = leerFecha(arch);
    arch >> ws;

    libro = buscarLibro(stock, codigo);

    if (libro == nullptr)
      continue;

    if (num > *(int *)libro[LI_COPIAS] || num < 1)
      continue;

    detalles = (void **)libro[LI_DETALLES];
    detalle = (void **)detalles[num - 1];

    if (FECHAACTUAL / 100 - fecha / 100 < 2)
    {
      *(int *)detalle[DE_ESTADO] = PRESTAMO;
    }
    else
    {
      *(int *)detalle[DE_ESTADO] = PERDIDO;
      *(double *)detalle[DE_VALOR] = *(double *)libro[LI_PRECIO];
    }
    *(int *)detalle[DE_FECHA] = fecha;
  }
}

void imprimestock(void *stock)
{
  void **arrLibros = (void **)stock;
  void **libro;

  ofstream arch("RepStock.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir RepStock.txt" << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  arch << setw(15) << "CODIGO";
  arch << setw(45) << "TITULO";
  arch << setw(30) << "AUTOR";
  arch << setw(15) << "COPIAS";
  arch << setw(15) << "STOCK";
  arch << endl;

  void **arrDetalles;
  void **detalle;
  for (int i = 0; arrLibros[i]; i++)
  {
    libro = (void **)arrLibros[i];
    arch << setw(15) << (char *)libro[LI_CODIGO];
    arch << setw(45) << (char *)libro[LI_TITULO];
    arch << setw(30) << (char *)libro[LI_AUTOR];
    arch << setw(15) << *(int *)libro[LI_COPIAS];
    arch << setw(15) << *(int *)libro[LI_STOCK];
    arch << endl;

    arrDetalles = (void **)libro[LI_DETALLES];
    if (arrDetalles == nullptr)
      continue;

    for (int i = 0; i < *(int *)libro[LI_COPIAS]; i++)
    {
      detalle = (void **)arrDetalles[i];
      arch << setw(15) << *(int *)detalle[DE_NUMCOPIA];
      switch (*(int *)detalle[DE_ESTADO])
      {
      case DISPONIBLE:
        arch << setw(30) << "Disponible";
        break;
      case PRESTAMO:
        arch << setw(30) << "Prestamo";
        break;
      case PERDIDO:
        arch << setw(30) << "Perdido";
        break;
      }
      if (*(int *)detalle[DE_ESTADO] != DISPONIBLE)
        arch << setw(30) << *(int *)detalle[DE_FECHA];
      if (*(int *)detalle[DE_ESTADO] == PERDIDO)
        arch << setw(15) << *(double *)detalle[DE_VALOR];
      arch << endl;
    }
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  return cad;
}

int leerFecha(ifstream &arch)
{
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;

  return a * 10000 + m * 100 + d;
}

void **buscarLibro(void *stock, char *codigo)
{
  void **arrLibros = (void **)stock;
  void **libro;
  for (int i = 0; arrLibros[i]; i++)
  {
    libro = (void **)arrLibros[i];
    if (strcmp((char *)libro[LI_CODIGO], codigo) == 0)
      return libro;
  }
  return nullptr;
}