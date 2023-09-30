#ifndef METODODINAMICOEXACTO_H
#define METODODINAMICOEXACTO_H

#include <fstream>
using namespace std;

void lecturaAlumnos(const char *nomArch, int *&almCodigo, char **&almNombre, char *&almModalidad, int *&almPorcentaje, int *&almEscala);
void pruebaLecturaAlumnos(const char *nomArch, int *almCodigo, char **almNombre, char *almModalidad, int *almPorcentaje, int *almEscala);
void lecturaCursos(const char *nomArch, int *almCodigo, int *almEscala, char **&crsNombre, double *&crsCredito, int **&crsAlumnos);
void pruebaLecturaCursos(const char *nomArch, char **crsNombre, double *crsCredito, int **crsAlumnos);
void reporteDeRecaudacionPorModalidad(const char *nomArch, int *almCodigo, char *almModalidad, int *almPorcentaje, char **almNombre, char **crsNombre, double *crsCredito, int **crsAlumnos);

char *leerCadena(ifstream &arch, char del = '\n');
char leerModalidad(ifstream &arch);
int buscarCurso(const char *buscado, char **cursos);
void colocarAlumno(int *alumnos, int &cantidad, int codigo);
void asignarEspaciosExactos(int *&arreglo);
void espacioExacto(int *&arr, int nAlu);

#endif