#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "AperturaDeArchivos.h"
#include "Pregunta1.h"
#include "Pregunta2.h"
#include "Pregunta3.h"
#define BUFFALMSIZE 20

enum AlumnoVeces
{
  AV_CODIGO,
  AV_NUMCURSOS,
  AV_NUMCURSOSAPROBADOS,
  AV_CURSOSAPROBADOSPRIMERA,
  AV_CURSOSAPROBADOSSEGUNDA,
  AV_CURSOSAPROBADOSTERCERA,
  AV_CURSOS,
  AV_CANTCAMPOS
};

enum Curso
{
  C_CODIGO,
  C_CICLO,
  C_NOTA,
  C_CANTCAMPOS
};

void CargaCursos(int *alumnosCod, void *&alumnoVeces, const char *nomArch)
{
  ifstream arch;
  AperturaDeUnArchivoDeTextosParaLeer(arch, nomArch);

  inicializar(alumnosCod, alumnoVeces);
  int cantidad[200]{};

  int codAlm, semestre, nota;
  char *codCrs;

  void **arrAlmVeces = (void **)alumnoVeces;

  void **reg;
  int pos;
  while (true)
  {
    // 202225778,INF246,202301,19
    arch >> codAlm;
    if (arch.eof())
      break;
    arch.get();
    codCrs = leerCadena(arch, ',');
    arch >> semestre;
    arch.get();
    arch >> nota;

    pos = buscarAlumno(alumnosCod, codAlm);
    if (pos == -1)
      continue;

    void **curso = new void *[C_CANTCAMPOS];
    curso[C_CICLO] = new int(semestre);
    curso[C_CODIGO] = codCrs;
    curso[C_NOTA] = new int(nota);

    agregarCurso(arrAlmVeces[pos], curso, cantidad[pos]);
  }
  reducirMemoria(arrAlmVeces, cantidad);
}

int buscarAlumno(int *codigos, int codigo)
{
  for (int i = 0; codigos[i]; i++)
    if (codigos[i] == codigo)
      return i;
  return -1;
}

void agregarCurso(void *almVez, void *curso, int &cantidad)
{
  void **alumno = (void **)almVez;
  void **cursos = (void **)alumno[AV_CURSOS];
  cursos[cantidad] = curso;
  cantidad++;
}

void inicializar(int *alumnosCod, void *&alumnoVeces)
{
  void *buff[300]{};
  int size = 0;
  for (int i = 0; alumnosCod[i]; i++)
  {
    buff[i] = crearAlumnoVez(alumnosCod[i]);
    size++;
  }
  size++;
  void **arrExacto = new void *[size] {};
  for (int i = 0; i < size; i++)
    arrExacto[i] = buff[i];
  alumnoVeces = arrExacto;
}

void *crearAlumnoVez(int codigo)
{
  void **reg = new void *[AV_CANTCAMPOS];
  reg[AV_CODIGO] = new int(codigo);
  reg[AV_CURSOS] = new void *[BUFFALMSIZE] {};
  reg[AV_CURSOSAPROBADOSPRIMERA] = new int(0);
  reg[AV_CURSOSAPROBADOSSEGUNDA] = new int(0);
  reg[AV_CURSOSAPROBADOSTERCERA] = new int(0);
  reg[AV_NUMCURSOS] = new int(0);
  reg[AV_NUMCURSOSAPROBADOS] = new int(0);
  return reg;
}

void reducirMemoria(void **arrAlm, int *cantidad)
{
  void **alm, **cursos, **cursosAux;
  for (int i = 0; arrAlm[i]; i++)
  {
    if (cantidad[i] == 0)
      continue;
    alm = (void **)arrAlm[i];
    cursos = (void **)alm[AV_CURSOS];
    cursosAux = new void *[cantidad[i] + 1] {};
    for (int j = 0; j < cantidad[i]; j++)
      cursosAux[j] = cursos[j];
    delete cursos;
    alm[AV_CURSOS] = cursosAux;
  }
}

