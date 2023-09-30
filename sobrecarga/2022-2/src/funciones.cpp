#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../headers/Estructuras.h"

// 506117   EDGAR_MUNOZ_VERGEL_Urologia   337.03
bool operator>>(ifstream &arch, StMedico &medico){
  char buffCadena[100];
  arch >> medico.codigo >> buffCadena >> medico.tarifaPoxConsulta;
  
  int posSeparador = 0;
  for(int i=0; buffCadena[i];i++)
    if(buffCadena[i]=='_') posSeparador = i;
  
  for(int i=0; i<posSeparador;i++)
    medico.nombre[i] = buffCadena[i];

  for(int i=0; buffCadena[i+posSeparador+1];i++)
    medico.especialidad[i] = buffCadena[i+posSeparador+1];
  
  return !arch.eof();
}

// 43704548   Vizcardo/Maribel   960851431
bool operator>>(ifstream &arch, StPaciente &paciente){
  arch >> paciente.dni >> paciente.nombre >> paciente.telefono;
  paciente.numeroDeCitas = 0;
  paciente.totalGastado = 0;

  return !arch.eof();
}

// 43704548   892133   9/09/2022
int operator>>(ifstream &arch, StCita &cita){
  int buffDni, d, m, a;
  char c;
  arch >> buffDni >> cita.codigoDelMedico;
  arch >> d; 
  arch.get(); 
  arch >> m;
  arch.get(); 
  arch >> a;

  cita.fecha = 10000 * a + 100 * m + d;

  if(arch.eof()) return -1;
  return buffDni;
}

bool operator<=(StCita &cita, StMedico *medicos){
  for(int i=0; medicos[i].codigo; i++){
    if(cita.codigoDelMedico == medicos[i].codigo){
      strcpy(cita.especialidad,medicos[i].especialidad);
      cita.tarifaPorConsulta = medicos[i].tarifaPoxConsulta;
      return true;
    }
  }
  return false;
}

void operator+=(StPaciente &paciente, const StCita &cita){
  paciente.citas[paciente.numeroDeCitas] = cita;
  paciente.numeroDeCitas++;
}

void operator++(StPaciente &paciente){
  for(int i=0; i<paciente.numeroDeCitas; i++)
    paciente.totalGastado += paciente.citas[i].tarifaPorConsulta;
}

void date(int fecha, int &d, int &m, int &a){
  d = fecha % 100;
  m = (fecha / 100) % 100;
  a = fecha / 10000;
}

void operator<<(ofstream &arch, const StPaciente &paciente){
  arch << setw(15) << "DNI";
  arch << setw(40) << "NOMBRE";
  arch << setw(15) << "TELEFONO";
  arch << endl;

  arch << setw(15) << paciente.dni;
  arch << setw(40) << paciente.nombre;
  arch << setw(15) << paciente.telefono;
  arch << endl;

  arch << "RELACION DE CITAS";
  arch << endl;

  arch << setw(10) << "No.";
  arch << setw(15) << "FECHA";
  arch << setw(20) << "CODIGO DEL MEDICO";
  arch << setw(25) << "ESPECIALIDAD";
  arch << setw(10) << "TARIFA";
  arch << endl;

  for(int i=0; i<paciente.numeroDeCitas; i++){
    int d, m, a;
    date(paciente.citas[i].fecha,d,m,a);

    arch << setw(4) << right << i + 1 << left << setw(6) << ")";
    arch << right << setfill('0') << setw(2) << d << "/" << setw(2) << m << "/" << setw(4) << a << setw(5) << setfill(' ') << "" << left;
    arch << setw(20) << paciente.citas[i].codigoDelMedico;
    arch << setw(25) << paciente.citas[i].especialidad;
    arch << setw(10) << paciente.citas[i].tarifaPorConsulta;
    arch << endl;
  }

  arch << "MONTO TOTAL GASTADO: ";
  arch << paciente.totalGastado;
  arch << endl;

  arch << endl;
}