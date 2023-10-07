#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "Pregunta2.h"
#include "Pregunta1.h"
#include "AperturaDeArchivos.h"

#define BUFFSIZE 100

void cargaNotas(char ***&cursosCod, int ***&cursosNotaSemVeces, double **&costos, int **alumnos, char ***alumnosNomMod, double *escalas, char ***cursos, double *cursosCred, const char *nomArch)
{
  ifstream arch;
  AperturaDeUnArchivoDeTextosParaLeer(arch, nomArch);

  int cantAlumnos = 0;
  while (alumnos[cantAlumnos])
    cantAlumnos++;
  cursosCod = new char **[cantAlumnos + 1] {};
  cursosNotaSemVeces = new int **[cantAlumnos + 1] {};
  costos = new double *[cantAlumnos + 1] {};

  for (int i = 0; i < cantAlumnos; i++)
  {
    cursosCod[i] = new char *[BUFFSIZE] {};
    cursosNotaSemVeces[i] = new int *[BUFFSIZE] {};
    costos[i] = new double[BUFFSIZE + 1]{};
  }

  int cantidadCursos[cantAlumnos]{};

  int codigoAlmLeido;
  char *codigoCrsLeido;
  int semestreLeido;
  int notaFinalLeida;

  int posAlm, posCrs;
  double precioEscala;

  while (true)
  {
    // 202315643, MEC270, 202202, 13
    arch >> codigoAlmLeido;
    if (arch.eof())
      break;
    arch.get();
    codigoCrsLeido = leerCadena(arch, ',');
    arch >> semestreLeido;
    arch.get();
    arch >> notaFinalLeida;

    posAlm = buscarAlumno(alumnos, codigoAlmLeido);
    if (posAlm == -1)
      continue;

    posCrs = buscarCurso(cursos, codigoCrsLeido);
    if (posCrs == -1)
      continue;

    precioEscala = obtenerPrecioEscala(alumnos[posAlm], escalas);

    agregarCurso(cursosCod[posAlm], cursosNotaSemVeces[posAlm], costos[posAlm], cursos[posCrs], cursosCred[posCrs], precioEscala, notaFinalLeida, semestreLeido, cantidadCursos[posAlm]);
  }

  for (int i = 0; i < cantAlumnos; i++)
    corregirEspacios(cursosCod[i], cursosNotaSemVeces[i], costos[i], cantidadCursos[i]);
}

void pruebaCargaNotas(char ***cursosCod, int ***cursosNotaSemVeces, double **costos, int **alumnos, char ***alumnosNomMod, const char *nomArch)
{
  ofstream arch;
  AperturaDeUnArchivoDeTextosParaEscribir(arch, nomArch);
  arch << fixed << left;
  arch.precision(2);

  arch << "PRUEBA DE CARGA NOTAS" << endl;
  arch << setw(105) << setfill('=') << "" << setfill(' ') << endl;

  int *alumno;
  char **alumnoNomMod;

  for (int i = 0; alumnos[i]; i++)
  {
    alumno = alumnos[i];
    alumnoNomMod = alumnosNomMod[i];

    arch << right << setw(10) << "CODIGO: " << left << setw(15) << alumno[0];
    arch << right << setw(10) << "NOMBRE: " << left << setw(45) << alumnoNomMod[0];
    arch << right << setw(10) << "ESCALA: " << left << setw(15) << alumno[1];
    arch << endl;

    arch << setw(105) << setfill('-') << "" << setfill(' ') << endl;

    if (cursosCod[i] != nullptr)
    {
      imprimirCursos(arch, cursosCod[i], cursosNotaSemVeces[i], costos[i]);
    }
    else
      arch << "NO SE HAN REGISTRADO CURSOS PARA ESTE ALUMNO" << endl;

    arch << setw(105) << setfill('=') << "" << setfill(' ') << endl;
  }
}

void imprimirCursos(ofstream &arch, char **codigos, int **NSVs, double *costos)
{

  arch << setw(15) << "CODIGO";
  arch << setw(15) << "U. NOTA";
  arch << setw(15) << "U. SEMESTRE";
  arch << setw(15) << "VECES";
  arch << setw(15) << "COSTO";
  arch << endl;

  arch << setw(105) << setfill('-') << "" << setfill(' ') << endl;

  int *NSV;
  for (int i = 0; codigos[i]; i++)
  {
    NSV = NSVs[i];

    arch << setw(15) << codigos[i];
    arch << setw(15) << NSV[0];
    arch << setw(15) << NSV[1];
    arch << setw(15) << NSV[2];
    arch << setw(15) << costos[i];
    arch << endl;
  }
}

int buscarAlumno(int **alumnos, int codigo)
{
  int *alumno;
  for (int i = 0; alumnos[i]; i++)
  {
    alumno = alumnos[i];
    if (alumno[0] == codigo)
      return i;
  }

  return -1;
}

int buscarCurso(char ***cursos, char *codigo)
{
  char **curso;
  for (int i = 0; cursos[i]; i++)
  {
    curso = cursos[i];
    if (strcmp(curso[0], codigo) == 0)
      return i;
  }

  return -1;
}

double obtenerPrecioEscala(int *alumno, double *escalas)
{
  return escalas[alumno[1] - 1];
}

void agregarCurso(char **codigosCurso, int **notaSemVeces, double *costos, char **curso, double creditos, double precioEscala, int nota, int semestre, int &cantidad)
{
  int pos = -1;
  for (int i = 0; i < cantidad; i++)
  {
    if (strcmp(codigosCurso[i], curso[0]) == 0)
    {
      pos = i;
      break;
    }
  }
  int *NSVCurso;
  double costoLocal = creditos * precioEscala;
  if (pos == -1)
  {
    codigosCurso[cantidad] = new char[strlen(curso[0]) + 1];
    strcpy(codigosCurso[cantidad], curso[0]);
    NSVCurso = new int[3];

    NSVCurso[0] = nota;
    NSVCurso[1] = semestre;
    NSVCurso[2]++;
    notaSemVeces[cantidad] = NSVCurso;

    costos[cantidad + 1] = costos[cantidad];
    costos[cantidad] = costoLocal;
    costos[cantidad + 1] += costoLocal;

    cantidad++;
  }
  else
  {
    NSVCurso = notaSemVeces[pos];
    NSVCurso[0] = nota;
    NSVCurso[1] = semestre;
    NSVCurso[2]++;

    costos[pos] += costoLocal;
    costos[cantidad] += costoLocal;
  }
}

void corregirEspacios(char **&cursosCod, int **&cursosNotaSemVeces, double *&costos, int cantidad)
{
  char **cursosCodExacto = new char *[cantidad + 1] {};
  int **cursosNotaSemVecesExacto = new int *[cantidad + 1] {};
  double *costosExacto = new double[cantidad + 1]{};

  for (int i = 0; i < cantidad; i++)
  {
    cursosCodExacto[i] = cursosCod[i];
    cursosNotaSemVecesExacto[i] = cursosNotaSemVeces[i];
    costosExacto[i] = costos[i];
  }

  delete cursosCod;
  delete cursosNotaSemVeces;
  delete costos;

  if (cantidad == 0)
  {
    cursosCod = nullptr;
    cursosNotaSemVeces = nullptr;
    costos = nullptr;
  }

  cursosCod = cursosCodExacto;
  cursosNotaSemVeces = cursosNotaSemVecesExacto;
  costos = costosExacto;
}
