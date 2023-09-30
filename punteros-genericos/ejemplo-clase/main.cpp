#include "Tareas.h"

int main(void)
{
  void *alumnos;

  cargarAlumnos(alumnos, "Alumnos.csv");
  reporteAlumnos(alumnos, "Reporte.txt");

  return 0;
}