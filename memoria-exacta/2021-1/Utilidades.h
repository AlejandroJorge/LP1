#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <fstream>
using namespace std;

void abrirArchivo(ifstream &arch, const char *nombreArch);
void abrirArchivo(ofstream &arch, const char *nombreArch);

char *leerCadena(ifstream &arch, char del);
char leerGravedad(ifstream &arch);

void leerDatos(int *&licenciaRep, char **&placa, int *&cantidad, double *&monto,
               int *infraccion, char *gravedad, double *multa, char tipo);

void imprimirReporte(ofstream &arch, int *licenciaRep, char **placa, int *cantidad, double *monto);
void liberarMemoria(int *&licenciaRep, char **&placa, int *&cantidad, double *&monto);
void imprimirLinea(ofstream &arch, char c);

#endif /*UTILIDADES_H*/