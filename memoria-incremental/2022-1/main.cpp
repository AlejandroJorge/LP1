#include "Clientes.h"
#include "PedidosYProductos.h"

int main()
{
  char ***cliNombreCategoria, ***proCodigoDescripcion, ***pedCodigo;
  int **cliDniTelefono, ***pedFechaCantidad;
  double **proPrecioDescuento;

  CargaDeClientes(cliDniTelefono, cliNombreCategoria, "Clientes.csv");
  ReporteDeClientes(cliDniTelefono, cliNombreCategoria, "ReporteClientes.txt");

  CargaDePedidosYProductos(cliDniTelefono, proCodigoDescripcion, proPrecioDescuento,
                           pedCodigo, pedFechaCantidad, "Pedidos.csv");

  ReporteDePedidosYProductos(cliDniTelefono, proCodigoDescripcion, proPrecioDescuento,
                             pedCodigo, pedFechaCantidad, "ReportePedidosYProductos.txt");

  ReporteRelacionDePedidos(cliDniTelefono, cliNombreCategoria, proCodigoDescripcion, proPrecioDescuento,
                           pedCodigo, pedFechaCantidad, "ReporteRelacionPedidos.txt");

  return 0;
}