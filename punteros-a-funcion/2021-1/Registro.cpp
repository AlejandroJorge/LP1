#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Registro.h"

void *leeregistro(ifstream &arch)
{
  int licencia, fecha, infraccion, d, m, a;
  char *placa = new char[8];
  arch >> licencia;

  if (arch.eof())
    return nullptr;

  arch.get();
  arch.getline(placa, 30, ',');
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;
  arch.get();
  arch >> infraccion;

  fecha = d + m * 100 + a * 10000;

  void **registro = new void *[4];
  registro[R_FECHA] = new int(fecha);
  registro[R_INFRACCION] = new int(infraccion);
  registro[R_LICENCIA] = new int(licencia);
  registro[R_PLACA] = placa;

  return registro;
}

int cmpregistro(const void *ptrRegA, const void *ptrRegB)
{
  void **regA = (void **)ptrRegA;
  void **regB = (void **)ptrRegB;

  int fechaA = *(int *)regA[R_FECHA];
  int fechaB = *(int *)regB[R_FECHA];

  return fechaA - fechaB;
}

void imprimeregistro(ofstream &arch, void *registro, int &bloquePrevio)
{
  void **reg = (void **)registro;

  ifstream archNombres("Conductores.csv", ios::in);
  if (!archNombres)
  {
    cout << "No se pudo abrir el archivo Conductores.csv" << endl;
    exit(1);
  }

  int licencia;
  char nombre[100];
  // 63736112,ZAMORA ZAVALETA RONAL MANUEL
  while (true)
  {
    archNombres >> licencia;
    if (archNombres.eof())
    {
      nombre[0] = '-';
      nombre[1] = 0;
      break;
    }
    if (licencia == *(int *)reg[R_LICENCIA])
    {
      archNombres.get();
      archNombres.getline(nombre, 100);
      nombre[strlen(nombre) - 1] = 0;
      break;
    }
    while (archNombres.get() != '\n')
      ;
  }

  int bloqueActual = *(int *)reg[R_FECHA] / 100;

  if (bloquePrevio != bloqueActual)
  {
    arch << setw(95) << setfill('=') << "" << setfill(' ') << endl;
    arch << "Ano: " << bloqueActual / 100 << " Mes: " << bloqueActual % 100 << endl;
    arch << setw(15) << "FECHA";
    arch << setw(15) << "LICENCIA";
    arch << setw(50) << "NOMBRE";
    arch << setw(15) << "INFRACCION";
    arch << endl;
    arch << setw(95) << setfill('=') << "" << setfill(' ') << endl;
  }

  arch << setw(15) << *(int *)reg[R_FECHA];
  arch << setw(15) << *(int *)reg[R_LICENCIA];
  arch << setw(50) << nombre;
  arch << setw(15) << *(int *)reg[R_INFRACCION];
  arch << endl;

  bloquePrevio = bloqueActual;
}
