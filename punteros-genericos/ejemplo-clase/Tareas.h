#ifndef TAREAS_H
#define TAREAS_H

#include <fstream>
using namespace std;

void cargarAlumnos(void *&alumnos, const char *nomArch);
void reporteAlumnos(void *alumnos, const char *nomArch);

void *leerRegistro(ifstream &arch);
char *leerCadena(ifstream &arch, char del);
void agregarRegistro(void **&alumnos, void *alumno, int &cantidad, int &capacidad);
void imprimirAlumno(ofstream &arch, void *al);

#endif /*TAREAS_H*/