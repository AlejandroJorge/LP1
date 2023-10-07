#include <iostream>
#include <fstream>
using namespace std;
#include "FlotaGenerica.h"

void *crearPila()
{
  void **pila = new void *[P_CANTCAMPOS];
  pila[P_CIMA] = nullptr;
  pila[P_PESO] = new double(0);
  return pila;
}

void *crearNodo(void *elemento)
{
  void **nodo = new void *[N_CANTCAMPOS];
  nodo[N_DATO] = elemento;
  nodo[N_SIG] = nullptr;
  return nodo;
}

bool puedeApilar(void **arrPilas, int idx, int numcamiones, double pesomax, void *elemento, double (*calculaelemento)(void *elemento))
{
  if (idx == numcamiones)
    return false;
  void **pila = (void **)arrPilas[idx];
  return (*(double *)pila[P_PESO] + calculaelemento(elemento)) <= pesomax;
}

void apilar(void *pila, void *elemento, double (*calculaelemento)(void *num))
{
  void **pilaCast = (void **)pila;
  void **nuevoNodo = (void **)crearNodo(elemento);
  nuevoNodo[N_SIG] = pilaCast[P_CIMA];
  pilaCast[P_CIMA] = nuevoNodo;
  *(double *)pilaCast[P_PESO] += calculaelemento(elemento);
}

void mostrarPila(ofstream &arch, void *pila, void (*imprimeelemento)(ofstream &arch, void *elemento))
{
  void **pilaCast = (void **)pila;
  void **nodo = (void **)pilaCast[P_CIMA];
  while (nodo)
  {
    imprimeelemento(arch, nodo[N_DATO]);
    nodo = (void **)nodo[N_SIG];
  }
}

void cargacamiones(void *&flota, int numcamiones, double pesomaximo,
                   void *(*leeelemento)(ifstream &arch), double (*calculaelemento)(void *num), const char *nomArch)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  void **arrPilas = new void *[numcamiones];

  for (int i = 0; i < numcamiones; i++)
    arrPilas[i] = crearPila();

  void *elemento;
  int idxPilaActual = 0;
  while (elemento = leeelemento(arch))
  {
    if (calculaelemento(elemento) > pesomaximo)
      continue;
    while (!puedeApilar(arrPilas, idxPilaActual, numcamiones, pesomaximo, elemento, calculaelemento) && idxPilaActual < numcamiones)
      idxPilaActual++;
    if (idxPilaActual == numcamiones)
      break;
    apilar(arrPilas[idxPilaActual], elemento, calculaelemento);
  }

  flota = arrPilas;
}

void muestracamiones(void *flota, int numcamiones, void (*imprimeelemento)(ofstream &arch, void *num), const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  void **arrPilas = (void **)flota;
  void **pila;
  for (int i = 0; i < numcamiones; i++)
  {
    pila = (void **)arrPilas[i];
    arch << "===========================" << endl;
    arch << "Pila Nro " << i + 1 << " con peso " << *(double *)pila[P_PESO] << endl;
    arch << "---------------------------" << endl;
    mostrarPila(arch, pila, imprimeelemento);
  }
}
