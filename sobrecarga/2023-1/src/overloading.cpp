#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../headers/Estructuras.h"

/*
INF263,Algoritmia,3.75,35030611,INGA_FLORES_CESAR_ADOLFO
MEC270,Procesos_De_Manufactura,4,83265244,PAIRAZAMAN_ALAMO_MOISES_MIGUEL
MEC289,Turbomaquinas_Y_Maquinas_De_Desplazamiento_Positivo,4.25,49516360,DELGADO_GONZALES_GUILLERMO_ALFONSO
MAT241,Metodos_Numericos_En_Ingenieria,3,17750908,HERNANDEZ_BARRIOS_EMILIO_
MEC206,Termodinamica_1,4.5,66152145,SALAS_AGUERO_DANIEL_
INF246,Bases_De_Datos,3.75,65071478,MEJIA_DIAZ_BLANCA_MILAGROS
FIS220,Tecnicas_Computacionales_En_Fisica,4.5,37500242,VASQUEZ_PAZ_ALEX_MARTIN
*/

bool operator>>(ifstream& arch, StCurso &curso){
  arch.getline(curso.codigoDelCurso,7,',');
  arch.getline(curso.nombreDelCurso,60,',');
  arch >> curso.creditos;
  arch.get();
  arch >> curso.codigoDelProfesor;
  arch.get();
  arch.getline(curso.nombreDelProfesor,60);
  curso.ingresos = 0;
  curso.numeroDeAlumnos = 0;
  
  return !arch.eof();
}

/*
20211,1260,GORDILLO/CASTRO/RONAL,G2
20211,1397,ZEVALLOS/PRADO/RICARDO,S,50,G2
20211,2598,MORI/ZAVALETA/LUZ-LOURDES,S,20,G1
20211,2887,CABRERA/AGUERO/JESSICA,S,50,G2
20211,3223,DIAZ/SEDANO/YVONNE,S,30,G4
20211,3758,SOMA/INGA/DIALY,G1
20211,4285,CHAVARRI/ALDAVE/FERNANDO-MARTIN,S,25,G2
20211,4739,VELASQUEZ/CANO/FERNANDO,S,50,G4
20211,5400,SANTISTEBAN/JUGO/NESTOR,S,30,G1
20211,5802,MINAYA/AMEZQUITA/RHONY-JAIME,G5
20211,6038,SAONA/ARIAS/ALBERTO,S,25,G4
20211,6963,CORTEZ/LEIVA/SURAMI-SILVIA,S,30,G4
*/
bool operator>>(ifstream& arch, StAlumno &alumno){
  arch >> alumno.semestre;
  arch.get();
  arch >> alumno.codigo;
  arch.get();
  arch.getline(alumno.nombre,50,',');
  char c = arch.get();
  switch (c)
  {
  case 'G':
    strcpy(alumno.modalidad,"PRESENCIAL");
    arch >> alumno.escala;
    break;
  case 'V':
    strcpy(alumno.modalidad,"VIRTUAL");
    arch.get();
    arch.get();
    arch >> alumno.escala;
    break;
  case 'S':
    strcpy(alumno.modalidad,"SEMIPRESENCIAL");
    arch.get();
    arch >> alumno.porcentaje;
    arch.get();
    arch.get();
    arch >> alumno.escala;
    break;
  }

  alumno.costoTotal = 0;
  alumno.numeroDeCursos = 0;

  return !arch.eof();
}

/*
INF263,20231,8320
MEC289,20231,2000
INF263,20212,5400
MEC289,20221,4204
MEC270,20211,1397
MEC206,20221,5494
MEC270,20212,9719
INF246,20231,3754
MEC206,20211,5802
MEC206,20222,3508
FIS220,20212,5775
INF246,20221,4204
*/
bool operator>>(ifstream& arch, StRegistroDeMatricula &registro){
  arch.getline(registro.codigoDelCurso,7,',');
  arch >> registro.semestreDelAlumno;
  arch.get();
  arch >> registro.codigodelAlumno >> ws;
  return !arch.eof();
}

void operator+=(StCurso *cursos, const StCurso &curso){
  int idx;
  for(idx=0; strcmp(cursos[idx].codigoDelCurso,"XXXXXX");idx++);
  cursos[idx] = curso;
  strcpy(cursos[idx+1].codigoDelCurso,"XXXXXX");
}

void operator+=(StAlumno *alumnos, const StAlumno &alumno){
  int idx;
  for(idx=0; alumnos[idx].semestre;idx++);
  alumnos[idx] = alumno;
  alumnos[idx+1].semestre = 0;
}

void operator*=(StCurso &curso, const StRegistroDeMatricula &registro){
  curso.alumnos[curso.numeroDeAlumnos] = registro.codigodelAlumno;
  curso.numeroDeAlumnos++;
}

void operator*=(StAlumno *alumnos, const StRegistroDeMatricula &registro){
  for(int i=0; alumnos[i].codigo; i++){
    if(alumnos[i].codigo==registro.codigodelAlumno){
      cout << "Encontrado un registro para " << alumnos[i].codigo << endl;
      alumnos[i].cursos[alumnos[i].numeroDeCursos] = new char[7];
      cout << alumnos[i].cursos[alumnos[i].numeroDeCursos] << endl;
      cout << registro.codigoDelCurso << endl;
      // strcpy(alumnos[i].cursos[alumnos[i].numeroDeCursos],registro.codigoDelCurso);
    }
  }
}

void operator<<(ofstream &arch, const StCurso &curso){
  arch << setw(4) << "";
  arch << setw(15) << "CODIGO";
  arch << setw(50) << "NOMBRE";
  arch << setw(15) << "CREDITOS" << endl; 

  arch << setw(4) << "";
  arch << setw(15) << curso.codigoDelCurso;
  arch << setw(50) << curso.nombreDelCurso;
  arch << setw(15) << curso.creditos << endl;; 

  
  arch << setw(4) << "";
  arch << setw(15) << "PROFESOR: " << curso.nombreDelProfesor << " [" << curso.codigoDelProfesor << "]" << endl;

  arch << setw(4) << "";
  arch << "Alumnos matriculados:" << endl;

  arch << setw(4) << "";
  arch << setw(15) << "Semestre";
  arch << setw(20) << "Matriculados" << endl;

  //Bucle

  arch << setw(4) << "";
  arch << "Numero de alumnos: " << curso.numeroDeAlumnos;

  // Total ingresado

  arch << endl << endl;
}

void operator<<(ofstream &arch, const StAlumno &alumno);
