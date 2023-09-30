#ifndef TAREAS_H
#define TAREAS_H

void estructurasParaLosLibros_CargaDeDatos(char **&codigo, char **&titulo, int *&cantEnBib, double *&precio);
void estructurasParaLosLibros_Reporte(char **codigo, char **titulo, int *cantEnBib, double *precio);
void usuariosDeLaBiblioteca_CargaDeDatos(int *&carne, char *&tipo, char **&nombre);
void usuariosDeLaBiblioteca_Reporte(int *carne, char *tipo, char **nombre);
void librosYUsuariosInhabilitados_Reporte(char **codigo, char **titulo, int *&cantEnBib, double *precio, int *carne, char *tipo, char **nombre);

#endif /*TAREAS_H*/