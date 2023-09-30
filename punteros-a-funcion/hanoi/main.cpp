#include <iostream>
using namespace std;

enum Pila
{
  P_CIMA,
  P_LONGITUD
};

enum Nodo
{
  N_ELEMENTO,
  N_SIGUIENTE
};

void *crearPila()
{
  void **pila = new void *[2];
  pila[P_CIMA] = nullptr;
  pila[P_LONGITUD] = new int(0);
  return pila;
}

int cantidad(void *pila)
{
  void **pil = (void **)pila;
  return *(int *)pil[P_LONGITUD];
}

void *crearNodo(void *elemento, void *siguiente = nullptr)
{
  void **nodo = new void *[2];
  nodo[N_ELEMENTO] = elemento;
  nodo[N_SIGUIENTE] = siguiente;
  return nodo;
}

void apilar(void *pila, void *elemento)
{
  void **pil = (void **)pila;
  pil[P_CIMA] = crearNodo(elemento, pil[P_CIMA]);
  ++*(int *)pil[P_LONGITUD];
}

void *desapilar(void *pila)
{
  void **pil = (void **)pila;
  if (pil[P_CIMA] == nullptr)
    return nullptr;
  void **nodoExtraido = (void **)pil[P_CIMA];
  void *elm = nodoExtraido[N_ELEMENTO];
  pil[P_CIMA] = nodoExtraido[N_SIGUIENTE];
  delete nodoExtraido;
  return elm;
}

void imprimir(void *pila)
{
  void **pil = (void **)pila;
  void **aux = (void **)pil[P_CIMA];
  cout << "Imprimiendo pila" << endl;
  while (aux)
  {
    cout << *(int *)aux[N_ELEMENTO] << endl;
    aux = (void **)aux[N_SIGUIENTE];
  }
  cout << "--------------------------------" << endl;
}

void hanoi(void *origen, void *pivot, void *destino, int cantidad)
{
  if (cantidad == 0)
    return;
  hanoi(origen, destino, pivot, cantidad - 1);
  apilar(destino, desapilar(origen));
  hanoi(pivot, origen, destino, cantidad - 1);
}

int main()
{

  void *pila = crearPila();
  void *pivot = crearPila();
  void *pilaFinal = crearPila();
  apilar(pila, new int(5));
  apilar(pila, new int(4));
  apilar(pila, new int(3));
  apilar(pila, new int(2));

  imprimir(pila);
  hanoi(pila, pivot, pilaFinal, cantidad(pila));
  imprimir(pila);
  imprimir(pilaFinal);

  return 0;
}