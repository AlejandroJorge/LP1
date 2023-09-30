#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;
#include "Estructuras.h"

bool operator>>(ifstream &arch, StMedico &medico);
bool operator>>(ifstream &arch, StPaciente &paciente);
int operator>>(ifstream &arch, StCita &cita);

bool operator<=(StCita &cita, StMedico *medicos);

void operator+=(StPaciente &paciente, const StCita &cita);

void operator++(StPaciente &paciente);

void operator<<(ofstream &arch, const StPaciente &paciente);

#endif /*FUNCIONES_H*/