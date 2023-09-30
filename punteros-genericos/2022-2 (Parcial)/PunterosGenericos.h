#ifndef PUNTEROSGENERICOS_H
#define PUNTEROSGENERICOS_H

#include <fstream>
using namespace std;

void cargaMedicinas(void *&medicinas);
void cargaConsultas(void *&citas);
void actualizaReservas(void *medicinas, void *citas);

char *leerCadena(ifstream &arch, char del);
void *leerMedicinas(ifstream &arch, int cant);
int leerFecha(ifstream &arch);
int buscarMedicina(void *medicinas, int codMedicina);

#endif /*PUNTEROSGENERICOS_H*/