#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "PunterosGenericos.h"
#include "MuestraPunteros.h"
#include "Enums.h"
#define BUFFSIZE 300

void cargaproductos(void *&productos)
{
  ifstream arch("productos2.csv", ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir productos2.csv" << endl;
    exit(1);
  }

  void **buffProductos[BUFFSIZE]{};
  int size = 0;

  int codigo, cantidad;
  char *descripcion;
  double precio;

  void **producto;

  while (true)
  {
    // 422763, GALLETAS SUAVICREMAS FRESA 158GR, 13.85, 14
    arch >> codigo;
    if (arch.eof())
      break;
    arch.get();
    descripcion = leerCadena(arch, ',');
    arch >> precio;
    arch.get();
    arch >> cantidad;
    arch >> ws;

    producto = new void *[4];
    producto[PRO_CODIGO] = new int(codigo);
    producto[PRO_CANTIDAD] = new int(cantidad);
    producto[PRO_DESCRIPCION] = descripcion;
    producto[PRO_PRECIO] = new double(precio);

    buffProductos[size] = producto;
    size++;
  }
  size++;

  void **aux = new void *[size];
  for (int i = 0; i < size; i++)
    aux[i] = buffProductos[i];

  productos = aux;

  // imprimeproductos(productos);
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[BUFFSIZE];
  arch.getline(buff, BUFFSIZE, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  if (del == '\n')
    cad[strlen(buff) - 1] = 0;
  return cad;
}

void cargapedidos(void *&pedidos)
{
  ifstream arch("pedidos2.csv", ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir pedidos2.csv" << endl;
    exit(1);
  }

  void **buffPedidos[BUFFSIZE]{};
  int size = 0;

  int codigo, cantidad, dni, fecha;
  char *descripcion, estado;

  void **ped;

  while (true)
  {
    // 422763,GALLETAS SUAVICREMAS FRESA 158GR,2,17913944,23/09/2019
    arch >> codigo;
    if (arch.eof())
      break;
    arch.get();
    descripcion = leerCadena(arch, ',');
    arch >> cantidad;
    arch.get();
    arch >> dni;
    arch.get();
    fecha = leerFecha(arch);
    estado = 'N';
    arch >> ws;

    ped = new void *[6];
    ped[PE_CANTIDAD] = new int(cantidad);
    ped[PE_CODIGO] = new int(codigo);
    ped[PE_DESCRIPCION] = descripcion;
    ped[PE_DNI] = new int(dni);
    ped[PE_ESTADO] = new char(estado);
    ped[PE_FECHA] = new int(fecha);

    buffPedidos[size] = ped;
    size++;
  }
  size++;

  void **aux = new void *[size];
  for (int i = 0; i < size; i++)
    aux[i] = buffPedidos[i];

  pedidos = aux;

  imprimepedidos(pedidos);
}

int leerFecha(ifstream &arch)
{
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;

  return d + m * 100 + a * 10000;
}

void procesacliente(void *productos, void *pedidos, void *&clientes)
{
  ifstream arch("clientes2.csv", ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir clientes2.csv" << endl;
    exit(1);
  }

  void **buffClientes[BUFFSIZE]{};
  int size = 0;

  int dni;
  char *nombre;

  void **cliente;
  while (true)
  {
    // 91897732, GAMARRA ALCOCER VIRGINIA
    arch >> dni;
    if (arch.eof())
      break;
    arch.get();
    nombre = leerCadena(arch, '\n');
    arch >> ws;

    cliente = new void *[3];
    cliente[CL_DNI] = new int(dni);
    cliente[CL_NOMBRE] = nombre;
    cliente[CL_PEDIDOS] = extraerPedidos(productos, pedidos, dni);

    buffClientes[size] = cliente;
    size++;
  }
  size++;

  void **aux = new void *[size];
  for (int i = 0; i < size; i++)
    aux[i] = buffClientes[i];

  clientes = aux;
}

void *extraerPedidos(void *productos, void *pedidos, int dni)
{
  void **arrProductos = (void **)productos;
  void **arrPedidos = (void **)pedidos;

  void *buffPedidosDelCliente[BUFFSIZE]{};
  int size = 0;

  void **pedido, **producto, **pedidoDelCliente;
  int dniPedido, codigoProducto, posProducto, cantidadPedido, cantidadStock;

  for (int i = 0; arrPedidos[i]; i++)
  {
    // Se trabaja en dos lineas diferentes para que sea mas legible
    pedido = (void **)arrPedidos[i];
    dniPedido = *(int *)pedido[PE_DNI];

    if (dni == dniPedido)
    {
      codigoProducto = *(int *)pedido[PE_CODIGO];
      posProducto = buscarProducto(arrProductos, codigoProducto);
      if (posProducto == -1)
        continue;

      producto = (void **)arrProductos[posProducto];
      cantidadPedido = *(int *)pedido[PE_CANTIDAD];
      cantidadStock = *(int *)producto[PRO_CANTIDAD];

      if (cantidadPedido > cantidadStock)
        continue;

      *(int *)producto[PRO_CANTIDAD] -= cantidadPedido;
      *(char *)pedido[PE_ESTADO] = 'A';

      int codigo = codigoProducto;
      char *descripcion = (char *)producto[PRO_DESCRIPCION];
      int fecha = *(int *)pedido[PE_FECHA];

      pedidoDelCliente = new void *[4];
      pedidoDelCliente[PEDEN_CODIGO] = new int(codigo);
      pedidoDelCliente[PEDEN_DESCRIPCION] = descripcion;
      pedidoDelCliente[PEDEN_FECHA] = new int(fecha);
      pedidoDelCliente[PEDEN_CANTIDAD] = new int(cantidadPedido);

      buffPedidosDelCliente[size] = pedidoDelCliente;
      size++;
    }
  }
  size++;

  void **aux = new void *[size] {};
  for (int i = 0; i < size; i++)
    aux[i] = buffPedidosDelCliente[i];

  return aux;
}

int buscarProducto(void **arrProductos, int codigoProducto)
{
  void **producto;
  int codigoLocal;
  for (int i = 0; arrProductos[i]; i++)
  {
    producto = (void **)arrProductos[i];
    codigoLocal = *(int *)producto[PRO_CODIGO];
    if (codigoLocal == codigoProducto)
      return i;
  }
  return -1;
}