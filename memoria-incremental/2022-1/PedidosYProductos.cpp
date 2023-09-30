#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "PedidosYProductos.h"
#define INCREMENTO 5

void CargaDePedidosYProductos(int **cliDniTelefono, char ***&proCodigoDescripcion, double **&proPrecioDescuento,
                              char ***&pedCodigo, int ***&pedFechaCantidad, const char *nomArch)
{
  // WCF779,LICUADO LALA CIRUELA PASA Y NUEZ 240GR,%5.13,19,10.89,33713901,19/04/2020
  ifstream arch(nomArch, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }

  // Para la estructura de productos
  proCodigoDescripcion = nullptr;
  proPrecioDescuento = nullptr;
  int cantidadPro = 0, capacidadPro = 0;

  // Para la estructura de pedidos (corresponde con la estructura de clientes)
  int lenClientes = 0;
  while (cliDniTelefono[lenClientes])
    lenClientes++;
  pedCodigo = new char **[lenClientes + 1] {};
  pedFechaCantidad = new int **[lenClientes + 1] {};
  int cantidadPed[lenClientes + 1]{}, capacidadPed[lenClientes + 1]{};

  char *codigo, *descripcion;
  double descuento, precio;
  int cantidad, dni, fecha;

  int *fechaCantidad;
  char **codigoDescripcion;
  double *precioDescuento;

  int posProd, posCli;

  while (true)
  {
    codigo = leerCadena(arch, ',');
    descripcion = leerCadena(arch, ',');
    if (arch.get() == '%')
    {
      arch >> descuento;
      arch.get();
    }
    else
    {
      arch.unget();
      descuento = 0;
    }
    arch >> cantidad;
    arch.get();
    arch >> precio;
    arch.get();
    arch >> dni;
    arch.get();
    fecha = leerFecha(arch);
    arch >> ws;

    precioDescuento = new double[2];
    precioDescuento[0] = precio;
    precioDescuento[1] = descuento;

    codigoDescripcion = new char *[2];
    codigoDescripcion[0] = codigo;
    codigoDescripcion[1] = descripcion;

    fechaCantidad = new int[2];
    fechaCantidad[0] = fecha;
    fechaCantidad[1] = cantidad;

    // Asignamos para la estructura de productos
    posProd = buscarProd(proCodigoDescripcion, codigo);
    if (posProd == -1)
      agregarProducto(proCodigoDescripcion, proPrecioDescuento, codigoDescripcion, precioDescuento,
                      cantidadPro, capacidadPro);

    // Asignamos para la estructura de pedidos (agregamos pedidos a un cliente)
    posCli = buscarCli(cliDniTelefono, dni);
    if (posCli != -1)
      agregarPedido(pedCodigo[posCli], pedFechaCantidad[posCli], codigo, fechaCantidad,
                    cantidadPed[posCli], capacidadPed[posCli]);

    arch.peek();
    if (arch.eof())
      break;
  }
}

int buscarProd(char ***proCodigoDescripcion, char *codigo)
{
  if (proCodigoDescripcion == nullptr)
    return -1;

  for (int i = 0; proCodigoDescripcion[i]; i++)
    if (strcmp(proCodigoDescripcion[i][0], codigo) == 0)
      return i;
  return -1;
}

int buscarCli(int **cliDniTelefono, int dni)
{
  for (int i = 0; cliDniTelefono[i]; i++)
    if (cliDniTelefono[i][0] == dni)
      return i;
  return -1;
}

void agregarProducto(char ***&proCodigoDescripcion, double **&proPrecioDescuento,
                     char **codigoDescripcion, double *precioDescuento, int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    char ***auxProCD = new char **[capacidad + INCREMENTO + 1] {};
    double **auxProPD = new double *[capacidad + INCREMENTO + 1] {};

    if (capacidad > 0)
    {
      for (int i = 0; i < cantidad; i++)
      {
        auxProCD[i] = proCodigoDescripcion[i];
        auxProPD[i] = proPrecioDescuento[i];
      }
      delete proCodigoDescripcion;
      delete proPrecioDescuento;
    }
    proCodigoDescripcion = auxProCD;
    proPrecioDescuento = auxProPD;
    capacidad += INCREMENTO;
  }
  proCodigoDescripcion[cantidad] = codigoDescripcion;
  proPrecioDescuento[cantidad] = precioDescuento;
  cantidad++;
}

void agregarPedido(char **&pedCodigo, int **&pedFechaCantidad, char *codigo, int *fechaCantidad,
                   int &cantidad, int &capacidad)
{
  if (cantidad == capacidad)
  {
    char **auxPedCodigo = new char *[capacidad + INCREMENTO + 1] {};
    int **auxPedFechaCantidad = new int *[capacidad + INCREMENTO + 1] {};
    if (capacidad > 0)
    {
      for (int i = 0; pedCodigo[i]; i++)
      {
        auxPedCodigo[i] = pedCodigo[i];
        auxPedFechaCantidad[i] = pedFechaCantidad[i];
      }
      delete pedCodigo;
      delete pedFechaCantidad;
    }
    pedCodigo = auxPedCodigo;
    pedFechaCantidad = auxPedFechaCantidad;

    capacidad++;
  }
  pedCodigo[cantidad] = codigo;
  pedFechaCantidad[cantidad] = fechaCantidad;
  cantidad++;
}

