#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define BUFFSIZE 400
#define LEN 80

void abrirArchivo(ifstream &arch, const char *nombreArch)
{
  arch.open(nombreArch, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombreArch << endl;
    exit(1);
  }
}

void abrirArchivo(ofstream &arch, const char *nombreArch)
{
  arch.open(nombreArch, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombreArch << endl;
    exit(1);
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  int len = strlen(buff);
  char *cad = new char[len + 1];
  strcpy(cad, buff);
  // Linux fix
  if (del == '\n')
    cad[len - 1] = 0;
  // Linux fix
  return cad;
}

char leerGravedad(ifstream &arch)
{
  char buff[50];
  arch.getline(buff, 50, ',');
  if (strcmp(buff, "Leve") == 0)
    return 'L';
  if (strcmp(buff, "Grave") == 0)
    return 'G';
  if (strcmp(buff, "Muy Grave") == 0)
    return 'M';

  return ' ';
}

bool esDelTipoCorrecto(int infraccionArch, int *infraccion, char *gravedad, char tipo)
{
  int pos = -1;
  for (int i = 0; infraccion[i]; i++)
  {
    if (infraccion[i] == infraccionArch)
    {
      pos = i;
      break;
    }
  }
  if (pos == -1)
    return false;

  return gravedad[pos] == tipo;
}

int buscarEnEstructura(int *licenciaRepBuff, char **placaBuff, int licenciaArch, char *placaArch)
{
  for (int i = 0; licenciaRepBuff[i]; i++)
    if (licenciaRepBuff[i] == licenciaArch && strcmp(placaBuff[i], placaArch))
      return i;
  return -1;
}

double conseguirMulta(int *infraccion, double *multa, int infraccionArch)
{
  int pos = -1;
  for (int i = 0; infraccion[i]; i++)
    if (infraccion[i] == infraccionArch)
    {
      pos = i;
      break;
    }
  if (pos == -1)
    return 0;
  return multa[pos];
}

void leerDatos(int *&licenciaRep, char **&placa, int *&cantidad, double *&monto,
               int *infraccion, char *gravedad, double *multa, char tipo)
{
  // Archivo
  ifstream arch;
  abrirArchivo(arch, "RegistroDeFaltas.csv");

  // Buffers
  int licenciaRepBuff[BUFFSIZE]{};
  char *placaBuff[BUFFSIZE]{};
  int cantidadBuff[BUFFSIZE]{};
  double montoBuff[BUFFSIZE]{};
  int size = 0;

  // Lectura
  int licenciaArch;
  char *placaArch;
  int infraccionArch;
  int pos;
  while (true)
  {
    // 30441350,M9Z-497,17/03/2020,158
    arch >> licenciaArch;
    if (arch.eof())
      break;
    arch.get();
    placaArch = leerCadena(arch, ',');
    while (arch.get() != ',')
      ;
    arch >> infraccionArch;

    if (esDelTipoCorrecto(infraccionArch, infraccion, gravedad, tipo))
    {
      pos = buscarEnEstructura(licenciaRepBuff, placaBuff, licenciaArch, placaArch);
      if (pos != -1)
      {
        montoBuff[pos] += conseguirMulta(infraccion, multa, infraccionArch);
        cantidadBuff[pos]++;
      }
      else
      {
        licenciaRepBuff[size] = licenciaArch;
        placaBuff[size] = placaArch;
        montoBuff[size] = conseguirMulta(infraccion, multa, infraccionArch);
        cantidadBuff[size]++;
        size++;
      }
    }
  }
  size++;

  // Memoria
  licenciaRep = new int[size];
  placa = new char *[size];
  cantidad = new int[size];
  monto = new double[size];

  // Copiado
  for (int i = 0; i < size; i++)
  {
    licenciaRep[i] = licenciaRepBuff[i];
    placa[i] = placaBuff[i];
    cantidad[i] = cantidadBuff[i];
    monto[i] = montoBuff[i];
  }
}

void imprimirLinea(ofstream &arch, char c)
{
  for (int i = 0; i < LEN; i++)
    arch.put(c);
  arch << endl;
}

void imprimirReporte(ofstream &arch, int *licenciaRep, char **placa, int *cantidad, double *monto)
{
  imprimirLinea(arch, '-');
  arch << setw(15) << "LICENCIA";
  arch << setw(15) << "PLACA";
  arch << setw(15) << "CANTIDAD";
  arch << setw(15) << "MONTO";
  arch << endl;
  imprimirLinea(arch, '-');

  for (int i = 0; licenciaRep[i]; i++)
  {
    arch << setw(15) << licenciaRep[i];
    arch << setw(15) << placa[i];
    arch << setw(15) << cantidad[i];
    arch << setw(15) << monto[i];
    arch << endl;
  }
  imprimirLinea(arch, '-');
}

void liberarMemoria(int *&licenciaRep, char **&placa, int *&cantidad, double *&monto)
{
  for (int i = 0; licenciaRep[i]; i++)
    delete placa[i];
  delete licenciaRep;
  delete cantidad;
  delete monto;
  delete placa;
}