#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void leerAlumnos(const char *archNombre, int *&codigo, char **&nombre);
void mostrarAlumnos(const char *nomArch, int *codigo, char **nombre);

void leerCursos(const char *nomArch, int *codigo, char ***&cursos);
void mostrarAlumnosCursos(const char *nomArch, int *codigo, char **nombre, char ***cursos);

char *leerCadena(ifstream &arch, char del);
int buscarCodigo(int *codigo, int cod);
void agregarCurso(char **&cursos, char *curso, int &cantidad, int &capacidad);
void imprimirCursos(ofstream &arch, char **cursos);

#endif /*FUNCIONES_H*/