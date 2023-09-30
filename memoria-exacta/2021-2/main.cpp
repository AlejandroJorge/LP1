#include "Tareas.h"

int main(void)
{

  char **codigo, **titulo, **nombre, *tipo;
  int *cantEnBib, *carne;
  double *precio;

  estructurasParaLosLibros_CargaDeDatos(codigo, titulo, cantEnBib, precio);
  estructurasParaLosLibros_Reporte(codigo, titulo, cantEnBib, precio);
  usuariosDeLaBiblioteca_CargaDeDatos(carne, tipo, nombre);
  usuariosDeLaBiblioteca_Reporte(carne, tipo, nombre);
  librosYUsuariosInhabilitados_Reporte(codigo, titulo, cantEnBib, precio, carne, tipo, nombre);

  return 0;
}