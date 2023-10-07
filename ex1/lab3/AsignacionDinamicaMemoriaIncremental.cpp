#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "AsignacionDinamicaMemoriaIncremental.h"
#define INCREMENTO 5

void lecturaProductos(const char *nomArch, char ***&productos, int *&stock, double *&precios)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  productos = nullptr;
  stock = nullptr;
  precios = nullptr;

  int cantidad = 0, capacidad = 0;

  char *cod, *nom, **producto;
  double prec;
  int st;
  while (true)
  {
    // BIT-434,Campana Extractora modelo Glass,375.09,10
    cod = leerCadena(arch, ',');
    nom = leerCadena(arch, ',');
    arch >> prec;
    arch.get();
    arch >> st >> ws;

    producto = new char *[2];
    producto[0] = cod;
    producto[1] = nom;

    agregarProducto(productos, producto, precios, prec, stock, st, cantidad, capacidad);

    arch.peek();
    if (arch.eof())
      break;
  }
}

void pruebaLecturaProductos(const char *nomArch, char ***productos, int *stock, double *precios)
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

  arch << setw(105) << setfill('=') << "" << setfill(' ') << endl;

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

void lecturaPedidos(const char *nomArch, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos)
{

  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  fechaPedidos = nullptr;
  codigoPedidos = nullptr;
  dniCantPedidos = nullptr;

  int cantidadPedidos[400]{}, capacidadPedidos[400]{};

  char *codigo;
  int dni, cantidad, fecha;
  int cantFechas = 0, capacidadFechas = 0;

  int *dniCant;

  int posFecha;
  while (true)
  {
    // CRU - 009, 50375303, 5, 3 / 09 / 2023
    codigo = leerCadena(arch, ',');
    arch >> dni;
    arch.get();
    arch >> cantidad;
    arch.get();
    fecha = leerFecha(arch);
    arch >> ws;

    dniCant = new int[2];
    dniCant[0] = dni;
    dniCant[1] = cantidad;

    posFecha = buscarFecha(fechaPedidos, fecha);

    if (posFecha == -1)
    {
      posFecha = cantFechas;
      agregarFecha(fechaPedidos, fecha, codigoPedidos, dniCantPedidos, cantFechas, capacidadFechas);
    }

    agregarPedido(codigoPedidos[posFecha], codigo, dniCantPedidos[posFecha], dniCant, cantidadPedidos[posFecha], capacidadPedidos[posFecha]);

    arch.peek();
    if (arch.eof())
      break;
  }
}

void pruebaLecturaPedidos(const char *nomArch, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos)
{

  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  char **codigos;
  int **dniCants, *dniCant;
  for (int i = 0; fechaPedidos[i]; i++)
  {
    arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;
    arch << "FECHA: " << fechaPedidos[i] << endl;
    arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;

    arch << setw(30) << "CODIGO";
    arch << setw(30) << "DNI";
    arch << setw(30) << "CANTIDAD";
    arch << endl;

    arch << setw(90) << setfill('-') << "" << setfill(' ') << endl;

    codigos = codigoPedidos[i];
    dniCants = dniCantPedidos[i];

    for (int j = 0; codigos[j]; j++)
    {
      dniCant = dniCants[j];

      arch << setw(30) << codigos[j];
      arch << setw(30) << dniCant[0];
      arch << setw(30) << dniCant[1];
      arch << endl;
    }
  }
}

