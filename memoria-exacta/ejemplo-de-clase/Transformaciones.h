#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H

void imprimirLinea(ofstream &arch, char caracter);
char *leerCadena(ifstream &arch);
int buscarDni(int *dnis, int dniLeido);
void agregarCurso(char **cursos, int &cantidad, char *cadena);
void reasignarMemoria(char **&cursos, int cantidad);

#endif /*TRANSFORMACIONES_H*/