#ifndef METODOEXACTO_H
#define METODOEXACTO_H

#include <fstream>
using namespace std;

void cargaClientes(int *&cliDni, char **&cliNombre, char *&cliCategoria);
void reporteClientes(int *cliDni, char **cliNombre, char *cliCategoria);
char *leerCadena(ifstream &arch, char del);
void extraerNombreYCategoria(const char *cadena, char *&nombre, char &categoria);

#endif