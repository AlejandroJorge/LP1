#include "AsignacionDinamicaMemoriaIncremental.h"

int main()
{

  char ***productos, ***codigoPedidos;
  int *stock, *fechaPedidos, ***dniCantPedidos;
  double *precios;

  lecturaProductos("Productos.csv", productos, stock, precios);
  pruebaLecturaProductos("ReporteProductos.txt", productos, stock, precios);

  lecturaPedidos("Pedidos.csv", fechaPedidos, codigoPedidos, dniCantPedidos);
  pruebaLecturaPedidos("ReportePedidos.txt", fechaPedidos, codigoPedidos, dniCantPedidos);

  reporteEnvioPedidos("ReporteEntregaPedidos.txt", productos, stock, precios, fechaPedidos, codigoPedidos, dniCantPedidos);

  pruebaLecturaProductos("ReporteProductosFinal.txt", productos, stock, precios);

  return 0;
}