#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "Estructuras.h"

typedef struct
{
  char codigoLib[10];
  int fechaDeRetiro; // aaaammdd
  bool deuda;
} St_LibroPrestado;

typedef struct
{
  int carne;
  char tipo;
  int fechaDeRetiro;
  bool deuda;
} St_UsuarioPrestamo;

typedef struct
{
  char codigo[10];
  char titulo[50];
  int stock;
  double precio;
  int prestados;
  St_UsuarioPrestamo estudiantes[20];
  int cantEst;
  St_UsuarioPrestamo docentes[20];
  int cantDoc;
  St_UsuarioPrestamo administrativos[20];
  int cantAdm;
} St_Libro;

typedef struct
{
  int carne;
  char tipo[30]; // ESTUDIANTE ADMINISTRATIVO DOCENTE
  char nombre[40];
  St_LibroPrestado libPrest[20];
  int numLibPrest;
  char condicion[15]; // HABILITADO INHABILITADO
} St_Usuario;

#endif // ESTRUCTURAS_H