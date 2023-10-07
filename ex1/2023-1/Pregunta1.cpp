#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Pregunta1.h"
#include "AperturaDeArchivos.h"
#define INCREMENTO 5

void cargaCursoEscalas(char ***&cursos, double *&cursosCred, double *escalas, const char *nomCurArch, const char *nomEscArch)
{
  ifstream archC, archE;
  AperturaDeUnArchivoDeTextosParaLeer(archC, nomCurArch);
  AperturaDeUnArchivoDeTextosParaLeer(archE, nomEscArch);

  cursos = nullptr;
  cursosCred = nullptr;

  leerEscalas(escalas, archE);

  char *codigo, *nombre, *nombreProfesor;
  double creditos;
  int codProfesor;

  char **cursoLeido;

  int cantidad = 0, capacidad = 0;

  while (true)
  {
    // INF263,Algoritmia,3.75,35030611,INGA FLORES CESAR ADOLFO
    codigo = leerCadena(archC, ',');

    if (archC.eof())
      break;

    nombre = leerCadena(archC, ',');
    archC >> creditos;
    archC.get();
    archC >> codProfesor;
    archC.get();
    nombreProfesor = leerCadena(archC, '\n');
    archC >> ws;

    cursoLeido = new char *[3];
    cursoLeido[0] = codigo;
    cursoLeido[1] = nombre;
    cursoLeido[2] = nombreProfesor;

    agregarCurso(cursos, cursoLeido, cursosCred, creditos, cantidad, capacidad);
  }
}

void pruebaCargaCursos(char ***cursos, double *cursosCred, const char *nomArch)
{
  ofstream arch;
  AperturaDeUnArchivoDeTextosParaEscribir(arch, nomArch);

  arch << left << fixed;
  arch.precision(2);

  arch << "PRUEBA DE CARGA DE CURSOS" << endl;
  arch << setw(135) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(15) << "CODIGO";
  arch << setw(60) << "NOMBRE";
  arch << setw(45) << "PROFESOR";
  arch << setw(15) << "CREDITOS";
  arch << endl;

  char **curso;
  for (int i = 0; cursos[i]; i++)
  {
    curso = cursos[i];

    arch << setw(15) << curso[0];
    arch << setw(60) << curso[1];
    arch << setw(45) << curso[2];
    arch << setw(15) << cursosCred[i];
    arch << endl;
  }
}

void cargaAlumnos(int **&alumnos, int *&alumnosCod, char ***&alumnosNomMod, const char *nomArch)
{
  ifstream arch;
  AperturaDeUnArchivoDeTextosParaLeer(arch, nomArch);

  int cantidad = 0, capacidad = 0;

  alumnos = nullptr;
  alumnosCod = nullptr;
  alumnosNomMod = nullptr;

  int codigo;
  char *nombre, modalidad;
  int porcentaje;
  int escala;
  char esp;

  int *alumno;
  char **alumnoNomMod;

  while (true)
  {
    // 202123703,GAMARRA TABORI PAUL RONAL, S, 30, G5
    // 202119153,MENDOZA ARIAS HENRY, G4
    // 202318072,RIVERA MONTERO GLORIA OFELIA,V,G3
    arch >> codigo;
    if (arch.eof())
      break;
    arch.get();
    nombre = leerCadena(arch, ',');
    esp = arch.get();
    switch (esp)
    {
    case 'S':
      modalidad = 'S';
      arch.get();
      arch >> porcentaje;
      arch.get();
      arch.get();
      break;
    case 'G':
      modalidad = 'P';
      break;
    case 'V':
      modalidad = 'V';
      arch.get();
      arch.get();
      break;
    }
    arch >> escala;
    arch >> ws;

    if (modalidad == 'S')
    {
      alumno = new int[3];
      alumno[2] = porcentaje;
    }
    else
      alumno = new int[2];

    alumno[0] = codigo;
    alumno[1] = escala;

    alumnoNomMod = new char *[2];
    alumnoNomMod[0] = nombre;
    alumnoNomMod[1] = new char(modalidad);

    agregarAlumno(alumnos, alumno, alumnosCod, codigo, alumnosNomMod, alumnoNomMod, cantidad, capacidad);
  }
}

void pruebaCargaAlumnos(int **alumnos, int *alumnosCod, char ***alumnosNomMod, const char *nomArch)
{
  ofstream arch;
  AperturaDeUnArchivoDeTextosParaEscribir(arch, nomArch);

  arch << fixed << left;
  arch.precision(2);

  arch << "PRUEBA DE CARGA DE ALUMNOS" << endl;
  arch << setw(105) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(15) << "CODIGO";
  arch << setw(45) << "NOMBRE";
  arch << setw(15) << "MODALIDAD";
  arch << setw(15) << "PORCENTAJE";
  arch << setw(15) << "ESCALA";
  arch << endl;

  int *alumno;
  char **alumnoNomMod;

  for (int i = 0; alumnos[i]; i++)
  {
    alumno = alumnos[i];
    alumnoNomMod = alumnosNomMod[i];

    arch << setw(15) << alumno[0];
    arch << setw(45) << alumnoNomMod[0];
    arch << setw(15) << *alumnoNomMod[1];
    if (*alumnoNomMod[1] == 'S')
      arch << setw(15) << alumno[2];
    else
      arch << setw(15) << "No";
    arch << setw(15) << alumno[1];
    arch << endl;
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  if (del == '\n')
    cad[strlen(buff) - 1] = 0;
  return cad;
}

void agregarCurso(char ***&cursos, char **cursoLeido, double *&cursosCred, double creditos, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    char ***cursosAux = new char **[capacidad + INCREMENTO + 1] {};
    double *cursosCredAux = new double[capacidad + INCREMENTO + 1]{};

    if (capacidad > 0)
    {
      for (int i = 0; i < cantidad; i++)
      {
        cursosAux[i] = cursos[i];
        cursosCredAux[i] = cursosCred[i];
      }
      delete cursos;
      delete cursosCred;
    }

    cursos = cursosAux;
    cursosCred = cursosCredAux;
    capacidad += INCREMENTO;
  }

  cursos[cantidad] = cursoLeido;
  cursosCred[cantidad] = creditos;
  cantidad++;
}

void leerEscalas(double *escalas, ifstream &arch)
{
  int escala;
  double coste;
  for (int i = 0; i < 5; i++)
  {
    // G1, 282.30
    arch.get();
    arch >> escala;
    arch.get();
    arch >> coste >> ws;
    escalas[escala - 1] = coste;
  }
}

void agregarAlumno(int **&alumnos, int *alumno, int *&alumnosCod, int codigo, char ***&alumnosNomMod, char **alumnoNomMod, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    int **alumnosAux = new int *[capacidad + INCREMENTO + 1] {};
    int *alumnosCodAux = new int[capacidad + INCREMENTO + 1]{};
    char ***alumnosNomModAux = new char **[capacidad + INCREMENTO + 1] {};

    if (capacidad > 0)
    {
      for (int i = 0; i < cantidad; i++)
      {
        alumnosAux[i] = alumnos[i];
        alumnosCodAux[i] = alumnosCod[i];
        alumnosNomModAux[i] = alumnosNomMod[i];
      }
      delete alumnos;
      delete alumnosCod;
      delete alumnosNomMod;
    }

    alumnos = alumnosAux;
    alumnosCod = alumnosCodAux;
    alumnosNomMod = alumnosNomModAux;
    capacidad += INCREMENTO;
  }

  alumnos[cantidad] = alumno;
  alumnosCod[cantidad] = codigo;
  alumnosNomMod[cantidad] = alumnoNomMod;
  cantidad++;
}