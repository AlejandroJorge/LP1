#ifndef FUNCIONESEXAMEN01PREGUNTA01_H
#define FUNCIONESEXAMEN01PREGUNTA01_H

void CargaProductosPedidos(int **&proInformacion, char **&proDescripcion, int **&pedTodo, const char *nomArch);
void PruebaProductosPedidos(int **proInformacion, char **proDescripcion, int **pedTodo, const char *nomArch);

void ordenarPedidos(int **pedTodo);

void asignarPedidos(int ***cliDniTelPed, int **proInformacion, int **pedTodo);

char *leerCadena(ifstream &arch, char del);
int leerFecha(ifstream &arch);
int *crearPedido(int dni, int fecha, int cantidad, int codigo);
int *crearProInformacion(int codigo, double descuento, double precioUnitario, double stock);
int buscarProducto(int **arrProInformacion, int codigo);
void quickSort(int **pedidos, int izq, int der);
void intercambiar(int *&a, int *&b);
int buscarCliente(int ***arrDniTelPed, int dni);
bool hayStock(int *producto, int *pedido);
void agregarPedido(int *&arrPedidos, int &cantidad, int &capacidad, int *pedido);
void disminuirStock(int *producto, int *pedido);

#endif /*FUNCIONESEXAMEN01PREGUNTA01_H*/