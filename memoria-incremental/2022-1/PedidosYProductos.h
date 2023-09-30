#ifndef PEDIDOSYPRODUCTOS_H
#define PEDIDOSYPRODUCTOS_H

#include <fstream>
using namespace std;

void CargaDePedidosYProductos(int **cliDniTelefono, char ***&proCodigoDescripcion, double **&proPrecioDescuento,
                              char ***&pedCodigo, int ***&pedFechaCantidad, const char *nomArch);

int leerFecha(ifstream &arch);

char *leerCadena(ifstream &arch, char del);

int buscarProd(char ***proCodigoDescripcion, char *codigo);

int buscarCli(int **cliDniTelefono, int dni);

void agregarProducto(char ***&proCodigoDescripcion, double **&proPrecioDescuento,
                     char **codigoDescripcion, double *precioDescuento, int &cantidad, int &capacidad);

void ReporteDePedidosYProductos(int **cliDniTelefono, char ***proCodigoDescripcion, double **proPrecioDescuento,
                                char ***pedCodigo, int ***pedFechaCantidad, const char *nomArch);

void agregarPedido(char **&pedCodigo, int **&pedFechaCantidad, char *codigo, int *fechaCantidad,
                   int &cantidad, int &capacidad);

void imprimirPedidos(ofstream &arch, char **pedCodigo, int **pedFechaCantidad);

void ReporteRelacionDePedidos(int **cliDniTelefono, char ***cliNombreCategoria, char ***proCodigoDescripcion,
                              double **proPrecioDescuento, char ***pedCodigo, int ***pedFechaCantidad, const char *nomArch);

void imprimirLineaReporte(ofstream &arch, int num, char *pedCodigo, int *pedFechaCantidad,
                          char ***proCodigoDescripcion, double **proPrecioDescuento);

#endif /*PEDIDOSYPRODUCTOS_H*/