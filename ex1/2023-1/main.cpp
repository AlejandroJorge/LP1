#include "Pregunta1.h"
#include "Pregunta2.h"
#include "Pregunta3.h"

int main()
{

  // Pregunta 1

  char ***cursos, ***alumnosNomMod;
  double *cursosCred, escalas[5];
  int **alumnos, *alumnosCod;

  cargaCursoEscalas(cursos, cursosCred, escalas, "Cursos.csv", "Escalas.csv");
  pruebaCargaCursos(cursos, cursosCred, "PruebaCursos.txt");

  cargaAlumnos(alumnos, alumnosCod, alumnosNomMod, "Alumnos.csv");
  pruebaCargaAlumnos(alumnos, alumnosCod, alumnosNomMod, "PruebaAlumnos.txt");

  // Pregunta 2

  char ***cursosCod;
  int ***cursosNotaSemVeces;
  double **costos;

  cargaNotas(cursosCod, cursosNotaSemVeces, costos, alumnos, alumnosNomMod, escalas, cursos, cursosCred, "HistoriaDeNotas.csv");
  pruebaCargaNotas(cursosCod, cursosNotaSemVeces, costos, alumnos, alumnosNomMod, "PruebaDeNotas.txt");

  // Pregunta 3

  void *alumnoVeces;

  CargaCursos(alumnosCod, alumnoVeces, "HistoriaDeNotas.csv");
  ActualizaVeces(alumnoVeces);
  ImprimeAlumno(alumnoVeces);

  return 0;
}