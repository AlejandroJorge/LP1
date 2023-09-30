#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <fstream>
using namespace std;

void abrir(ifstream &arch, const char *nombre);
void abrir(ofstream &arch, const char *nombre);

char *leerCadena(ifstream &arch, char del);

void cargarDatos(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda,
                 char **codigo, double *precio, int *&cantEnBib, int *carne, char **nombre, double *&montoPorDeuda, char tipo);

int leerFecha(ifstream &arch);

int buscarCarne(int *carneDeudaBuff, int carneLeido);

char *buscarNombre(int *carne, char **nombre, int carneLeido);

double buscarPrecio(char **codigo, double *precio, char *codigoLeido);

void disminuirStock(char **codigo, int *cantEnBib, char *codigoLeido);

void imprimirReporte(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda, ofstream &arch);

void liberarDatos(int *&carneDeuda, int *&cantDeuda, char **&nombreDeuda, double *&montoDeuda);

void imprimirLinea(ofstream &arch, char c);

void imprimirStockLibros(char **codigo, char **titulo, int *cantEnBib, double *precio, double *montoDeuda);

void actualizarMontoPorDeuda(double *montoDeuda, char **codigo, double *precio, char *codigoLeido);

#endif /*UTILIDADES_H*/