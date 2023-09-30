#include "MetodoDinamicoExacto.h"

int main(void)
{

  int *almCodigo, *almPorcentaje, *almEscala;
  char **almNombre, *almModalidad;

  char **crsNombre;
  double *crsCredito;
  int **crsAlumnos;

  lecturaAlumnos("alumnos.csv", almCodigo, almNombre, almModalidad, almPorcentaje, almEscala);

  pruebaLecturaAlumnos("ReporteAlumnos.txt", almCodigo, almNombre, almModalidad, almPorcentaje, almEscala);

  lecturaCursos("alumnos_cursos.csv", almCodigo, almEscala, crsNombre, crsCredito, crsAlumnos);

  pruebaLecturaCursos("ReporteCursos.txt", crsNombre, crsCredito, crsAlumnos);

  reporteDeRecaudacionPorModalidad("ReporteFinal.txt", almCodigo, almModalidad, almPorcentaje, almNombre, crsNombre, crsCredito, crsAlumnos);

  return 0;
}