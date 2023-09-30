#include "arreglosGenericos.h"
#include "listasGenericas.h"
#include "heroe.h"

int main()
{

  void *arrHeroes, *listaHeroes;

  llenarArreglo(arrHeroes, "heroes.csv");
  qsort(arrHeroes, sizeof(void *), cmpHeroeQsort);
  crearLista(arrHeroes, listaHeroes, leerHeroe);
  imprimirLista(listaHeroes, imprimirHeroe);
  imprimirListaRepetidos(listaHeroes, eliminarHeroe);
  imprimirLista(listaHeroes, imprimirHeroe);

  return 0;
}