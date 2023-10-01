#include "PunterosGenericos.h"
#include "MuestraPunteros.h"

int main(void)
{
  void *productos, *clientes, *pedidos;

  cargaproductos(productos);
  cargapedidos(pedidos);
  procesacliente(productos, pedidos, clientes);
  // imprimerepfinal(clientes);
  imprimereporte(clientes);

  return 0;
}