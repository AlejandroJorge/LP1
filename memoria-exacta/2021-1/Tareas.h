#ifndef TAREAS_H
#define TAREAS_H

void cargarConductores(int *&licencia, char **&conductor);

void reporteConductores(int *licencia, char **conductor);

void cargarInfracciones(int *&infraccion, char *&gravedad, double *&multa);

void reporteInfracciones(int *infraccion, char *gravedad, double *multa);

void reporteDeFaltas(int *licencia, char **conductor, int *infraccion, char *gravedad, double *multa);

#endif /*TAREAS_H*/