#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "BibliotecaListaGenerica.h"

void creaLista(void *&lista, void *leedato(ifstream &arch), int cmpdato(const void *ptrA, const void *ptrB), const char *nomArch)
{
  void **lis = new void *[3];
  lis[L_CABEZA] = nullptr;
  lis[L_COLA] = nullptr;
  lis[L_LONGITUD] = new int(0);

  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  void *dato = nullptr;
  while (true)
  {
    dato = leedato(arch);
    if (dato == nullptr)
      break;
    insertaLista(lis, dato, cmpdato);
  }

  lista = lis;
}

void insertaLista(void *lista, void *dato, int cmpdato(const void *ptrA, const void *ptrB))
{
  void **lis = (void **)lista;

  void **nodoNuevo = new void *[2];
  nodoNuevo[N_ELEMENTO] = dato;
  nodoNuevo[N_SIGUIENTE] = nullptr;

  void **nodoActual = (void **)lis[L_CABEZA];
  void **nodoAnterior = nullptr;

  if (nodoActual == nullptr)
  {
    lis[L_CABEZA] = nodoNuevo;
    lis[L_COLA] = nodoNuevo;
    return;
  }

  for (int i = 0; i < *(int *)lis[L_LONGITUD]; i++)
  {
    if (cmpdato(nodoActual[N_ELEMENTO], nodoNuevo[N_ELEMENTO]) > 0)
      break;
    nodoAnterior = nodoActual;
    nodoActual = (void **)nodoActual[N_SIGUIENTE];
  }

  nodoNuevo[N_SIGUIENTE] = nodoActual;

  if (nodoAnterior == nullptr)
    lis[L_CABEZA] = nodoNuevo;
  else
    nodoAnterior[N_SIGUIENTE] = nodoNuevo;

  if (nodoActual == nullptr)
    lis[L_COLA] = nodoNuevo;

  ++*(int *)lis[L_LONGITUD];
}

bool listaVacia(void *lista)
{
  return ((void **)lista)[L_LONGITUD] == 0;
}

void uneLista(void *listaA, void *&listaB)
{
  void **lisA = (void **)listaA;
  void **lisB = (void **)listaB;
  lisA[L_COLA] = lisB[L_CABEZA];
  *(int *)lisA[L_LONGITUD] += *(int *)lisB[L_LONGITUD];
  delete lisB;
}

void imprimeLista(void *lista, void imprimedato(ofstream &arch, void *dato, int &bloquePrevio), const char *nomArch)
{
  void **lis = (void **)lista;
  void **nodo = (void **)lis[L_CABEZA];

  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  arch << fixed << left;
  arch.precision(2);

  int bloquePrevio = 0;

  while (nodo)
  {
    imprimedato(arch, nodo[N_ELEMENTO], bloquePrevio);
    nodo = (void **)nodo[N_SIGUIENTE];
  }
}