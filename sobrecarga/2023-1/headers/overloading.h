#ifndef OVERLOADING_H
#define OVERLOADING_H

#include <fstream>
using namespace std;
#include "Estructuras.h"

bool operator>>(ifstream& arch, StCurso &curso);
bool operator>>(ifstream& arch, StAlumno &alumno);
bool operator>>(ifstream& arch, StRegistroDeMatricula &registro);

void operator+=(StCurso *cursos,const StCurso &curso);
void operator+=(StAlumno *alumnos,const StAlumno &alumno);
void operator*=(StCurso &curso, const StRegistroDeMatricula &registro);
void operator*=(StAlumno *alumnos, const StRegistroDeMatricula &registro);

void operator<<(ofstream &arch, const StCurso &curso);
void operator<<(ofstream &arch, const StAlumno &alumno);

#endif /*OVERLOADING_H*/