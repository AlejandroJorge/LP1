#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
#include "FuncionesExamen01Pregunta01.h"
#define BUFF 300
#define INCREMENTO 5

void CargaProductosPedidos(int **&proInformacion, char **&proDescripcion, int **&pedTodo, const char *nomArch)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  int *buffProInformacion[BUFF]{};
  char *buffProDescripcion[BUFF]{};
  int *buffPedTodo[BUFF * 2]{};
  int sizePro = 0;
  int sizeTodo = 0;

  int codigo, dni, fecha;
  char *descripcion;
  double descuento, cantidad, precioUnitario, stock;

  int *localProInformacion;
  int *localPedTodo;

  int posPro;

  while (true)
  {
    // 872819,GELATINA DE LECHE VAINILLA DANETTE 100GR,5.54,5.13,8.19,32821689,19/04/2020
    arch >> codigo;
    if (arch.eof())
      break;
    arch.get();
    descripcion = leerCadena(arch, ',');
    arch >> descuento;
    if (arch.peek() != '%')
    {
      cantidad = descuento;
      descuento = 0;
    }
    else
    {
      arch.get();
      arch.get();
      arch >> cantidad;
    }
    arch.get();
    arch >> precioUnitario;
    arch.get();
    arch >> stock;
    arch.get();
    arch >> dni;
    arch.get();
    fecha = leerFecha(arch);

    localPedTodo = crearPedido(dni, fecha, cantidad, codigo);
    buffPedTodo[sizeTodo] = localPedTodo;
    sizeTodo++;

    posPro = buscarProducto(buffProInformacion, codigo);
    if (posPro == -1)
    {
      localProInformacion = crearProInformacion(codigo, descuento, precioUnitario, stock);
      buffProInformacion[sizePro] = localProInformacion;
      buffProDescripcion[sizePro] = descripcion;
      sizePro++;
    }
  }
  sizePro++;
  sizeTodo++;

  proInformacion = new int *[sizePro] {};
  proDescripcion = new char *[sizePro] {};
  for (int i = 0; i < sizePro; i++)
  {
    proInformacion[i] = buffProInformacion[i];
    proDescripcion[i] = buffProDescripcion[i];
  }

  pedTodo = new int *[sizeTodo];
  for (int i = 0; i < sizeTodo; i++)
    pedTodo[i] = buffPedTodo[i];
}

void PruebaProductosPedidos(int **proInformacion, char **proDescripcion, int **pedTodo, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  arch << fixed << left;
  arch.precision(2);

  arch << "REPORTE DE PRODUCTOS" << endl;
  arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(15) << "CODIGO";
  arch << setw(60) << "DESCRIPCION";
  arch << setw(15) << "DESCUENTO";
  arch << setw(15) << "PRECIO";
  arch << setw(15) << "STOCK";
  arch << endl;

  arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

  int *localProInformacion;

  for (int i = 0; proInformacion[i]; i++)
  {
    localProInformacion = proInformacion[i];

    arch << setw(15) << localProInformacion[0];
    arch << setw(60) << proDescripcion[i];
    arch << setw(15) << localProInformacion[1] / 100.0;
    arch << setw(15) << localProInformacion[2] / 100.0;
    arch << setw(15) << localProInformacion[3] / 100.0;
    arch << endl;
  }

  arch << "REPORTE DE PEDIDOS" << endl;
  arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(30) << "DNI";
  arch << setw(30) << "FECHA";
  arch << setw(30) << "CANTIDAD";
  arch << setw(30) << "CODIGO";
  arch << endl;

  arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

  int *pedActual;
  for (int i = 0; pedTodo[i]; i++)
  {
    pedActual = pedTodo[i];

    arch << setw(30) << pedActual[0];
    arch << setw(30) << pedActual[1];
    arch << setw(30) << pedActual[2];
    arch << setw(30) << pedActual[3];
    arch << endl;
  }
}

void ordenarPedidos(int **pedTodo)
{
  int len = 0;
  while (pedTodo[len])
    len++;
  quickSort(pedTodo, 0, len - 1);
}

