#ifndef TAREAS_H
#define TAREAS_H

void cargarAlumnos(int *&dnis, char **&nombres);
void cargarCursos(int *dnis, char ***&cursos);
void imprimirReporte(int *dnis, char **nombres, char ***cursos);

#endif /*TAREAS_H*/