void ActualizaVeces(void *alumnoVeces)
{
  void **arrAlmVez = (void **)alumnoVeces;
  void **almVez, **cursos, **curso;
  int total;
  int primas;
  int bikas;
  int trikas;

  int ocurrenciasPrevias;
  for (int i = 0; arrAlmVez[i]; i++)
  {
    almVez = (void **)arrAlmVez[i];
    cursos = (void **)almVez[AV_CURSOS];

    total = 0;
    primas = 0;
    bikas = 0;
    trikas = 0;

    if (cursos == nullptr)
      continue;
    for (int j = 0; cursos[j]; j++)
    {
      curso = (void **)cursos[j];
      ocurrenciasPrevias = calcOcurrenciasPrevias(cursos, curso);
      switch (ocurrenciasPrevias)
      {
      case 0:
        total++;
        if (*(int *)curso[C_NOTA] >= 11)
          primas++;
        break;
      case 1:
        if (*(int *)curso[C_NOTA] >= 11)
          bikas++;
        delete curso;
        shift(cursos, j);
        break;
      case 2:
        if (*(int *)curso[C_NOTA] >= 11)
          trikas++;
        delete curso;
        shift(cursos, j);
        break;
      }
    }
    *(int *)almVez[AV_NUMCURSOS] = total;
    *(int *)almVez[AV_CURSOSAPROBADOSPRIMERA] = primas;
    *(int *)almVez[AV_CURSOSAPROBADOSSEGUNDA] = bikas;
    *(int *)almVez[AV_CURSOSAPROBADOSTERCERA] = trikas;
    *(int *)almVez[AV_NUMCURSOSAPROBADOS] = total - (primas + bikas + trikas);
  }

  void **cursosAux = new void *[total + 1] {};
  for (int i = 0; i < total; i++)
    cursosAux[i] = cursos[i];
  delete cursos;
  almVez[AV_CURSOS] = cursosAux;
}

int calcOcurrenciasPrevias(void *cursos, void *curso)
{
  void **arr = (void **)cursos;
  void **cursoRef = (void **)curso;
  void **cursoLocal;

  int cantidad = 0;

  for (int i = 0; arr[i] != curso; i++)
  {
    cursoLocal = (void **)arr[i];
    if (*(int *)cursoLocal[C_CODIGO] == *(int *)cursoRef[C_CODIGO])
      cantidad++;
  }

  return cantidad;
}

void shift(void *cursos, int idx)
{
  void **arr = (void **)cursos;
  for (int i = idx; arr[i]; i++)
    arr[i] = arr[i + 1];
}

void ImprimeAlumno(void *alumnoVeces)
{
  ofstream arch("ReportePregunta3.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir ReportePregunta3.txt" << endl;
    exit(1);
  }

  arch << left << fixed;
  arch.precision(2);

  arch << "REPORTE DE ALUMNOS" << endl;
  arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(20) << "CODIGO";
  arch << setw(20) << "TOTAL CURSOS";
  arch << setw(20) << "APROBADOS";
  arch << setw(20) << "POR PRIMERA";
  arch << setw(20) << "POR SEGUNDA";
  arch << setw(20) << "POR TERCERA";
  arch << endl;

  arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

  void **arrAlmVeces = (void **)alumnoVeces;
  void **almVez, **arrCursos, **curso;
  for (int i = 0; arrAlmVeces[i]; i++)
  {
    almVez = (void **)arrAlmVeces[i];

    arch << setw(20) << *(int *)almVez[AV_CODIGO];
    arch << setw(20) << *(int *)almVez[AV_NUMCURSOS];
    arch << setw(20) << *(int *)almVez[AV_NUMCURSOSAPROBADOS];
    arch << setw(20) << *(int *)almVez[AV_CURSOSAPROBADOSPRIMERA];
    arch << setw(20) << *(int *)almVez[AV_CURSOSAPROBADOSSEGUNDA];
    arch << setw(20) << *(int *)almVez[AV_CURSOSAPROBADOSTERCERA];
    arch << endl;

    arrCursos = (void **)almVez[AV_CURSOS];

    for (int j = 0; arrCursos[j]; j++)
    {
      curso = (void **)arrCursos[j];
      arch << (char *)curso[C_CODIGO] << " ";
    }
    arch << endl;
  }
}