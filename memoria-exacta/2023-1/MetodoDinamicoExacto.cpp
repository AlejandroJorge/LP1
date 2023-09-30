#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "MetodoDinamicoExacto.h"
#define BUFFSIZE 300

void lecturaAlumnos(const char *nomArch, int *&almCodigo, char **&almNombre, char *&almModalidad, int *&almPorcentaje, int *&almEscala)
{
    ifstream arch(nomArch, ios::in);
    if (!arch.is_open())
    {
        cout << "No se pudo abrir " << nomArch << endl;
        exit(1);
    }
    // ifstream archEsc("escalas.csv", ios::in);
    // if (!archEsc.is_open()) {
    //     cout << "No se pudo abrir escalas.csv" << endl;
    //     exit(1);
    // }

    int buffCodigo[BUFFSIZE]{};
    char *buffNombre[BUFFSIZE]{};
    char buffModalidad[BUFFSIZE]{};
    int buffPorcentaje[BUFFSIZE]{};
    int buffEscala[BUFFSIZE]{};
    int size = 0;

    int cod;
    char *cad;
    char mod;
    int porc;
    int esc;

    while (true)
    {
        // 5802,MINAYA AMEZQUITA RHONY JAIME,5
        // 2050,LOYOLA HIJAR NICOLAS OSCAR,V,4
        // 7660, CHANG ARGUEDAS HENRY ANTONIO, S, 25, 4
        arch >> cod;
        if (arch.eof())
            break;
        arch.get();
        cad = leerCadena(arch, ',');
        mod = leerModalidad(arch);
        if (mod == 'S')
        {
            arch >> porc;
            arch.get();
        }
        arch >> esc;

        buffCodigo[size] = cod;
        buffEscala[size] = esc;
        buffModalidad[size] = mod;
        buffNombre[size] = cad;
        if (mod == 'S')
            buffPorcentaje[size] = porc;

        size++;
    }
    size++;

    almCodigo = new int[size];
    almEscala = new int[size];
    almModalidad = new char[size];
    almNombre = new char *[size];
    almPorcentaje = new int[size];

    for (int i = 0; i < size; i++)
    {
        almCodigo[i] = buffCodigo[i];
        almEscala[i] = buffEscala[i];
        almModalidad[i] = buffModalidad[i];
        almNombre[i] = buffNombre[i];
        almPorcentaje[i] = buffPorcentaje[i];
    }
}

char *leerCadena(ifstream &arch, char del)
{
    char buff[BUFFSIZE]{};
    arch.getline(buff, BUFFSIZE, del);
    char *cad = new char[strlen(buff) + 1];
    strcpy(cad, buff);
    if (del == '\n')
        cad[strlen(buff) - 1]; // Linux fix
    return cad;
}

char leerModalidad(ifstream &arch)
{
    char c = arch.peek();
    if (c != 'V' and c != 'S')
        return 'P';

    arch.get();
    arch.get();
    return c;
}

void pruebaLecturaAlumnos(const char *nomArch, int *almCodigo, char **almNombre, char *almModalidad, int *almPorcentaje, int *almEscala)
{
    ofstream arch(nomArch, ios::out);
    if (!arch.is_open())
    {
        cout << "No se pudo abrir " << nomArch << endl;
        exit(1);
    }

    arch << fixed << left;
    arch.precision(2);

    arch << setw(15) << "CODIGO";
    arch << setw(40) << "NOMBRE";
    arch << setw(15) << "MODALIDAD";
    arch << setw(15) << "PORCENTAJE";
    arch << setw(15) << "ESCALA";
    arch << endl;

    for (int i = 0; almCodigo[i]; i++)
    {
        arch << setw(15) << almCodigo[i];
        arch << setw(40) << almNombre[i];
        arch << setw(15) << almModalidad[i];
        arch << setw(15) << almPorcentaje[i];
        arch << setw(15) << almEscala[i];
        arch << endl;
    }
}
// void lecturaCursos(const char* nomArch, int* almCodigo, int* almEscala, char**& crsNombre, double*& crsCredito, int**& crsAlumnos) {
//     ifstream arch(nomArch, ios::in);
//     if (!arch.is_open())
//     {
//         cout << "No se pudo abrir " << nomArch << endl;
//         exit(1);
//     }

//     char* buffNombre[BUFFSIZE]{};
//     double buffCredito[BUFFSIZE]{};
//     int* buffAlumnos[BUFFSIZE]{};
//     int buffCantAlm[BUFFSIZE]{};
//     int size = 0;

//     int cod;
//     char* cad;
//     double cred;
//     int posCurso;
//     while (true) {
//         // 4628, Lenguaje de Programacion 2, 5
//         arch >> cod;
//         if (arch.eof()) break;
//         arch.get();
//         cad = leerCadena(arch, ',');
//         arch >> cred;

//         posCurso = buscarCurso(cad, buffNombre);
//         if (posCurso == -1) {
//             //No encontrado
//             buffNombre[size] = cad;
//             buffCredito[size] = cred;
//             buffAlumnos[size] = new int[BUFFSIZE] {};
//             buffCantAlm[size] = 0;
//             colocarAlumno(buffAlumnos[size], buffCantAlm[size], cod);
//             size++;
//         }
//         else
//             //Encontrado
//             colocarAlumno(buffAlumnos[posCurso], buffCantAlm[posCurso], cod);
//     }
//     size++;

