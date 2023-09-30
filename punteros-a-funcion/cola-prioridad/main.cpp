#include <iostream>
using namespace std;

enum Cola
{
  C_HEAD,
  C_REAR
};

enum Nodo
{
  N_SIG,
  N_ELM
};

enum ColaConPrioridad
{
  CCP_CANTPRIORIDADES,
  CCP_COLAS
};

void *crearCola()
{
  void **cola = new void *[2];
  cola[C_HEAD] = nullptr;
  cola[C_REAR] = nullptr;
  return cola;
}

void *crearNodo(void *elm)
{
  void **nodo = new void *[2];
  nodo[N_ELM] = elm;
  nodo[N_SIG] = nullptr;
  return nodo;
}

void encolar(void *cola, void *elm)
{
  void **col = (void **)cola;
  void **nuevoNodo = (void **)crearNodo(elm);
  if (col[C_REAR] == nullptr)
  {
    col[C_HEAD] = nuevoNodo;
    col[C_REAR] = nuevoNodo;
    return;
  }
  void **prevUltimo = (void **)col[C_REAR];
  prevUltimo[N_SIG] = nuevoNodo;
  col[C_REAR] = nuevoNodo;
}

void *desencolar(void *cola)
{
  void **col = (void **)cola;
  if (col[C_HEAD] == nullptr)
  {
    cout << "Se intento desencolar de una cola vacia" << endl;
    exit(1);
  }
  void **nodo = (void **)col[C_HEAD];
  col[C_HEAD] = nodo[N_SIG];
  void *elem = nodo[N_ELM];
  delete nodo;
  return elem;
}

void mostrarCola(void *cola, void mostrarElemento(void *elm))
{
  void **col = (void **)cola;
  void **aux = (void **)col[C_HEAD];
  while (aux)
  {
    mostrarElemento(aux[N_ELM]);
    aux = (void **)aux[N_SIG];
  }
}

void *crearElemento(int n)
{
  void *elm = new int(n);
  return elm;
}

void imprimirElemento(void *elm)
{
  cout << *(int *)elm << endl;
}

void *crearColaConPrioridad(int cantPrioridades)
{
  void **colaConPrioridad = new void *[2];
  colaConPrioridad[CCP_CANTPRIORIDADES] = new int(cantPrioridades);
  colaConPrioridad[CCP_COLAS] = new void *[cantPrioridades];
  void **subcolas = (void **)colaConPrioridad[CCP_COLAS];
  for (int i = 0; i < cantPrioridades; i++)
    subcolas[i] = crearCola();
  return colaConPrioridad;
}

void encolarConPrioridad(void *colaConPrioridad, void *elem, int prioridad)
{
  void **col = (void **)colaConPrioridad;
  int cantPrio = *(int *)col[CCP_CANTPRIORIDADES];
  if (prioridad >= cantPrio || prioridad < 0)
  {
    cout << "Se intento encolar con una prioridad no valida" << endl;
    exit(1);
  }
  void **subcolas = (void **)col[CCP_COLAS];
  void *colaCorrespondiente = subcolas[prioridad];
  encolar(colaCorrespondiente, elem);
}

void mostrarColaConPrioridad(void *colaConPrioridad, void mostrarElemento(void *elm))
{
  void **colConPrio = (void **)colaConPrioridad;
  void **subcolas = (void **)colConPrio[CCP_COLAS];
  int cantSubcolas = *(int *)colConPrio[CCP_CANTPRIORIDADES];
  void **cola;
  for (int i = 0; i < cantSubcolas; i++)
  {
    cola = (void **)subcolas[i];
    if (cola[C_HEAD] != nullptr)
    {
      cout << "==========================" << endl;
      cout << "Prioridad " << i << endl;
      mostrarCola(cola, mostrarElemento);
    }
  }
}

void *desencolarConPrioridad(void *colaConPrioridad, int prio)
{
  void **col = (void **)colaConPrioridad;
  int cantPrio = *(int *)col[CCP_CANTPRIORIDADES];
  if (prio >= cantPrio || prio < 0)
  {
    cout << "Se intento desencolar con una prioridad no valida" << endl;
    exit(1);
  }
  void **subcolas = (void **)col[CCP_COLAS];
  void *colaCorrespondiente = subcolas[prio];
  return desencolar(colaCorrespondiente);
}

void *desencolarSimpleCCP(void *colaConPrioridad)
{
  void **col = (void **)colaConPrioridad;
  int cantPrio = *(int *)col[CCP_CANTPRIORIDADES];
  void **subcolas = (void **)col[CCP_COLAS];
  void **colaActual;
  for (int i = cantPrio - 1; i >= 0; i--)
  {
    colaActual = (void **)subcolas[i];
    if (colaActual[C_HEAD] == nullptr)
      continue;
    return desencolar(colaActual);
  }
  cout << "Se intento desencolar de una cola con prioridad vacia" << endl;
  exit(1);
}

int main()
{
  void *colaConPrioridad = crearColaConPrioridad(5); // Create a priority queue with 5 priorities

  // Enqueue elements with different priorities
  encolarConPrioridad(colaConPrioridad, crearElemento(5), 2);
  encolarConPrioridad(colaConPrioridad, crearElemento(6), 0);
  encolarConPrioridad(colaConPrioridad, crearElemento(7), 3);
  encolarConPrioridad(colaConPrioridad, crearElemento(8), 1);
  encolarConPrioridad(colaConPrioridad, crearElemento(9), 0);

  // Display the priority queue
  mostrarColaConPrioridad(colaConPrioridad, imprimirElemento);

  // Dequeue elements with specified priorities
  void *element1 = desencolarConPrioridad(colaConPrioridad, 0);
  void *element2 = desencolarConPrioridad(colaConPrioridad, 1);

  // Display the updated priority queue
  cout << "\nPriority Queue after dequeuing 2 elements:\n";
  mostrarColaConPrioridad(colaConPrioridad, imprimirElemento);

  // Dequeue elements without specifying priorities (simple dequeue)
  void *element3 = desencolarSimpleCCP(colaConPrioridad);
  void *element4 = desencolarSimpleCCP(colaConPrioridad);

  // Display the updated priority queue
  cout << "\nPriority Queue after simple dequeue of 2 elements:\n";
  mostrarColaConPrioridad(colaConPrioridad, imprimirElemento);

  // Clean up memory (optional but recommended)
  delete (int *)element1;
  delete (int *)element2;
  delete (int *)element3;
  delete (int *)element4;

  return 0;
}
