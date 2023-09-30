#include "Funciones.h"

int main()
{

  // 20196975,Hijar Pairazaman Jenny Delicia
  int *codigo;
  char **nombre;
  leerAlumnos("Alumnos.csv", codigo, nombre);
  mostrarAlumnos("ReporteAlumnos.txt", codigo, nombre);

  // 20171444,MEC270
  char ***cursos;
  leerCursos("Cursos.csv", codigo, cursos);
  mostrarAlumnosCursos("ReporteAlumnosCursos.txt", codigo, nombre, cursos);

  return 0;
}