//     for (int i = 0;buffNombre[i];i++)
//         asignarEspaciosExactos(buffAlumnos[i]);

//     crsNombre = new char* [size];
//     crsAlumnos = new int* [size];
//     crsCredito = new double[size];

//     for (int i = 0; buffNombre[i];i++) {
//         crsNombre[i] = buffNombre[i];
//         crsCredito[i] = buffCredito[i];
//         crsAlumnos[i] = buffAlumnos[i];
//     }
// }

void lecturaCursos(const char *nomarch, int *alumno_Codigo, int *alumno_Escala,
                   char **&curso_Nombre, double *&curso_Credito, int **&curso_Alumnos)
{

    ifstream arch(nomarch, ios::in);
    if (!arch.is_open())
    {
        cout << "error al abrir archivo" << endl;
        exit(1);
    }
    int *buffCursoAlumnos[100]{};
    int numdat = 0, cod, nAlu[100]{};
    char *buffCursoNombre[100]{}, *cad;
    double buffCursoCred[100]{}, cred;
    int pos;

    while (1)
    {
        arch >> cod;
        if (arch.eof())
            break;
        arch.get();
        cad = leerCadena(arch, ',');
        arch >> cred;
        //            cout<<cad<<" "<<cred<<endl;
        pos = buscarCurso(cad, buffCursoNombre);
        cout << pos << endl;
        if (pos == -1)
        { // curso nuevo, separar memoia
            buffCursoNombre[numdat] = cad;
            buffCursoCred[numdat] = cred;
            buffCursoAlumnos[numdat] = new int[100]{};
            nAlu[numdat] = 0;
            colocarAlumno(buffCursoAlumnos[numdat], nAlu[numdat], cod);
            numdat++;
        }
        else
        { // ya existe el curso
            colocarAlumno(buffCursoAlumnos[pos], nAlu[pos], cod);
        }
    }
    numdat++;

    for (int i = 0; i < numdat; i++)
        espacioExacto(buffCursoAlumnos[i], nAlu[i]);

    curso_Alumnos = new int *[numdat] {};
    curso_Nombre = new char *[numdat] {};
    curso_Credito = new double[numdat]{};
    for (int i = 0; i < numdat; i++)
    {
        curso_Alumnos[i] = buffCursoAlumnos[i];
        curso_Credito[i] = buffCursoCred[i];
        curso_Nombre[i] = buffCursoNombre[i];
    }
}

int buscarCurso(const char *buscado, char **cursos)
{
    for (int i = 0; cursos[i]; i++)
        if (strcmp(buscado, cursos[i]) == 0)
            return i;
    return -1;
}

void colocarAlumno(int *alumnos, int &cantidad, int codigo)
{
    alumnos[cantidad] = codigo;
    cantidad++;
}

void asignarEspaciosExactos(int *&arreglo)
{
    int len = 0;
    int *aux;
    while (arreglo[len])
        len++;
    if (len == 0)
    {
        aux = nullptr;
    }
    else
    {
        aux = new int[len + 1];
        for (int i = 0; i < len + 1; i++)
            aux[i] = arreglo[i];
    }
    delete arreglo;
    arreglo = aux;
}

void espacioExacto(int *&arr, int nAlu)
{
    int *espacioFinal;
    if (nAlu != 0)
    {
        espacioFinal = new int[nAlu + 1];
        for (int i = 0; i < nAlu; i++)
            espacioFinal[i] = arr[i];
        espacioFinal[nAlu] = 0; // fin de arreglo
    }
    else
    {

        espacioFinal = nullptr;
    }
    delete arr;
    arr = espacioFinal;
}

void pruebaLecturaCursos(const char *nomArch, char **crsNombre, double *crsCredito, int **crsAlumnos)
{
    ofstream arch(nomArch, ios::out);
    if (!arch.is_open())
    {
        cout << "No se pudo abrir " << nomArch << endl;
        exit(1);
    }

    arch << fixed << left;
    arch.precision(2);

    arch << setw(60) << "NOMBRE";
    arch << setw(15) << "CREDITO";
    arch << setw(50) << "ALUMNOS";
    arch << endl;

    for (int i = 0; crsNombre[i]; i++)
    {
        arch << setw(60) << crsNombre[i];
        arch << setw(15) << crsCredito[i];
        for (int j = 0; crsAlumnos[i][j]; j++)
            arch << crsAlumnos[i][j] << " ";
        arch << endl;
    }
}
void reporteDeRecaudacionPorModalidad(const char *nomArch, int *almCodigo, char *almModalidad, int *almPorcentaje, char **almNombre, char **crsNombre, double *crsCredito, int **crsAlumnos)
{
    ofstream arch(nomArch, ios::out);
    if (!arch.is_open())
    {
        cout << "No se pudo abrir " << nomArch << endl;
        exit(1);
    }
    arch << fixed << left;
    arch.precision(2);
}