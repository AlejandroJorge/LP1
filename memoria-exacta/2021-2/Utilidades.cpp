#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Utilidades.h"
#define BUFFSIZE 300
#define LEN 80

void abrir(ifstream &arch, const char *nombre)
{
  arch.open(nombre, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombre << endl;
    exit(1);
  }
}

void abrir(ofstream &arch, const char *nombre)
{
  arch.open(nombre, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombre << endl;
    exit(1);
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

void cargarDatos(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda,
                 char **codigo, double *precio, int *&cantEnBib, int *carne, char **nombre, double *&montoPorDeuda, char tipo)
{
  // Archivo
  ifstream arch;
  abrir(arch, "RegistroDePrestamos.csv");

  // Buffers
  int carneDeudaBuff[BUFFSIZE]{};
  int cantDeudaBuff[BUFFSIZE]{};
  char *nombreDeudaBuff[BUFFSIZE]{};
  double montoDeudaBuff[BUFFSIZE]{};
  int size = 0;

  // Monto por deuda
  int len = 0;
  while (codigo[len])
    len++;
  montoPorDeuda = new double[len]{};

  // Lectura
  int carneLeido;
  char tipoLeido;
  char *codigoLeido;
  int fechaLeida;
  int pos;
  int fechaActual = 2021924;
  while (true)
  {
    // 50860318E,SA04133,21/09/2021
    arch >> carneLeido;
    tipoLeido = arch.get();
    arch.get();
    codigoLeido = leerCadena(arch, ',');
    fechaLeida = leerFecha(arch);
    if (arch.eof())
      break;

    if (tipoLeido != tipo)
      continue;
    if (fechaLeida <= fechaActual)
      continue;
    pos = buscarCarne(carneDeudaBuff, carneLeido);
    if (pos == -1)
    {
      carneDeudaBuff[size] = carneLeido;
      cantDeudaBuff[size] = 1;
      nombreDeudaBuff[size] = buscarNombre(carne, nombre, carneLeido);
      montoDeudaBuff[size] = buscarPrecio(codigo, precio, codigoLeido);
      size++;
    }
    else
    {
      cantDeudaBuff[pos]++;
      montoDeudaBuff[pos] += buscarPrecio(codigo, precio, codigoLeido);
    }
    disminuirStock(codigo, cantEnBib, codigoLeido);
    // actualizarMontoPorDeuda(montoDeuda, codigo, precio, codigoLeido);
  }
  size++;

  // Memoria
  carneDeuda = new int[size];
  nombreDeuda = new char *[size];
  cantDeuda = new int[size];
  montoDeuda = new double[size];

  // Copiado
  for (int i = 0; i < size; i++)
  {
    carneDeuda[i] = carneDeudaBuff[i];
    nombreDeuda[i] = nombreDeudaBuff[i];
    cantDeuda[i] = cantDeudaBuff[i];
    montoDeuda[i] = montoDeudaBuff[i];
  }
}

int leerFecha(ifstream &arch)
{
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a >> ws;
  return a * 10000 + m * 100 + d;
}

int buscarCarne(int *carneDeudaBuff, int carneLeido)
{
  for (int i = 0; carneDeudaBuff[i]; i++)
    if (carneDeudaBuff[i] == carneLeido)
      return i;

  return -1;
}

char *buscarNombre(int *carne, char **nombre, int carneLeido)
{
  for (int i = 0; carne[i]; i++)
    if (carne[i] == carneLeido)
      return nombre[i];

  cout << "No se encontro el nombre correspondiente a " << carneLeido << ", error fatal" << endl;
  exit(2);
}

double buscarPrecio(char **codigo, double *precio, char *codigoLeido)
{
  for (int i = 0; codigo[i]; i++)
    if (strcmp(codigo[i], codigoLeido))
      return precio[i];

  cout << "No se encontro el precio correspondiente a " << codigoLeido << ", error fatal" << endl;
  exit(2);
}

void disminuirStock(char **codigo, int *cantEnBib, char *codigoLeido)
{
  for (int i = 0; codigo[i]; i++)
    if (strcmp(codigo[i], codigoLeido))
    {
      cantEnBib[i]--;
      return;
    }
}

void imprimirReporte(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda, ofstream &arch)
{
  arch << setw(15) << "CARNE";
  arch << setw(10) << "CANTIDAD";
  arch << setw(50) << "NOMBRE";
  arch << setw(10) << "MONTO";
  arch << endl;

  for (int i = 0; carneDeuda[i]; i++)
  {
    arch << setw(15) << carneDeuda[i];
    arch << setw(10) << cantDeuda[i];
    arch << setw(50) << nombreDeuda[i];
    arch << setw(10) << montoDeuda[i];
    arch << endl;
  }
}
void liberarDatos(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda)
{
  delete carneDeuda;
  delete cantDeuda;
  for (int i = 0; nombreDeuda[i]; i++)
    delete nombreDeuda[i];
  delete nombreDeuda;
  delete montoDeuda;
}

void imprimirLinea(ofstream &arch, char c)
{
  for (int i = 0; i < LEN; i++)
    arch.put(c);
  arch << endl;
}

void imprimirStockLibros(char **codigo, char **titulo, int *cantEnBib, double *precio, double *montoDeuda)
{
}

void actualizarMontoPorDeuda(double *montoDeuda, char **codigo, double *precio, char *codigoLeido)
{
  for (int i = 0; codigo[i]; i++)
    if (strcmp(codigo[i], codigoLeido) == 0)
      montoDeuda[i] += precio[i];
  cout << "No se encontro el precio correspondiente a " << codigoLeido << endl;
  return;
}
