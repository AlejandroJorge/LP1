#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "AsignacionDinamicaMemoriaExacta.h"
#define BUFFSIZE 1000
#define MINIBUFFSIZE 50

void lecturaDeProductos(const char *nomArch, char ***&productos, int *&stock, double *&precios)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  char **buffProductos[BUFFSIZE]{};
  int buffStock[BUFFSIZE]{};
  double buffPrecios[BUFFSIZE]{};
  int size = 0;

  char *cod, *nom;
  double prec;
  int st;

  char **producto;

  // SSE-115,Refrigeradora  CoolStyle 311N Steel,3243.58,23
  while (true)
  {
    cod = leerCad(arch, ',');
    if (arch.eof())
    {
      delete cod;
      break;
    }
    nom = leerCad(arch, ',');
    arch >> prec;
    arch.get();
    arch >> st;
    arch >> ws;

    producto = new char *[2];
    producto[0] = cod;
    producto[1] = nom;

    buffProductos[size] = producto;
    buffPrecios[size] = prec;
    buffStock[size] = st;
    size++;
  }
  size++;

  productos = new char **[size] {};
  stock = new int[size]{};
  precios = new double[size]{};
  for (int i = 0; i < size; i++)
  {
    productos[i] = buffProductos[i];
    stock[i] = buffStock[i];
    precios[i] = buffPrecios[i];
  }
}

void pruebaDeLecturaDeProductos(const char *nomArch, char ***productos, int *stock, double *precios)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  arch << setw(15) << "CODIGO";
  arch << setw(60) << "NOMBRE";
  arch << setw(15) << "STOCK";
  arch << setw(15) << "PRECIO";
  arch << endl;

  char **producto;
  for (int i = 0; productos[i]; i++)
  {
    producto = productos[i];

    arch << setw(15) << producto[0];
    arch << setw(60) << producto[1];
    arch << setw(15) << stock[i];
    arch << setw(15) << precios[i];
    arch << endl;
  }
}

void lecturaDePedidos(const char *nomArch, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  int buffFechas[BUFFSIZE]{};
  char **buffCodigos[BUFFSIZE]{};
  int **buffDniCant[BUFFSIZE]{};
  int cantidadPedidos[BUFFSIZE]{};
  int size = 0;

  for (int i = 0; i < BUFFSIZE; i++)
  {
    buffCodigos[i] = new char *[MINIBUFFSIZE] {};
    buffDniCant[i] = new int *[MINIBUFFSIZE] {};
  }

  char *cod;
  int dni, cant, fech;
  int *dniCant;
  int pos;

  char **arrCodigos;
  int **arrDniCant;
  while (true)
  {
    // OTS-581,42157219,5,28/08/2023
    cod = leerCad(arch, ',');
    if (arch.eof())
    {
      delete cod;
      break;
    }
    arch >> dni;
    arch.get();
    arch >> cant;
    arch.get();
    fech = leerFecha(arch);
    arch >> ws;

    dniCant = new int[2];
    dniCant[0] = dni;
    dniCant[1] = cant;

    pos = buscarFecha(buffFechas, fech);
    if (pos == -1)
      pos = size++;

    buffFechas[pos] = fech;

    arrCodigos = buffCodigos[pos];
    arrDniCant = buffDniCant[pos];

    arrCodigos[cantidadPedidos[pos]] = cod;
    arrDniCant[cantidadPedidos[pos]] = dniCant;

    cantidadPedidos[pos]++;
  }
  size++;

  for (int i = 0; buffFechas[i]; i++)
    ajustarMemoria(buffCodigos[i], buffDniCant[i], cantidadPedidos[i]);

  fechaPedidos = new int[size];
  dniCantPedidos = new int **[size];
  codigoPedidos = new char **[size];

  for (int i = 0; i < size; i++)
  {
    fechaPedidos[i] = buffFechas[i];
    dniCantPedidos[i] = buffDniCant[i];
    codigoPedidos[i] = buffCodigos[i];
  }
}

