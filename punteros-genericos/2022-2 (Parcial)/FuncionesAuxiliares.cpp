#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "enums.h"

void imprimeconsultas(void *citas)
{
  void **arr = (void **)citas;
  void **cita;
  void **medicamentos, **medicamento;
  char *paciente;
  int fecha, codMedicina, cant;
  for (int i = 0; arr[i]; i++)
  {
    cita = (void **)arr[i];
    paciente = (char *)cita[CI_NOMBRE];
    fecha = *(int *)cita[CI_FECHA];
    cant = *(int *)cita[CI_CANTIDAD];
    medicamentos = (void **)cita[CI_MEDICINAS];
    cout << "Paciente: " << paciente << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Cantidad: " << cant << endl;
    for (int j = 0; j < cant; j++)
    {
      medicamento = (void **)medicamentos[j];
      codMedicina = *(int *)medicamento[MECI_CODIGO];
      cout << "  Medicina: " << codMedicina << endl;
    }
  }
}
void imprimemedicinas(void *medicinas)
{
  void **arr = (void **)medicinas;
  void **medicina;
  int cod;
  char *nom;
  for (int i = 0; arr[i]; i++)
  {
    medicina = (void **)arr[i];
    cod = *(int *)medicina[ME_CODIGO];
    nom = (char *)medicina[ME_NOMBRE];
    cout << cod << " " << nom << endl;
  }
}
void imprimerepfinal(void *citas)
{
  ofstream arch("Reporte.txt", ios::out);
  if (!arch)
  {
    cout << "No se pudo abrir Reporte.txt" << endl;
    exit(1);
  }
  arch << fixed << left;
  arch.precision(2);

  void **arrCitas = (void **)citas;
  void **cita, **med, **meds;
  arch << "REPORTE FINAL" << endl;
  for (int i = 0; arrCitas[i]; i++)
  {
    cita = (void **)arrCitas[i];
    arch << setw(86) << setfill('=') << "" << setfill(' ') << endl;
    arch << "NOMBRE: " << (char *)cita[CI_NOMBRE] << endl;
    arch << "DNI: " << *(int *)cita[CI_DNI] << endl;
    arch << "FECHA: " << *(int *)cita[CI_FECHA] << endl;
    arch << "CANTIDAD: " << *(int *)cita[CI_CANTIDAD] << endl;
    arch << setw(86) << setfill('=') << "" << setfill(' ') << endl;

    meds = (void **)cita[CI_MEDICINAS];
    arch << setw(15) << "CODIGO";
    arch << setw(15) << "CANTIDAD";
    arch << setw(15) << "ESTADO";
    arch << endl;
    arch << setw(86) << setfill('-') << "" << setfill(' ') << endl;

    for (int j = 0; meds[j]; j++)
    {
      med = (void **)meds[j];
      arch << setw(15) << *(int *)med[MECI_CODIGO];
      if (*(char *)med[MECI_ESTADO] == 'R')
        arch << setw(15) << *(int *)med[MECI_CANTIDAD];
      else
        arch << setw(15) << "-";
      arch << setw(15) << *(char *)med[MECI_ESTADO];
      arch << endl;
    }
  }
  arch << setw(86) << setfill('-') << "" << setfill(' ') << endl;
}

void change(void *&a, void *&b)
{
  void *temp = a;
  a = b;
  b = temp;
}

void quicksort(void *arr, int left, int right)
{
  void **arrIterable = (void **)arr;
  int lim, pos;
  void **a, **b;
  int fechaA, fechaB;
  if (left >= right)
    return;
  pos = (left + right) / 2;
  change(arrIterable[left], arrIterable[pos]);
  lim = left;
  for (int i = left + 1; i <= right; i++)
  {
    a = (void **)arrIterable[i];
    b = (void **)arrIterable[left];
    fechaA = *(int *)a[CI_FECHA];
    fechaB = *(int *)b[CI_FECHA];
    if (fechaA < fechaB)
    {
      lim++;
      change(arrIterable[i], arrIterable[lim]);
    }
  }
  change(arrIterable[lim], arrIterable[left]);
  quicksort(arr, left, lim - 1);
  quicksort(arr, lim + 1, right);
}

void ordenareservas(void *citas)
{
  int len = 0;
  void **arr = (void **)citas;
  while (arr[len])
    len++;
  quicksort(citas, 0, len - 1);
} // Ordenamiento por fecha ascendente