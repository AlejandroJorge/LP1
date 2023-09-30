#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../headers/Estructuras.h"
#include "../headers/funcionesFecha.h"

bool operator>>(ifstream &arch, St_Libro &libro)
{
  arch >> libro.codigo >> libro.titulo >> libro.stock >> libro.precio;
  if (arch.eof())
    return false;
  return true;
}

bool operator>>(ifstream &arch, St_Usuario &usuario)
{
  char c;
  arch >> usuario.carne >> c >> usuario.nombre;
  if (arch.eof())
    return false;

  switch (c)
  {
  case 'E':
    strcpy(usuario.tipo, "Estudiante");
    break;
  case 'D':
    strcpy(usuario.tipo, "Docente");
    break;
  case 'A':
    strcpy(usuario.tipo, "Administrativo");
    break;
  default:
    strcpy(usuario.tipo, "Desconocido");
    break;
  }

  return true;
}

void operator+=(St_Usuario &usuario, const St_LibroPrestado &libroPrestado)
{
  usuario.libPrest[usuario.numLibPrest] = libroPrestado;
  usuario.numLibPrest++;
}

void operator+=(St_Libro &libro, const St_UsuarioPrestamo &usuarioPrestamo)
{
  switch (usuarioPrestamo.tipo)
  {
  case 'E':
    libro.estudiantes[libro.cantEst] = usuarioPrestamo;
    libro.cantEst++;
    break;

  case 'D':
    libro.docentes[libro.cantDoc] = usuarioPrestamo;
    libro.cantDoc++;

  case 'A':
    libro.administrativos[libro.cantAdm] = usuarioPrestamo;
    libro.cantAdm++;

  default:
    break;
  }
}

void operator<=(St_Usuario &usuario, int fecha)
{
  int cantidadDeudas = 0;
  for (int i = 0; i < usuario.numLibPrest; i++)
  {
    int difDias = numeroDeDias(usuario.libPrest[i].fechaDeRetiro, fecha);

    int diasPermitidos;
    if (strcmp(usuario.tipo, "Estudiante") == 0)
      diasPermitidos = 7;
    if (strcmp(usuario.tipo, "Docente") == 0)
      diasPermitidos = 15;
    if (strcmp(usuario.tipo, "Administrativo") == 0)
      diasPermitidos = 3;

    if (difDias > diasPermitidos)
    {
      usuario.libPrest[i].deuda = true;
      cantidadDeudas++;
    }
    else
      usuario.libPrest[i].deuda = false;
  }
  if (cantidadDeudas > 0)
    strcpy(usuario.condicion, "Inhabilitado");
  else
    strcpy(usuario.condicion, "Habilitado");
}

void operator<=(St_Libro &libro, int fecha)
{
  for (int i = 0; i < libro.cantDoc; i++)
  {
    int difDias = numeroDeDias(libro.docentes[i].fechaDeRetiro, fecha);
    if (difDias > 15)
      libro.docentes[i].deuda = true;
    else
      libro.docentes[i].deuda = false;
  }
  for (int i = 0; i < libro.cantEst; i++)
  {
    int difDias = numeroDeDias(libro.estudiantes[i].fechaDeRetiro, fecha);
    if (difDias > 7)
      libro.estudiantes[i].deuda = true;
    else
      libro.estudiantes[i].deuda = false;
  }
  for (int i = 0; i < libro.cantAdm; i++)
  {
    int difDias = numeroDeDias(libro.administrativos[i].fechaDeRetiro, fecha);
    if (difDias > 3)
      libro.administrativos[i].deuda = true;
    else
      libro.administrativos[i].deuda = false;
  }
}

void operator<<(ofstream &arch, const St_Usuario &usuario)
{
  arch << usuario.carne << endl;
  arch << usuario.nombre << endl;
  arch << usuario.tipo << endl;
  arch << usuario.condicion << endl;
  for (int i = 0; i < usuario.numLibPrest; i++)
  {
    arch << setw(20) << usuario.libPrest[i].codigoLib;
    arch << setw(20) << usuario.libPrest[i].fechaDeRetiro;
    if (usuario.libPrest[i].deuda)
      arch << "Deuda" << endl;
    else
      arch << "No deuda" << endl;
  }
  arch << endl;
}

void operator<<(ofstream &arch, const St_Libro &libro)
{

  arch << setw(10) << "Titulo"
       << ": " << libro.titulo << endl;
  arch << setw(10) << "Codigo"
       << ": " << setw(40) << libro.codigo;
  arch << setw(10) << "Precio"
       << ": " << libro.precio << endl;
  arch << setw(10) << "Stock"
       << ": " << setw(40) << libro.stock;
  arch << setw(10) << "Prestados"
       << ": " << libro.cantAdm + libro.cantDoc + libro.cantEst << endl;
  arch << "===================================================================================" << endl;

  arch << "Usuarios que lo tienen en su poder:" << endl;
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << "DOCENTES" << endl;
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << setw(10) << "No" << setw(25) << "Carne" << setw(25) << "Fecha de retiro" << setw(15) << "Observacion" << endl;
  for (int i = 0; i < libro.cantDoc; i++)
  {
    int dd, mm, aaaa;
    fTodma(libro.docentes[i].fechaDeRetiro, dd, mm, aaaa);
    arch << i + 1 << ")" << setw(8) << "";
    arch << setw(25) << libro.docentes[i].carne;
    arch << right << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << aaaa << setw(15) << left << setfill(' ') << "";
    if (libro.docentes[i].deuda)
      arch << setw(15) << "Deuda" << endl;
    else
      arch << setw(15) << "No deuda" << endl;
  }
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << "ESTUDIANTES" << endl;
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << setw(10) << "No" << setw(25) << "Carne" << setw(25) << "Fecha de retiro" << setw(15) << "Observacion" << endl;
  for (int i = 0; i < libro.cantEst; i++)
  {
    int dd, mm, aaaa;
    fTodma(libro.estudiantes[i].fechaDeRetiro, dd, mm, aaaa);
    arch << i + 1 << ")" << setw(8) << "";
    arch << setw(25) << libro.estudiantes[i].carne;
    arch << right << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << aaaa << setw(15) << left << setfill(' ') << "";
    if (libro.estudiantes[i].deuda)
      arch << setw(15) << "Deuda" << endl;
    else
      arch << setw(15) << "No deuda" << endl;
  }
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << "ADMINISTRATIVOS" << endl;
  arch << "-----------------------------------------------------------------------------------" << endl;
  arch << setw(10) << "No" << setw(25) << "Carne" << setw(25) << "Fecha de retiro" << setw(15) << "Observacion" << endl;
  for (int i = 0; i < libro.cantAdm; i++)
  {
    int dd, mm, aaaa;
    fTodma(libro.administrativos[i].fechaDeRetiro, dd, mm, aaaa);
    arch << i + 1 << ")" << setw(8) << "";
    arch << setw(25) << libro.administrativos[i].carne;
    arch << right << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << aaaa << setw(15) << left << setfill(' ') << "";
    if (libro.administrativos[i].deuda)
      arch << setw(15) << "Deuda" << endl;
    else
      arch << setw(15) << "No deuda" << endl;
  }

  arch << "===================================================================================" << endl;
}