int leerFecha(ifstream &arch)
{
  // 19/04/2020
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;
  return d + m * 100 + a * 10000;
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[150];
  arch.getline(buff, 150, del);
  char *cadena = new char[strlen(buff) + 1];
  strcpy(cadena, buff);
  // FIX LINUX
  if (del == '\n')
    cadena[strlen(buff) - 1] = 0;
  // FIX LINUX
  return cadena;
}

void ReporteDePedidosYProductos(int **cliDniTelefono, char ***proCodigoDescripcion, double **proPrecioDescuento,
                                char ***pedCodigo, int ***pedFechaCantidad, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  arch << fixed << left;
  arch.precision(2);

  // Para los productos
  arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;
  arch << "PRODUCTOS" << endl;
  arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;

  arch << setw(15) << "CODIGO";
  arch << setw(60) << "DESCRIPCION";
  arch << setw(10) << "PRECIO";
  arch << setw(10) << "DESCUENTO";
  arch << endl;

  for (int i = 0; proCodigoDescripcion[i]; i++)
  {
    arch << setw(15) << proCodigoDescripcion[i][0];
    arch << setw(60) << proCodigoDescripcion[i][1];
    arch << setw(10) << proPrecioDescuento[i][0];
    arch << setw(10) << proPrecioDescuento[i][1];
    arch << endl;
  }

  // Para los pedidos
  arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;
  arch << "PEDIDOS" << endl;
  arch << setw(90) << setfill('=') << "" << setfill(' ') << endl;

  for (int i = 0; cliDniTelefono[i]; i++)
  {
    arch << "DNI: " << cliDniTelefono[i][0] << endl;
    arch << setw(90) << setfill('-') << "" << setfill(' ') << endl;
    imprimirPedidos(arch, pedCodigo[i], pedFechaCantidad[i]);
    arch << setw(90) << setfill('-') << "" << setfill(' ') << endl;
  }
}

void imprimirPedidos(ofstream &arch, char **pedCodigo, int **pedFechaCantidad)
{
  arch << setw(5) << "";
  arch << setw(15) << "CODIGO";
  arch << setw(10) << "FECHA";
  arch << setw(10) << "CANTIDAD";
  arch << endl;

  for (int i = 0; pedCodigo[i]; i++)
  {
    arch << right << setw(4) << i + 1 << ")" << left;
    arch << setw(15) << pedCodigo[i];
    arch << setw(10) << pedFechaCantidad[i][0];
    arch << setw(10) << pedFechaCantidad[i][1];
    arch << endl;
  }
}

void ReporteRelacionDePedidos(int **cliDniTelefono, char ***cliNombreCategoria, char ***proCodigoDescripcion,
                              double **proPrecioDescuento, char ***pedCodigo, int ***pedFechaCantidad, const char *nomArch)
{
  ofstream arch(nomArch, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  arch << left << fixed;
  arch.precision(2);

  arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;
  arch << "GASTOS DE LOS CLIENTES REGISTRADOS:" << endl;

  for (int i = 0; cliDniTelefono[i]; i++)
  {
    arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;

    arch << setw(15) << "DNI";
    arch << setw(60) << "NOMBRE";
    arch << setw(15) << "CATEGORIA";
    arch << setw(20) << "TELEFONO";
    arch << endl;

    arch << setw(15) << cliDniTelefono[i][0];
    arch << setw(60) << cliNombreCategoria[i][0];
    arch << setw(15) << cliNombreCategoria[i][1];
    arch << setw(20) << cliDniTelefono[i][1];
    arch << endl;

    arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;
    arch << "PRODUCTOS ADQUIRIDOS" << endl;
    arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

    arch << setw(10) << "";
    arch << setw(15) << "CODIGO";
    arch << setw(40) << "DESCRIPCION";
    arch << setw(15) << "P.U";
    arch << setw(15) << "CANTIDAD";
    arch << setw(15) << "TOTAL";
    arch << setw(15) << "DESCUENTO %";
    arch << setw(15) << "A PAGAR";
    arch << setw(15) << "DESCUENTO";
    arch << setw(15) << "FECHA";
    arch << endl;

    for (int j = 0; pedCodigo[j]; j++)
      imprimirLineaReporte(arch, i, pedCodigo[i][j], pedFechaCantidad[i][j], proCodigoDescripcion,
                           proPrecioDescuento);

    arch << setw(120) << setfill('-') << "" << setfill(' ') << endl;

    arch << setw(120) << setfill('=') << "" << setfill(' ') << endl;
  }
}

void imprimirLineaReporte(ofstream &arch, int num, char *pedCodigo, int *pedFechaCantidad,
                          char ***proCodigoDescripcion, double **proPrecioDescuento)
{
  int posProd = buscarProd(proCodigoDescripcion, pedCodigo);
  if (posProd == -1)
    return;

  // cout << "Encontrado " << pos << endl;

  // double totalPrecio = proPrecioDescuento[pos][0] * pedFechaCantidad[1];
  // double aPagar = totalPrecio * (1 - proPrecioDescuento[pos][1] / 100);
  // arch << setw(10) << num;
  // arch << setw(15) << pedCodigo;
  // arch << setw(40) << proCodigoDescripcion[pos][1];
  // arch << setw(15) << proPrecioDescuento[pos][0];
  // arch << setw(15) << pedFechaCantidad[1];
  // arch << setw(15) << totalPrecio;
  // arch << setw(15) << proPrecioDescuento[pos][1];
  // arch << setw(15) << aPagar;
  // arch << setw(15) << totalPrecio - aPagar;
  // arch << setw(15) << pedFechaCantidad[0];
  // arch << endl;
}