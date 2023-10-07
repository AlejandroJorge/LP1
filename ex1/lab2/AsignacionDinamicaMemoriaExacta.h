#ifndef ASIGNACIONDINAMICAMEMORIAEXACTA_H
#define ASIGNACIONDINAMICAMEMORIAEXACTA_H

#include <fstream>
using namespace std;

void lecturaDeProductos(const char *nomArch, char ***&productos, int *&stock, double *&precios);

void pruebaDeLecturaDeProductos(const char *nomArch, char ***productos, int *stock, double *precios);

void lecturaDePedidos(const char *nomArch, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos);

void pruebaDeLecturaDePedidos(const char *nomArch, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);

void reporteDeEnvioDePedidos(const char *nomArch, char ***productos, int *stock, double *precios,
                             int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);

char *leerCad(ifstream &arch, char del = '\n');
void ajustarMemoria(char **&arrCodigos, int **&arrDniCant, int cantidad);
int leerFecha(ifstream &arch);
int buscarFecha(int *arrFechas, int fecha);
void imprimirPedidos(ofstream &arch, char ***productos, int *stock, double *precios, char **codigos, int **dniCants, int &subtotalIngresado, int &subtotalPerdido);
int buscarProducto(char ***productos, char *producto);

#endif /*ASIGNACIONDINAMICAMEMORIAEXACTA_H*/