#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "ClientesPreg1.h"
#define BUFF 300

void CargaDeClientes(int ***&cliDniTelPed, char ***&cliNombreCategoria, const char *nomArch)
{
  // 71984468,IPARRAGUIRRE VILLEGAS NICOLAS EDILBERTO B,935441620
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  int **buffCliDniTelPed[BUFF]{};
  char **buffCliNombreCategoria[BUFF]{};
  int size = 0;

  int dni, telefono;
  char *cadena;

  int **dniTelPed;
  char **nombreCategoria;
  while (true)
  {
    arch >> dni;
    if (arch.eof())
      break;
    arch.get();
    cadena = leerCad(arch, ',');
    arch >> telefono;

    nombreCategoria = crearNombreCategoria(cadena);
    dniTelPed = crearDniTelPed(dni, telefono);

    buffCliDniTelPed[size] = dniTelPed;
    buffCliNombreCategoria[size] = nombreCategoria;
    size++;
  }
  size++;

  cliDniTelPed = new int **[size];
  cliNombreCategoria = new char **[size];

  for (int i = 0; i < size; i++)
  {
    cliDniTelPed[i] = buffCliDniTelPed[i];
    cliNombreCategoria[i] = buffCliNombreCategoria[i];
  }
}

char *leerCad(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  return cad;
}

char **crearNombreCategoria(char *&cadena)
{
  int len = strlen(cadena);
  char *nombre, *categoria;
  char **nombreCategoria = new char *[2];

  if (cadena[len - 2] == ' ')
  {
    nombre = new char[len - 1]{};
    for (int i = 0; i < len - 2; i++)
      nombre[i] = cadena[i];
    categoria = new char(cadena[len - 1]);
  }
  else
  {
    nombre = new char[len + 1]{};
    strcpy(nombre, cadena);
    categoria = new char('-');
  }

  nombreCategoria[0] = nombre;
  nombreCategoria[1] = categoria;
  return nombreCategoria;
}

int **crearDniTelPed(int dni, int telefono)
{
  int **dniTelPed = new int *[3];
  dniTelPed[0] = new int(dni);
  dniTelPed[1] = new int(telefono);
  dniTelPed[2] = nullptr;
  return dniTelPed;
}

void PruebaDeClientes(int ***cliDniTelPed, char ***cliNombreCategoria, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  arch << fixed << left;
  arch.precision(2);

  arch << "REPORTE DE CLIENTES" << endl;
  arch << setw(100) << setfill('=') << "" << setfill(' ') << endl;

  int **dniTelPed;
  int *pedidos;

  for (int i = 0; cliDniTelPed[i]; i++)
  {
    imprimirCabeceraCliente(arch, cliDniTelPed[i], cliNombreCategoria[i]);
    arch << setw(100) << setfill('-') << "" << setfill(' ') << endl;
    dniTelPed = cliDniTelPed[i];
    pedidos = dniTelPed[2];
    imprimirPedidos(arch, pedidos);
    arch << setw(100) << setfill('=') << "" << setfill(' ') << endl;
  }
}

void imprimirCabeceraCliente(ofstream &arch, int **dniTelPed, char **nombreCategoria)
{
  char *nombre = nombreCategoria[0];
  char *categoria = nombreCategoria[1];
  int dni = *dniTelPed[0];
  int telefono = *dniTelPed[1];

  arch << "NOMBRE: " << setw(50) << nombre << "CATEGORIA: " << *categoria << endl;
  arch << "DNI: " << setw(30) << dni << "TELEFONO: " << telefono << endl;
}

void imprimirPedidos(ofstream &arch, int *pedidos)
{
  if (pedidos == nullptr)
    return;

  arch << setw(15) << "FECHA";
  arch << setw(15) << "CANTIDAD";
  arch << setw(15) << "CODIGO";
  arch << endl;

  arch << setw(100) << setfill('-') << "" << setfill(' ') << endl;

  for (int i = 0; pedidos[i]; i += 3)
  {
    arch << setw(15) << pedidos[i];
    arch << setw(15) << pedidos[i + 1];
    arch << setw(15) << pedidos[i + 2];
    arch << endl;
  }
}