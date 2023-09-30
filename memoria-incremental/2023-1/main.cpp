#include "tareas.h"

int main()
{

  char ***cursoDatos, ****cursoAlumnos;
  int *cursoCredito;
  double **cursoInformacionEconomica;

  CargarCursos("archMatricula.csv", cursoDatos, cursoCredito, cursoAlumnos, cursoInformacionEconomica);

  return 0;
}