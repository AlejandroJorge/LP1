#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "BibliotecaPilaGenerica.h"
#define BUFF 300

void cargaarreglo(void *&arreglo, int cmp(const void *ptrA, const void *ptrB), void *lee(ifstream &arch), const char *nomArch)
{
  void *arr[BUFF]{};
  int size = 0;
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  void *elemento;
  while (true)
  {
    elemento = lee(arch);
    if (elemento == nullptr)
      break;
    arr[size] = elemento;
    size++;
  }
  size++;

  void **arrExacto = new void *[size];
  for (int i = 0; i < size; i++)
    arrExacto[i] = arr[i];

  qsort(arrExacto, size - 1, sizeof(void *), cmp);

  arreglo = arrExacto;
}

void *crearPila()
{
  void **pila = new void *[2];
  pila[P_CABEZA] = nullptr;
  pila[P_LONGITUD] = new int(0);
  return pila;
}

void apilar(void *pila, void *elemento)
{
  void **pi = (void **)pila;
  void **nodo = new void *[2];
  nodo[N_ELEMENTO] = elemento;
  nodo[N_SIGUIENTE] = pi[P_CABEZA];
  pi[P_CABEZA] = nodo;
  ++*(int *)pi[P_LONGITUD];
}

void *desapilar(void *pila)
{
  void **pi = (void **)pila;
  if (pi[P_CABEZA] == nullptr)
  {
    cout << "Se trato de desapilar una pila vacia" << endl;
    exit(1);
  }
  void **tope = (void **)pi[P_CABEZA];
  void *elemento = tope[N_ELEMENTO];
  --*(int *)pi[P_LONGITUD];
  pi[P_CABEZA] = tope[N_SIGUIENTE];
  delete tope;
  return elemento;
}

bool esPilaVacia(void *pila)
{
  void **pi = (void **)pila;
  return pi[P_CABEZA] == nullptr;
}

void cargapila(void *&pila, void *arreglo)
{
  pila = crearPila();
  void **arr = (void **)arreglo;
  for (int i = 0; arr[i]; i++)
    apilar(pila, arr[i]);
}

void hanoi(void *pilaorigen, void *pilapivot, void *piladestino, int nivel)
{
  if (nivel == 0)
    return;
  hanoi(pilaorigen, piladestino, pilapivot, nivel - 1);
  apilar(piladestino, desapilar(pilaorigen));
  hanoi(pilapivot, pilaorigen, piladestino, nivel - 1);
}

void muevepila(void *&pilaini, void *&pilafin)
{
  void **pilaorigen = (void **)pilaini;
  void *pilapivot = crearPila();
  pilafin = crearPila();
  int cantidad = *(int *)pilaorigen[P_LONGITUD];
  hanoi(pilaini, pilapivot, pilafin, cantidad);
}

void imprimepila(void *pilafin, void imprime(void *ptr, ofstream &arch), const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  arch << fixed << left;
  arch.precision(2);

  void **pi = (void **)pilafin;
  void **auxNodo = (void **)pi[P_CABEZA];

  arch << "Cantidad de datos: " << *(int *)pi[P_LONGITUD] << endl;

  while (auxNodo)
  {
    imprime(auxNodo[N_ELEMENTO], arch);
    auxNodo = (void **)auxNodo[N_SIGUIENTE];
  }
}