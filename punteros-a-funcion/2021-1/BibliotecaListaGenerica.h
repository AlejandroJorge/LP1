#ifndef BIBLIOTECALISTAGENERICA_H
#define BIBLIOTECALISTAGENERICA_H

#include <fstream>
using namespace std;

enum Lista
{
  L_CABEZA,
  L_COLA,
  L_LONGITUD
};

enum Nodo
{
  N_ELEMENTO,
  N_SIGUIENTE
};

void creaLista(void *&lista, void *leedato(ifstream &arch), int cmpdato(const void *ptrA, const void *ptrB), const char *nomArch);

void insertaLista(void *lista, void *dato, int cmpdato(const void *ptrA, const void *ptrB));

bool listaVacia(void *lista);

void uneLista(void *listaA, void *&listaB);

void imprimeLista(void *lista, void imprimedato(ofstream &arch, void *dato, int &bloquePrevio), const char *nomArch);

#endif /*BIBLIOTECALISTAGENERICA_H*/