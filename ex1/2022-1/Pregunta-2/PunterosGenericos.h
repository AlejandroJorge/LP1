#ifndef PUNTEROSGENERICOS_H
#define PUNTEROSGENERICOS_H

#include <fstream>
using namespace std;

void cargaproductos(void *&productos);
void cargapedidos(void *&pedidos);
void procesacliente(void *productos, void *pedidos, void *&clientes);

char *leerCadena(ifstream &arch, char del);
int leerFecha(ifstream &arch);
void *extraerPedidos(void *productos, void *pedidos, int dni);
int buscarProducto(void **arrProductos, int codigoProducto);

#endif /*PUNTEROSGENERICOS_H*/