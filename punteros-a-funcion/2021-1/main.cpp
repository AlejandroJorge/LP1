#include "BibliotecaListaGenerica.h"
#include "Num.h"
#include "Registro.h"

int main()
{

  void *lista1, *lista2;

  creaLista(lista1, leenum, cmpnum, "RegistroDeFaltas1.csv");
  creaLista(lista2, leenum, cmpnum, "RegistroDeFaltas2.csv");
  uneLista(lista1, lista2);
  imprimeLista(lista1, imprimenum, "Repnum.txt");

  creaLista(lista1, leeregistro, cmpregistro, "RegistroDeFaltas1.csv");
  creaLista(lista2, leeregistro, cmpregistro, "RegistroDeFaltas2.csv");
  uneLista(lista1, lista2);
  imprimeLista(lista1, imprimeregistro, "Repfalta.txt");

  return 0;
}