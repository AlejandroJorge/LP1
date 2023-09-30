#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "../headers/Estructuras.h"
#include "../headers/overloading.h"

int main() {

    ifstream aCursos("Cursos.csv",ios::in);
    ifstream aAlumnos("Alumnos.csv",ios::in);
    ifstream aRegistros("Matricula.csv",ios::in);
    ofstream aReporte1("Reporte1.txt",ios::out);
    
    StCurso cursos[200]{};
    int cCursos = 0;
    StAlumno alumnos[200]{};
    int cAlumnos = 0;

    StRegistroDeMatricula registro;

    while(aCursos >> cursos[cCursos]) cCursos++;
    while(aAlumnos >> alumnos[cAlumnos]) cAlumnos++;

    while(aRegistros >> registro){
        alumnos *= registro;
    }

    // aReporte1 << fixed << left;
    // aReporte1.precision(2);

    // for(int i=0; i< cAlumnos; i++) aReporte1 << alumnos[i];

    return 0;
}
