#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "PunterosGenericos.h"
#include "enums.h"

void cargaMedicinas(void *&medicinas)
{
  ifstream arch("Medicinas.csv");
  if (!arch)
  {
    cout << "No se pudo abrir Medicinas.csv" << endl;
    exit(1);
  }

  void **buffMedicinas[300]{};
  int size = 0;

  int cod, st;
  char *nom;
  double prec;

  void **med;

  while (true)
  {
    // 82469,GUAYACOL AMPOLLETA 1ML,60.35,47
    arch >> cod;
    if (arch.eof())
      break;
    arch.get();
    nom = leerCadena(arch, ',');
    arch >> prec;
    arch.get();
    arch >> st >> ws;

    med = new void *[5];
    med[ME_CODIGO] = new int(cod);
    med[ME_NOMBRE] = nom;
    med[ME_PRECIO] = new double(prec);
    med[ME_RESERVA] = new int(0);
    med[ME_STOCK] = new int(st);

    buffMedicinas[size] = med;
    size++;
  }
  size++;

  void **arrExacto = new void *[size];
  for (int i = 0; i < size; i++)
    arrExacto[i] = buffMedicinas[i];

  medicinas = arrExacto;
  // imprimemedicinas(medicinas);
}

void cargaConsultas(void *&citas)
{
  ifstream arch("Consultas.csv", ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir Consultas.csv" << endl;
    exit(1);
  }

  void **buffCitas[300]{};
  int size = 0;

  char *codMedico, *nomPaciente;
  int fecha, dni, cantidad;
  void *medicinas;

  void **cita;
  while (true)
  {
    // JL34117,93961840,Pairazaman/Tatiana,1/10/2022,5,46000,10,41995,19,89325,33,37549,7,81333,12
    codMedico = leerCadena(arch, ',');
    if (arch.eof())
      break;
    arch >> dni;
    arch.get();
    nomPaciente = leerCadena(arch, ',');
    fecha = leerFecha(arch);
    arch.get();
    arch >> cantidad;
    medicinas = leerMedicinas(arch, cantidad);
    arch >> ws;

    cita = new void *[5];
    cita[CI_CANTIDAD] = new int(cantidad);
    cita[CI_DNI] = new int(dni);
    cita[CI_FECHA] = new int(fecha);
    cita[CI_MEDICINAS] = medicinas;
    cita[CI_NOMBRE] = nomPaciente;

    buffCitas[size] = cita;
    size++;
  }
  size++;

  void **arrExacto = new void *[size];
  for (int i = 0; i < size; i++)
    arrExacto[i] = buffCitas[i];

  citas = arrExacto;
  // imprimeconsultas(citas);
}
void actualizaReservas(void *medicinas, void *citas)
{
  void **arrCitas = (void **)citas;
  void **cita, **mecis, **meci, **medEncontrada;
  int codMedicina;
  int pos;
  for (int i = 0; arrCitas[i]; i++)
  {
    cita = (void **)arrCitas[i];
    mecis = (void **)cita[CI_MEDICINAS];
    for (int j = 0; mecis[j]; j++)
    {
      meci = (void **)mecis[j];
      codMedicina = *(int *)meci[MECI_CODIGO];
      pos = buscarMedicina(medicinas, codMedicina);
      medEncontrada = (void **)((void **)medicinas)[pos];
      if (*(int *)medEncontrada[ME_STOCK] >= *(int *)cita[CI_CANTIDAD])
      {
        *(int *)medEncontrada[ME_RESERVA] += *(int *)meci[MECI_CANTIDAD];
        *(int *)medEncontrada[ME_STOCK] -= *(int *)meci[MECI_CANTIDAD];
        *(char *)meci[MECI_ESTADO] = 'R';
      }
      if (pos == -1)
        continue;
    }
  }
}

char *leerCadena(ifstream &arch, char del)
{
  char buff[150];
  arch.getline(buff, 150, del);
  char *cad = new char[strlen(buff) + 1];
  strcpy(cad, buff);
  return cad;
}

void *leerMedicinas(ifstream &arch, int cant)
{
  void ***arrMedicinas = new void **[cant + 1] {};

  void **medicina;
  int cod, can;
  for (int i = 0; i < cant; i++)
  {
    arch.get();
    arch >> cod;
    arch.get();
    arch >> can;

    medicina = new void *[4];
    medicina[MECI_CANTIDAD] = new int(can);
    medicina[MECI_CODIGO] = new int(cod);
    medicina[MECI_ESTADO] = new char('S');

    arrMedicinas[i] = medicina;
  }

  return arrMedicinas;
}

int leerFecha(ifstream &arch)
{
  int d, m, a;
  arch >> d;
  arch.get();
  arch >> m;
  arch.get();
  arch >> a;

  return d + m * 100 + a * 10000;
}

int buscarMedicina(void *medicinas, int codMedicina)
{
  void **arr = (void **)medicinas;
  int codIterado;
  void **medicina;
  for (int i = 0; arr[i]; i++)
  {
    medicina = (void **)arr[i];
    codIterado = *(int *)medicina[ME_CODIGO];
    if (codMedicina == codIterado)
      return i;
  }
  return -1;
}