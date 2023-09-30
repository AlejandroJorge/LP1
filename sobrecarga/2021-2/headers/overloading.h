#ifndef OVERLOADING_H
#define OVERLOADING_H

#include <fstream>
using namespace std;
#include "Estructuras.h"

bool operator>>(ifstream &arch, St_Libro &libro);
bool operator>>(ifstream &arch, St_Usuario &usuario);
void operator+=(St_Usuario &usuario, const St_LibroPrestado &libroPrestado);
void operator+=(St_Libro &libro, const St_UsuarioPrestamo &usuarioPrestamo);
void operator<=(St_Usuario &usuario, int fecha);
void operator<=(St_Libro &libro, int fecha);
void operator<<(ofstream &arch, const St_Usuario &usuario);
void operator<<(ofstream &arch, const St_Libro &libro);

#endif // OVERLOADING_H