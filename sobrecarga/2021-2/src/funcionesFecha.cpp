#include "../headers/funcionesFecha.h"

int numeroDeDias(int fecha1, int fecha2)
{
  // fecha1 y fecha2 están en el formato aaaammdd
  int dd1, mm1, aa1, dd2, mm2, aa2;
  int cont = 0, aux;
  if (fecha1 < fecha2)
  {
    aux = fecha1;
    fecha1 = fecha2;
    fecha2 = aux;
  }
  fTodma(fecha1, dd1, mm1, aa1);
  fTodma(fecha2, dd2, mm2, aa2);
  while (dd1 != dd2 or mm1 != mm2 or aa1 != aa2)
  {
    dd1--;
    cont++;
    if (dd1 == 0)
    {
      mm1--;
      if (mm1 == 0)
      {
        aa1--;
        mm1 = 12;
      }
      dd1 = diasDelMes(mm1, aa1);
    }
  }
  return cont;
}

void fTodma(int fecha, int &dd, int &mm, int &aa)
{
  aa = fecha / 10000;
  fecha = fecha % 10000;
  mm = fecha / 100;
  dd = fecha % 100;
}

int diasDelMes(int mm, int aa)
{
  switch (mm)
  {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    return 31;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    if (aa % 4 == 0 && (aa % 100 != 0 || aa % 400 == 0))
      return 29;
    return 28;
  }
}