void pruebaDeLecturaDePedidos(const char *nomArch, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  char **arrCodigos;
  int **arrDniCant, *dc;
  for (int i = 0; fechaPedidos[i]; i++)
  {
    arch << "FECHA: " << fechaPedidos[i] << endl;
    arch << setw(60) << setfill('-') << "" << setfill(' ') << endl;

    arch << setw(15) << "CODIGO";
    arch << setw(15) << "DNI";
    arch << setw(15) << "CANTIDAD";
    arch << endl;

    arch << setw(60) << setfill('-') << "" << setfill(' ') << endl;

    arrCodigos = codigoPedidos[i];
    arrDniCant = dniCantPedidos[i];
    for (int j = 0; arrCodigos[j]; j++)
    {
      dc = arrDniCant[j];

      arch << setw(15) << arrCodigos[j];
      arch << setw(15) << dc[0];
      arch << setw(15) << dc[1];
      arch << endl;
    }

    arch << setw(60) << setfill('=') << "" << setfill(' ') << endl;
  }
}

void reporteDeEnvioDePedidos(const char *nomArch, char ***productos, int *stock, double *precios,
                             int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);
  int subtotalIngresado, subtotalPerdido, totalIngresado = 0, totalPerdido = 0;
  for (int i = 0; fechaPedidos[i]; i++)
  {
    arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;
    arch << "FECHA: " << fechaPedidos[i] << endl;
    arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;

    arch << setw(10) << "No.";
    arch << setw(10) << "DNI";
    arch << setw(10) << "CODIGO";
    arch << setw(60) << "NOMBRE";
    arch << setw(10) << "CANTIDAD";
    arch << setw(15) << "PRECIO";
    arch << setw(15) << "TOTAL";
    arch << endl;

    arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

    imprimirPedidos(arch, productos, stock, precios, codigoPedidos[i], dniCantPedidos[i], subtotalIngresado, subtotalPerdido);

    arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

    arch << "Total ingresado: " << subtotalIngresado << endl;
    arch << "Total perdido por falta de stock: " << subtotalPerdido << endl;

    totalIngresado += subtotalIngresado;
    totalPerdido += subtotalPerdido;
  }

  arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;
  arch << "Resumen de ingresos" << endl;
  arch << "Total de ingresos en el periodo: " << totalIngresado << endl;
  arch << "Total perdido por falta de stock: " << totalPerdido << endl;
}

void imprimirPedidos(ofstream &arch, char ***productos, int *stock, double *precios, char **codigos, int **dniCants, int &subtotalIngresado, int &subtotalPerdido)
{
  subtotalIngresado = 0;
  subtotalPerdido = 0;

  int posProducto, *dniCant;
  char **producto;
  double ingresos, perdido;
  for (int i = 0; codigos[i]; i++)
  {
    dniCant = dniCants[i];
    posProducto = buscarProducto(productos, codigos[i]);
    if (posProducto == -1)
      continue;

    producto = productos[posProducto];

    if (stock[posProducto] >= dniCant[1])
    {
      ingresos = dniCant[1] * precios[posProducto];
      perdido = 0;
      stock[posProducto] -= dniCant[1];
    }
    else
    {
      ingresos = 0;
      perdido = dniCant[1] * precios[posProducto];
    }

    arch << setw(9) << right << i << left << ")";
    arch << setw(10) << dniCant[0];
    arch << setw(10) << producto[0];
    arch << setw(60) << producto[1];
    arch << setw(10) << dniCant[1];
    arch << setw(10) << right << precios[posProducto] << left;
    if (ingresos)
      arch << setw(10) << right << ingresos << left;
    else
      arch << setw(10) << right << "SIN STOCK" << left;
    arch << endl;

    subtotalIngresado += ingresos;
    subtotalPerdido += perdido;
  }
}

int buscarProducto(char ***productos, char *producto)
{
  char **productoRecorrido;
  for (int i = 0; productos[i]; i++)
  {
    productoRecorrido = productos[i];
    if (strcmp(productoRecorrido[0], producto) == 0)
      return i;
  }
  return -1;
}

char *leerCad(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  if (del == '\n')
    cad[strlen(buff) - 1] = 0;
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
  return d + m * 100 + a * 10000;
}

int buscarFecha(int *arrFechas, int fecha)
{
  for (int i = 0; arrFechas[i]; i++)
    if (fecha == arrFechas[i])
      return i;
  return -1;
}

void ajustarMemoria(char **&arrCodigos, int **&arrDniCant, int cantidad)
{
  char **auxCodigos = new char *[cantidad + 1] {};
  int **auxDniCant = new int *[cantidad + 1] {};
  for (int i = 0; i < cantidad; i++)
  {
    auxCodigos[i] = arrCodigos[i];
    auxDniCant[i] = arrDniCant[i];
  }
  delete arrCodigos;
  delete arrDniCant;
  arrCodigos = auxCodigos;
  arrDniCant = auxDniCant;
}