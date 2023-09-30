#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Enums.h"
#include "MuestraPunteros.h"

void imprimirPedido(ofstream &arch, void *pedido)
{
  void **ped = (void **)pedido;

  int codigo = *(int *)ped[PE_CODIGO];
  char *descripcion = (char *)ped[PE_DESCRIPCION];
  int cantidad = *(int *)ped[PE_CANTIDAD];
  int dni = *(int *)ped[PE_DNI];
  int fecha = *(int *)ped[PE_FECHA];
  char estado = *(char *)ped[PE_ESTADO];

  arch << setw(10) << codigo;
  arch << setw(60) << descripcion;
  arch << setw(10) << cantidad;
  arch << setw(10) << dni;
  arch << setw(10) << fecha;
  arch << setw(10) << estado;
  arch << endl;
}

void imprimepedidos(void *pedidos)
{
  ofstream arch("ReportePedidos.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir ReportePedidos.txt" << endl;
    exit(1);
  }

  arch << left << fixed;
  arch.precision(2);

  void **arrPedidos = (void **)pedidos;

  arch << setfill('=') << setw(110) << "" << setfill(' ') << endl;

  arch << setw(10) << "CODIGO";
  arch << setw(60) << "DESCRIPCION";
  arch << setw(10) << "CANTIDAD";
  arch << setw(10) << "DNI";
  arch << setw(10) << "FECHA";
  arch << setw(10) << "ESTADO";
  arch << endl;

  arch << setfill('=') << setw(110) << "" << setfill(' ') << endl;

  for (int i = 0; arrPedidos[i]; i++)
    imprimirPedido(arch, arrPedidos[i]);

  arch << endl;
}

void imprimirProducto(ofstream &arch, void *producto)
{
  void **prod = (void **)producto;

  int cantidad = *(int *)prod[PRO_CANTIDAD];
  int codigo = *(int *)prod[PRO_CODIGO];
  char *descripcion = (char *)prod[PRO_DESCRIPCION];
  double precio = *(double *)prod[PRO_PRECIO];

  arch << setw(10) << codigo;
  arch << setw(60) << descripcion;
  arch << setw(10) << cantidad;
  arch << setw(10) << precio;
  arch << endl;
}

void imprimeproductos(void *productos)
{
  ofstream arch("ReporteProductos.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir ReporteProductos.txt" << endl;
    exit(1);
  }

  arch << left << fixed;
  arch.precision(2);

  void **arrProductos = (void **)productos;

  arch << setfill('=') << setw(90) << "" << setfill(' ') << endl;

  arch << setw(10) << "CODIGO";
  arch << setw(60) << "DESCRIPCION";
  arch << setw(10) << "CANTIDAD";
  arch << setw(10) << "PRECIO";
  arch << endl;

  arch << setfill('=') << setw(90) << "" << setfill(' ') << endl;

  for (int i = 0; arrProductos[i]; i++)
    imprimirProducto(arch, arrProductos[i]);
}
void imprimerepfinal(void *clientes)
{
  ofstream arch("ReporteFinal.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir ReporteFinal.txt" << endl;
    exit(1);
  }
  arch << fixed << left;
  arch.precision(2);

  arch << setw(100) << setfill('=') << "" << setfill(' ') << endl;
  arch << "PEDIDOS ATENDIDOS POR CLIENTE" << endl;

  void **arrClientes = (void **)clientes;

  int dni;
  char *nombre;
  void **cliente;
  void **arrPedidosCliente;
  void **pedido;
  int fecha, codigo, cantidad;
  char *descripcion;
  for (int i = 0; arrClientes[i]; i++)
  {
    cliente = (void **)arrClientes[i];

    arch << setw(100) << setfill('=') << "" << setfill(' ') << endl;

    dni = *(int *)cliente[CL_DNI];
    nombre = (char *)cliente[CL_NOMBRE];

    arch << setw(15) << "DNI";
    arch << setw(70) << "NOMBRE";
    arch << endl;

    arch << setw(15) << dni;
    arch << setw(70) << nombre;
    arch << endl;

    arch << setw(100) << setfill('-') << "" << setfill(' ') << endl;
    arch << "PEDIDOS ATENDIDOS" << endl;
    arch << setw(100) << setfill('-') << "" << setfill(' ') << endl;
    arch << setw(15) << "FECHA";
    arch << setw(15) << "CODIGO";
    arch << setw(60) << "DESCRIPCION";
    arch << setw(10) << "CANTIDAD";
    arch << endl;
    arch << setw(100) << setfill('-') << "" << setfill(' ') << endl;

    arrPedidosCliente = (void **)cliente[CL_PEDIDOS];
    for (int i = 0; arrPedidosCliente[i]; i++)
    {
      pedido = (void **)arrPedidosCliente[i];

      fecha = *(int *)pedido[PEDEN_FECHA];
      descripcion = (char *)pedido[PEDEN_DESCRIPCION];
      codigo = *(int *)pedido[PEDEN_CODIGO];
      cantidad = *(int *)pedido[PEDEN_CANTIDAD];

      arch << setw(15) << fecha;
      arch << setw(15) << codigo;
      arch << setw(60) << descripcion;
      arch << setw(10) << cantidad;
      arch << endl;
    }
  }
}

