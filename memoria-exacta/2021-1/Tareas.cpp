#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Utilidades.h"
#define BUFFSIZE 200

void cargarConductores(int *&licencia, char **&conductor)
{
  // Archivo
  ifstream arch;
  abrirArchivo(arch, "Conductores.csv");

  // Buffers
  int licenciaBuff[BUFFSIZE]{};
  char *conductorBuff[BUFFSIZE]{};
  int size = 0;

  // Lectura
  int licenciaArch;
  char *conductorArch;
  while (true)
  {
    // 53853385,SOLIS NARVAEZ MARIA MADELEINE
    arch >> licenciaArch;
    if (arch.eof())
      break;
    arch.get();
    conductorArch = leerCadena(arch, '\n');

    licenciaBuff[size] = licenciaArch;
    conductorBuff[size] = conductorArch;
    size++;
  }
  size++;

  // Memoria
  licencia = new int[size];
  conductor = new char *[size];

  // Copiado
  for (int i = 0; i < size; i++)
  {
    licencia[i] = licenciaBuff[i];
    conductor[i] = conductorBuff[i];
  }
}

void reporteConductores(int *licencia, char **conductor)
{
  ofstream arch;
  abrirArchivo(arch, "ReporteConductores.txt");

  for (int i = 0; licencia[i]; i++)
    arch << licencia[i] << " " << conductor[i] << endl;
}

void cargarInfracciones(int *&infraccion, char *&gravedad, double *&multa)
{
  // Archivo
  ifstream arch;
  abrirArchivo(arch, "Infracciones.csv");

  // Buffers
  int infraccionBuff[BUFFSIZE]{};
  char gravedadBuff[BUFFSIZE]{};
  double multaBuff[BUFFSIZE]{};
  int size = 0;

  // Lectura
  int infraccionArch;
  char gravedadArch;
  double multaArch;
  while (true)
  {
    // 104,No detenerse antes de la l�nea de parada o antes de las �reas de intersecci�n de calzadas o no respetar el derecho de paso del peat�n.,Grave,316.00
    arch >> infraccionArch;
    if (arch.eof())
      break;
    arch.get();
    while (arch.get() != ',')
      ;
    gravedadArch = leerGravedad(arch);
    arch >> multaArch;

    infraccionBuff[size] = infraccionArch;
    gravedadBuff[size] = gravedadArch;
    multaBuff[size] = multaArch;
    size++;
  }
  size++;

  // Memoria
  infraccion = new int[size];
  gravedad = new char[size];
  multa = new double[size];

  // Copiado
  for (int i = 0; i < size; i++)
  {
    infraccion[i] = infraccionBuff[i];
    gravedad[i] = gravedadBuff[i];
    multa[i] = multaBuff[i];
  }
}

void reporteInfracciones(int *infraccion, char *gravedad, double *multa)
{
  ofstream arch;
  abrirArchivo(arch, "ReporteInfracciones.txt");

  for (int i = 0; infraccion[i]; i++)
    arch << infraccion[i] << " " << gravedad[i] << " " << multa[i] << endl;
}

void reporteDeFaltas(int *licencia, char **conductor, int *infraccion, char *gravedad, double *multa)
{
  int *licenciaRep;
  char **placa;
  int *cantidad;
  double *monto;

  ofstream arch;
  abrirArchivo(arch, "ReporteFinal.txt");
  arch << fixed << left;
  arch.precision(2);

  leerDatos(licenciaRep, placa, cantidad, monto, infraccion, gravedad, multa, 'L');

  imprimirLinea(arch, '=');
  arch << "FALTAS LEVES" << endl
       << endl;
  imprimirLinea(arch, '=');

  imprimirReporte(arch, licenciaRep, placa, cantidad, monto);
  liberarMemoria(licenciaRep, placa, cantidad, monto);

  leerDatos(licenciaRep, placa, cantidad, monto, infraccion, gravedad, multa, 'G');

  imprimirLinea(arch, '=');
  arch << "FALTAS GRAVES" << endl
       << endl;
  imprimirReporte(arch, licenciaRep, placa, cantidad, monto);
  imprimirLinea(arch, '=');

  liberarMemoria(licenciaRep, placa, cantidad, monto);

  leerDatos(licenciaRep, placa, cantidad, monto, infraccion, gravedad, multa, 'M');

  imprimirLinea(arch, '=');
  arch << "FALTAS MUY GRAVES" << endl
       << endl;
  imprimirReporte(arch, licenciaRep, placa, cantidad, monto);
  imprimirLinea(arch, '=');

  liberarMemoria(licenciaRep, placa, cantidad, monto);
}