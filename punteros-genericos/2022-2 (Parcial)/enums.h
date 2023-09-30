#ifndef ENUMS_H
#define ENUMS_H

enum Medicina
{
  ME_CODIGO,
  ME_NOMBRE,
  ME_PRECIO,
  ME_STOCK,
  ME_RESERVA
};

enum Cita
{
  CI_DNI,
  CI_NOMBRE,
  CI_CANTIDAD,
  CI_MEDICINAS,
  CI_FECHA
};

enum MedicinaCita
{
  MECI_CODIGO,
  MECI_CANTIDAD,
  MECI_ESTADO
};

#endif /*ENUMS_H*/