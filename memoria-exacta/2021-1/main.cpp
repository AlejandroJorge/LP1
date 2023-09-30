#include "Tareas.h"

int main(void)
{

  char **conductor, *gravedad;
  int *licencia, *infraccion;
  double *multa;

  cargarConductores(licencia, conductor);
  reporteConductores(licencia, conductor);
  cargarInfracciones(infraccion, gravedad, multa);
  reporteInfracciones(infraccion, gravedad, multa);

  reporteDeFaltas(licencia, conductor, infraccion, gravedad, multa);

  return 0;
}