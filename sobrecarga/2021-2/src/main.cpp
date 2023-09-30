#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "../headers/Estructuras.h"
#include "../headers/overloading.h"

int main()
{
    // Apertura de archivos
    ifstream aUsuarios("Usuarios.txt", ios::in);
    if (!aUsuarios)
    {
        cout << "No se pudo abrir el archivo usuarios.txt" << endl;
        return 1;
    }
    ifstream aLibros("Libros.txt", ios::in);
    if (!aLibros)
    {
        cout << "No se pudo abrir el archivo libros.txt" << endl;
        return 1;
    }
    ifstream aPrestamos("RegistroDePrestamos.txt", ios::in);
    if (!aPrestamos)
    {
        cout << "No se pudo abrir el archivo registrodeprestamos.txt" << endl;
        return 1;
    }
    ofstream aReporte("Reporte.txt", ios::out);
    if (!aReporte)
    {
        cout << "No se pudo abrir el archivo reporte.txt" << endl;
        return 1;
    }

    // Lectura de datos

    St_Usuario usuarios[100];
    int cUsuarios = 0;
    St_Libro libros[100];
    int cLibros = 0;

    while (aUsuarios >> usuarios[cUsuarios])
        cUsuarios++;

    while (aLibros >> libros[cLibros])
        cLibros++;

    while (true)
    {
        int carne;
        char codigoLib[10], tipo;
        int dd, mm, aaaa;
        char dummy;
        aPrestamos >> carne >> tipo >> codigoLib >> dd >> dummy >> mm >> dummy >> aaaa;
        if (aPrestamos.eof())
            break;

        int fecha = aaaa * 10000 + mm * 100 + dd;

        St_LibroPrestado libroPrestado;
        strcpy(libroPrestado.codigoLib, codigoLib);
        libroPrestado.fechaDeRetiro = fecha;

        St_UsuarioPrestamo usuarioPrestamo;
        usuarioPrestamo.carne = carne;
        usuarioPrestamo.fechaDeRetiro = fecha;
        usuarioPrestamo.tipo = tipo;

        for (int i = 0; i < cUsuarios; i++)
        {
            if (usuarios[i].carne == carne)
            {
                usuarios[i] += libroPrestado;
                break;
            }
        }
        for (int i = 0; i < cLibros; i++)
        {
            if (strcmp(libros[i].codigo, codigoLib) == 0)
            {
                libros[i] += usuarioPrestamo;
                break;
            }
        }
    }

    // Insertar una fecha para comparar
    int dd, mm, aaaa;
    char c;
    cout << "Inserte una fecha en formato dd/mm/aaaa (21/9/2021): ";
    cin >> dd >> c >> mm >> c >> aaaa;
    int fecha = aaaa * 10000 + mm * 100 + dd;

    // Procesamiento de datos

    for (int i = 0; i < cUsuarios; i++)
        usuarios[i] <= fecha;

    for (int i = 0; i < cLibros; i++)
        libros[i] <= fecha;

    // Impresion de datos

    aReporte << fixed;
    aReporte.precision(2);
    aReporte << left;

    for (int i = 0; i < cLibros; i++)
        aReporte
            << libros[i];
}
