#include "Tareas.h"

int main(void)
{
  int *dnis;
  char **nombres;
  char ***cursos;

  cargarAlumnos(dnis, nombres);
  cargarCursos(dnis, cursos);
  imprimirReporte(dnis, nombres, cursos);

  return 0;
}