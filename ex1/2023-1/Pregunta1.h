#ifndef PREGUNTA1_H
#define PREGUNTA1_H

#include <fstream>
using namespace std;

void cargaCursoEscalas(char ***&cursos, double *&cursosCred, double *escalas, const char *nomCurArch, const char *nomEscArch);
void pruebaCargaCursos(char ***cursos, double *cursosCred, const char *nomArch);

void cargaAlumnos(int **&alumnos, int *&alumnosCod, char ***&alumnosNomMod, const char *nomArch);
void pruebaCargaAlumnos(int **alumnos, int *alumnosCod, char ***alumnosNomMod, const char *nomArch);

char *leerCadena(ifstream &arch, char del);
void agregarCurso(char ***&cursos, char **cursoLeido, double *&cursosCred, double creditos, int &cantidad, int &capacidad);
void pruebaCargaCursos(char ***cursos, double *cursosCred, const char *nomArch);
void leerEscalas(double *escalas, ifstream &arch);
void agregarAlumno(int **&alumnos, int *alumno, int *&alumnosCod, int codigo, char ***&alumnosNomMod, char **alumnoNomMod, int &cantidad, int &capacidad);

#endif /*PREGUNTA1_H*/