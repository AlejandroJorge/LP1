#ifndef TAREAS_H
#define TAREAS_H

#include <fstream>
using namespace std;

void CargarCursos(const char *nomArch, char ***&cursoDatos,
                  int *&cursoCredito, char ****&cursoAlumnos,
                  double **&cursoInformacionEconomica);

char *leerCadena(ifstream &arch, char del);

#endif /*TAREAS_H*/