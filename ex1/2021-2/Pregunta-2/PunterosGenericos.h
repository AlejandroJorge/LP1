#ifndef PUNTEROSGENERICOS_H
#define PUNTEROSGENERICOS_H

#include <fstream>
using namespace std;

enum Libro
{
  LI_CODIGO,
  LI_TITULO,
  LI_AUTOR,
  LI_COPIAS,
  LI_STOCK,
  LI_PRECIO,
  LI_DETALLES,
  LI_CANTCAMPOS
};

enum Detalle
{
  DE_NUMCOPIA,
  DE_ESTADO,
  DE_FECHA,
  DE_VALOR,
  DE_CANTCAMPOS
};

enum Estados
{
  DISPONIBLE,
  PRESTAMO,
  PERDIDO
};

void cargalibros(void *&stock);
void actualiza(void *stock);
void imprimestock(void *stock);

char *leerCadena(ifstream &arch, char del);
int leerFecha(ifstream &arch);
void **buscarLibro(void *stock, char *codigo);

#endif /*PUNTEROSGENERICOS_H*/
