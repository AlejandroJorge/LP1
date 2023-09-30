#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "tareas.h"
#define INCREMENTO 5

void CargarCursos(const char *nomArch, char ***&cursoDatos,
                  int *&cursoCredito, char ****&cursoAlumnos,
                  double **&cursoInformacionEconomica)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  int capCursos = 0, cantCursos = 0;
  char *codigoCur, *nombreCur, *nombrePer;
  double creditos;
  int codigoPer;
  int escalaPer;
  char c;
  int *codigosPersonas = nullptr;
  int *escalasPersonas = nullptr;

  while (true)
  {
    // INF263,Algoritmia,4,PATINO MEZA MANUEL,20239927.3,LEE VASQUEZ JENNY,20239103.4,GORDILLO BOLANOS ARTURO GONZALO,20238383.3,NORABUENA RIVERA GLORIA YESSICA,20238320.5,TOKESHI GONZALES MARTIN,20238318.1,RIVERA MONTERO GLORIA OFELIA,20238072.3,ZEGARRA CUBA ANTONIO,20236517.2,ALFARO FUENTES MAGDA,20236015.3,CORREA AGUIRRE MOISES,20235763.2,VEGA SAENZ ALEXANDER RICHARD,20235724.4
    codigoCur = leerCadena(arch, ',');
    if (arch.eof())
      break;
    nombreCur = leerCadena(arch, ',');
    arch >> creditos;
    while (arch.get() == ',')
    {
      nombrePer = leerCadena(arch, ',');
      arch >> codigoPer;
      arch.get();
      arch >> 
    }
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cadena = new char[strlen(buff) + 1];
  strcpy(cadena, buff);
  if (del == '\n')
    cadena[strlen(buff) - 1] = 0;
  return cadena;
}