void asignarPedidos(int ***cliDniTelPed, int **proInformacion, int **pedTodo)
{
  int *pedido;

  int posCliente;
  int posProducto;

  int cantClientes = 0;
  while (cliDniTelPed[cantClientes])
    cantClientes++;

  int capacidad[cantClientes]{}, cantidad[cantClientes]{};
  int **cliente;

  for (int i = 0; pedTodo[i]; i++)
  {
    pedido = pedTodo[i];
    posCliente = buscarCliente(cliDniTelPed, pedido[0]);
    posProducto = buscarProducto(proInformacion, pedido[3]);

    if (posCliente == -1 || posProducto == -1)
      continue;

    if (hayStock(proInformacion[posProducto], pedido))
    {
      cliente = cliDniTelPed[posCliente];

      agregarPedido(cliente[2], cantidad[posCliente], capacidad[posCliente], pedido);
      disminuirStock(proInformacion[posProducto], pedido);
    }
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[100];
  arch.getline(buff, 100, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  return cad;
}

int leerFecha(ifstream &arch)
{
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;

  return a * 10000 + m * 100 + d;
}

int *crearPedido(int dni, int fecha, int cantidad, int codigo)
{
  int *pedTodo = new int[4];
  pedTodo[0] = dni;
  pedTodo[1] = fecha;
  pedTodo[2] = cantidad;
  pedTodo[3] = codigo;
  return pedTodo;
}

int *crearProInformacion(int codigo, double descuento, double precioUnitario, double stock)
{
  int *proInformacion = new int[4];
  proInformacion[0] = codigo;
  proInformacion[1] = (int)(descuento * 100);
  proInformacion[2] = (int)(precioUnitario * 100);
  proInformacion[3] = (int)(stock * 100);
  return proInformacion;
}

int buscarProducto(int **arrProInformacion, int codigo)
{
  int *proInformacion;
  for (int i = 0; arrProInformacion[i]; i++)
  {
    proInformacion = arrProInformacion[i];
    if (proInformacion[0] == codigo)
      return i;
  }
  return -1;
}

void quickSort(int **pedidos, int izq, int der)
{
  int lim, pos;
  int *pedidoA, *pedidoB;
  if (izq >= der)
    return;
  pos = (izq + der) / 2;
  intercambiar(pedidos[izq], pedidos[pos]);
  lim = izq;
  for (int i = izq + 1; i <= der; i++)
  {
    pedidoA = pedidos[i];
    pedidoB = pedidos[izq];
    if (pedidoA[1] < pedidoB[1])
    {
      lim++;
      intercambiar(pedidos[lim], pedidos[i]);
    }
  }
  intercambiar(pedidos[lim], pedidos[izq]);
  quickSort(pedidos, izq, lim - 1);
  quickSort(pedidos, lim + 1, der);
}

void intercambiar(int *&a, int *&b)
{
  int *aux = a;
  a = b;
  b = aux;
}

int buscarCliente(int ***arrDniTelPed, int dni)
{
  int **dniTelPed, dniAct;
  for (int i = 0; arrDniTelPed[i]; i++)
  {
    dniTelPed = arrDniTelPed[i];
    dniAct = *dniTelPed[0];
    if (dniAct == dni)
      return i;
  }
  return -1;
}

bool hayStock(int *producto, int *pedido)
{
  int stock = producto[3];
  int cantidad = pedido[2];
  return stock >= cantidad;
}

void agregarPedido(int *&arrPedidos, int &cantidad, int &capacidad, int *pedido)
{
  int *arrAux;
  if (capacidad == cantidad)
  {
    arrAux = new int[capacidad * 3 + INCREMENTO * 3 + 1]{};
    if (capacidad != 0)
    {
      for (int i = 0; arrPedidos[i]; i++)
        arrAux[i] = arrPedidos[i];
      delete arrPedidos;
    }
    arrPedidos = arrAux;
    capacidad += INCREMENTO;
  }
  arrPedidos[cantidad * 3] = pedido[1];
  arrPedidos[cantidad * 3 + 1] = pedido[2];
  arrPedidos[cantidad * 3 + 2] = pedido[3];
  cantidad++;
}

void disminuirStock(int *producto, int *pedido)
{
  int stock = producto[3];
  int cantidad = pedido[2];

  stock -= cantidad;
  producto[3] = stock;
}
