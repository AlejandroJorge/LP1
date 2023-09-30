#include "MetodoExacto.h"

int main()
{
  char **cliNombre, *cliCategoria, **proDescripcion;
  int *cliDni, **cliCodigoProFechaPedido, *proCodigo;
  double *proPrecio, *proDescuento, **cliCantidadPedido;

  cargaClientes(cliDni, cliNombre, cliCategoria);
  reporteClientes(cliDni, cliNombre, cliCategoria);
}