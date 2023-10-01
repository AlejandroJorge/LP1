/*
 * Proyecto: EX01_Preg01_2022_1
 * Archivo:  ClientesPreg1.h
 * Autor:    J. Miguel Guanira E.
 *
 * Created on 15 de mayo de 2022, 10:34 AM
 */

#ifndef CLIENTESPREG1_H
#define CLIENTESPREG1_H

#include <fstream>
using namespace std;

void CargaDeClientes(int ***&, char ***&, const char *);
void PruebaDeClientes(int ***, char ***, const char *);

char *leerCad(ifstream &arch, char del);
char **crearNombreCategoria(char *&cadena);
int **crearDniTelPed(int dni, int telefono);
void imprimirCabeceraCliente(ofstream &arch, int **dniTelPed, char **NombreCategoria);
void imprimirPedidos(ofstream &arch, int *pedidos);

#endif /* CLIENTESPREG1_H */