void imprimereporte(void *cli)
{
  ofstream ach("ReporteDePedidos.txt", ios::out);
  if (not ach.is_open())
  {
    cout << "no se pudo abrir" << endl;
    exit(1);
  }
  void **clientes = (void **)cli;
  void **cliente;
  char *nom;
  int dni;
  void **pedidos;
  ach << setfill('=') << setw(100) << " " << setfill(' ') << endl;
  ach << "PEDIDOS ATENDIDOS POR CLIENTE:" << endl;
  ach << setfill('=') << setw(100) << " " << setfill(' ') << endl;
  for (int i = 0; clientes[i]; i++)
  {
    ach << "Dni" << setw(20) << "Nombre" << endl;
    ach << setfill('-') << setw(100) << " " << setfill(' ') << endl;
    cliente = (void **)clientes[i];
    dni = *(int *)cliente[CL_DNI];
    nom = (char *)cliente[CL_NOMBRE];
    ach << dni << setw(10) << " " << left << nom << endl;
    pedidos = (void **)cliente[CL_PEDIDOS];
    // if (pedidos)
    imprimirPedidos(pedidos, ach);
  }
}

void imprimirPedidos(void *ped, ofstream &ach)
{
  ach << "Pedidos atendidos:" << endl;
  ach << setfill('-') << setw(100) << " " << setfill(' ') << endl;
  ach << right << "Fecha" << setw(20) << "Codigo" << setw(35) << "Descripcion del Producto" << setw(20) << "Cantidad" << endl;
  ach << setfill('-') << setw(100) << " " << setfill(' ') << endl;
  void **pedidos = (void **)ped;
  void **pedido;
  int *fecha, cant, cod;
  char *descripcion;
  for (int i = 0; pedidos[i]; i++)
  {
    pedido = (void **)pedidos[i];
    fecha = (int *)pedido[PEDEN_FECHA];
    cant = *(int *)pedido[PEDEN_CANTIDAD];
    cod = *(int *)pedido[PEDEN_CODIGO];
    descripcion = (char *)pedido[PEDEN_DESCRIPCION];
    //        impFecha(*fecha,ach);
    ach << right << setw(10) << cod;
    ach << left << setw(40) << descripcion << " ";
    ach << right << setw(3) << cant << endl;
  }
}

void impFecha(int fecha, ofstream &ach)
{
  ach << right << setw(12) << setfill('0') << setw(2) << fecha % 100
      << setfill('0') << setw(2) << fecha / 100 % 100
      << setfill('0') << setw(4) << fecha / 10000 << setfill(' ');
}