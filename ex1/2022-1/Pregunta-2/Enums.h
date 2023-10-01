#ifndef ENUMS_H
#define ENUMS_H

enum Producto
{
  PRO_CODIGO,
  PRO_DESCRIPCION,
  PRO_PRECIO,
  PRO_CANTIDAD,
};

enum Pedido
{
  PE_CODIGO,
  PE_DESCRIPCION,
  PE_CANTIDAD,
  PE_DNI,
  PE_FECHA,
  PE_ESTADO
};

enum Cliente
{
  CL_DNI,
  CL_NOMBRE,
  CL_PEDIDOS
};

enum PedidosEntregados
{
  PEDEN_FECHA,
  PEDEN_CODIGO,
  PEDEN_DESCRIPCION,
  PEDEN_CANTIDAD
};

#endif /*ENUMS_H*/