void reporteEnvioPedidos(const char *nomArch, char ***productos, int *stock, double *precios, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  double subtotalIngresos, subtotalPerdidas, totalIngresos = 0, totalPerdidas = 0;

  for (int i = 0; fechaPedidos[i]; i++)
  {
    arch << setw(135) << setfill('=') << "" << setfill(' ') << endl;
    arch << "FECHA: " << fechaPedidos[i] << endl;
    arch << setw(135) << setfill('=') << "" << setfill(' ') << endl;

    arch << setw(5) << "No.";
    arch << setw(15) << "DNI";
    arch << setw(15) << "CODIGO";
    arch << setw(55) << "NOMBRE";
    arch << setw(15) << "CANTIDAD";
    arch << setw(15) << "PRECIO";
    arch << setw(15) << "TOTAL";
    arch << endl;

    arch << setw(135) << setfill('-') << "" << setfill(' ') << endl;

    imprimirPedidos(arch, productos, stock, precios, codigoPedidos[i], dniCantPedidos[i], subtotalIngresos, subtotalPerdidas);

    arch << setw(135) << setfill('-') << "" << setfill(' ') << endl;

    arch << "Total ingresado: " << subtotalIngresos << endl;
    arch << "Total perdido por falta de stock: " << subtotalPerdidas << endl;
  }

  arch << setw(135) << setfill('=') << "" << setfill(' ') << endl;

  arch << "RESUMEN DE INGRESOS" << endl;
  arch << setw(60) << "TOTAL DE INGRESOS EN EL PERIODO:" << totalIngresos << endl;
  arch << setw(60) << "TOTAL PERDIDO POR STOCK EN EL PERIODO:" << totalPerdidas << endl;

  arch << setw(135) << setfill('=') << "" << setfill(' ') << endl;
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[150];
  arch.getline(buff, 150, del);
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

void agregarProducto(char ***&productos, char **producto, double *&precios,
                     double prec, int *&stock, int st, int &cantidad, int &capacidad)
{
  if (capacidad == cantidad)
  {
    char ***productosAux = new char **[capacidad + INCREMENTO + 1] {};
    double *preciosAux = new double[capacidad + INCREMENTO + 1]{};
    int *stockAux = new int[capacidad + INCREMENTO + 1]{};

    if (capacidad > 0)
    {
      for (int i = 0; i < cantidad; i++)
      {
        productosAux[i] = productos[i];
        preciosAux[i] = precios[i];
        stockAux[i] = stock[i];
      }

      delete productos;
      delete precios;
      delete stock;
    }

    productos = productosAux;
    precios = preciosAux;
    stock = stockAux;

    capacidad += INCREMENTO;
  }

  productos[cantidad] = producto;
  precios[cantidad] = prec;
  stock[cantidad] = st;

  cantidad++;
}

int buscarFecha(int *arrFechas, int fecha)
{
  if (arrFechas == nullptr)
    return -1;

  for (int i = 0; arrFechas[i]; i++)
    if (arrFechas[i] == fecha)
      return i;
  return -1;
}

void agregarFecha(int *&fechaPedidos, int fecha, char ***&codigoPedidos, int ***&dniCantPedidos, int &cantidadFechas, int &capacidadFechas)
{
  if (capacidadFechas == cantidadFechas)
  {
    int *fechaPedidosAux = new int[capacidadFechas + INCREMENTO + 1]{};
    char ***codigoPedidosAux = new char **[capacidadFechas + INCREMENTO + 1] {};
    int ***dniCantPedidosAux = new int **[capacidadFechas + INCREMENTO + 1] {};

    if (capacidadFechas > 0)
    {
      for (int i = 0; i < cantidadFechas; i++)
      {
        fechaPedidosAux[i] = fechaPedidos[i];
        codigoPedidosAux[i] = codigoPedidos[i];
        dniCantPedidosAux[i] = dniCantPedidos[i];
      }
      delete fechaPedidos;
      delete codigoPedidos;
      delete dniCantPedidos;
    }

    fechaPedidos = fechaPedidosAux;
    codigoPedidos = codigoPedidosAux;
    dniCantPedidos = dniCantPedidosAux;
    capacidadFechas += INCREMENTO;
  }

  fechaPedidos[cantidadFechas] = fecha;
  codigoPedidos[cantidadFechas] = nullptr;
  dniCantPedidos[cantidadFechas] = nullptr;
  cantidadFechas++;
}

void agregarPedido(char **&codigos, char *codigo, int **&dniCants, int *dniCant, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    char **codigosAux = new char *[capacidad + INCREMENTO + 1] {};
    int **dniCantsAux = new int *[capacidad + INCREMENTO + 1] {};

    if (cantidad > 0)
    {
      for (int i = 0; i < cantidad; i++)
      {
        codigosAux[i] = codigos[i];
        dniCantsAux[i] = dniCants[i];
      }
      delete codigos;
      delete dniCants;
    }

    codigos = codigosAux;
    dniCants = dniCantsAux;
    capacidad += INCREMENTO;
  }
  codigos[cantidad] = codigo;
  dniCants[cantidad] = dniCant;
  cantidad++;
}

void imprimirPedidos(ofstream &arch, char ***productos, int *stock, double *precios, char **codigosPed, int **dniCantPed, double &subtotalIngresos, double &subtotalPerdidas)
{
  subtotalIngresos = 0;
  subtotalPerdidas = 0;

  char *codigo, **producto;
  int *dniCant;
  int posProd;

  double ingresos, perdidas;

  for (int i = 0; codigosPed[i]; i++)
  {
    codigo = codigosPed[i];
    dniCant = dniCantPed[i];

    posProd = buscarProducto(productos, codigo);
    if (posProd == -1)
      continue;

    producto = productos[posProd];

    arch << setw(5) << i;
    arch << setw(15) << dniCant[0];
    arch << setw(15) << producto[0];
    arch << setw(55) << producto[1];
    arch << setw(15) << dniCant[1];
    arch << setw(15) << precios[posProd];

    if (dniCant[1] > stock[posProd])
    {
      ingresos = 0;
      perdidas = dniCant[1] * precios[posProd];
      arch << setw(15) << "SIN STOCK";
    }
    else
    {
      ingresos = dniCant[1] * precios[posProd];
      perdidas = 0;
      arch << setw(15) << ingresos;
      stock[posProd] -= dniCant[1];
    }

    arch << endl;

    subtotalIngresos += ingresos;
    subtotalPerdidas += perdidas;
  }
}

int buscarProducto(char ***productos, char *codigo)
{
  char **producto;
  for (int i = 0; productos[i]; i++)
  {
    producto = productos[i];
    if (strcmp(producto[0], codigo) == 0)
      return i;
  }
  return -1;
}