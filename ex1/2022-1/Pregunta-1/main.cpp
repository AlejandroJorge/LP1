#include "ClientesPreg1.h"
#include "FuncionesExamen01Pregunta01.h"

int main()
{

  char ***cliNombreCategoria, **proDescripcion;
  int ***cliDniTelPed, **proInformacion, **pedTodo;

  CargaDeClientes(cliDniTelPed, cliNombreCategoria, "ClientesPreg01.csv");
  PruebaDeClientes(cliDniTelPed, cliNombreCategoria, "PruebaClientes01.txt");

  CargaProductosPedidos(proInformacion, proDescripcion, pedTodo, "PedidosPreg01.csv");
  PruebaProductosPedidos(proInformacion, proDescripcion, pedTodo, "PruebaProductosPedidos01.txt");

  ordenarPedidos(pedTodo);
  PruebaProductosPedidos(proInformacion, proDescripcion, pedTodo, "PruebaProductosPedidos02.txt");

  asignarPedidos(cliDniTelPed, proInformacion, pedTodo);
  PruebaProductosPedidos(proInformacion, proDescripcion, pedTodo, "PruebaProductosPedidos03.txt");
  PruebaDeClientes(cliDniTelPed, cliNombreCategoria, "PruebaClientes02.txt");

  return 0;
}