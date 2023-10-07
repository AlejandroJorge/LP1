#ifndef PREGUNTA2_H
#define PREGUNTA2_H

void cargaNotas(char ***&cursosCod, int ***&cursosNotaSemVeces, double **&costos, int **alumnos, char ***alumnosNomMod, double *escalas, char ***cursos, double *cursosCred, const char *nomArch);
void pruebaCargaNotas(char ***cursosCod, int ***cursosNotaSemVeces, double **costos, int **alumnos, char ***alumnosNomMod, const char *nomArch);

void corregirEspacios(char **&cursosCod, int **&cursosNotaSemVeces, double *&costos, int cantidad);
void agregarCurso(char **codigosCurso, int **notaSemVeces, double *costos, char **curso, double creditos, double precioEscala, int nota, int semestre, int &cantidad);
int buscarAlumno(int **alumnos, int codigo);
int buscarCurso(char ***cursos, char *codigo);
double obtenerPrecioEscala(int *alumno, double *escalas);
void imprimirCursos(ofstream &arch, char **codigos, int **NSVs, double *costos);

#endif /*PREGUNTA2_H*/