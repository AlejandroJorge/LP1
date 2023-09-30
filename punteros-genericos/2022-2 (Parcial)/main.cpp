#include "FuncionesAuxiliares.h"
#include "PunterosGenericos.h"

int main()
{
  void *medicinas, *citas;

  cargaMedicinas(medicinas);
  cargaConsultas(citas);
  actualizaReservas(medicinas, citas);
  ordenareservas(citas);
  imprimerepfinal(citas);

  return 0;
}