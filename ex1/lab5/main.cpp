#include <cstdlib>
using namespace std;
#include "FlotaGenerica.h"
#include "PilaConEnteros.h"
#include "PilaConRegistros.h"

int main(int argc, char **argv)
{
  int numcamiones;
  double pesomaximo;
  void *flota;
  numcamiones = 5;
  pesomaximo = 10;

  cargacamiones(flota, numcamiones, pesomaximo, leenumero, calculanumero, "numeros.txt");
  qsort(flota, numcamiones, sizeof(void *), cmpnumero);
  muestracamiones(flota, numcamiones, imprimenumero, "reportenum.txt");

  numcamiones = 100;
  pesomaximo = 400;

  cargacamiones(flota, numcamiones, pesomaximo, leeregistro, calcularegistro, "Pedidos3.csv");
  qsort(flota, numcamiones, sizeof(void *), cmpregistro);
  muestracamiones(flota, numcamiones, imprimeregistro, "reporteregistro.txt");

  return 0;
}