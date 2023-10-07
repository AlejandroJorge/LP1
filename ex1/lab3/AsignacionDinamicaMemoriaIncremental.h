#ifndef ASIGNACIONDINAMICAMEMORIAINCREMENTAL_H
#define ASIGNACIONDINAMICAMEMORIAINCREMENTAL_H

#include <fstream>
using namespace std;

void lecturaProductos(const char *nomArch, char ***&productos, int *&stock, double *&precios);
void pruebaLecturaProductos(const char *nomArch, char ***productos, int *stock, double *precios);

void lecturaPedidos(const char *nomArch, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos);
void pruebaLecturaPedidos(const char *nomArch, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);

void reporteEnvioPedidos(const char *nomArch, char ***productos, int *stock, double *precios, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);

char *leerCadena(ifstream &arch, char del);
int leerFecha(ifstream &arch);
void agregarProducto(char ***&productos, char **producto, double *&precios,
                     double prec, int *&stock, int st, int &cantidad, int &capacidad);
int buscarFecha(int *arrFechas, int fecha);
void agregarFecha(int *&fechaPedidos, int fecha, char ***&codigoPedidos, int ***&dniCantPedidos, int &cantidadFechas, int &capacidadFechas);
void agregarPedido(char **&codigos, char *codigo, int **&dniCants, int *dniCant, int &cantidad, int &capacidad);
void imprimirPedidos(ofstream &arch, char ***productos, int *stock, double *precios, char **codigosPed, int **dniCantPed, double &subtotalIngresos, double &subtotalPerdidas);
int buscarProducto(char ***productos, char *codigo);

#endif /*ASIGNACIONDINAMICAMEMORIAINCREMENTAL_H*/