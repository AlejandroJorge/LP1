#include <iostream>
#include <fstream>
using namespace std;
#include "../headers/Estructuras.h"
#include "../headers/funciones.h"

int main() {

    StMedico medicos[100]{};
    int cMed = 0;
    StPaciente pacientes[100]{};
    int cPac = 0;
    StCita cita;

    ifstream aMed("MedicosLab3.txt",ios::in);
    ifstream aPac("PacientesLab3.txt",ios::in);
    ifstream aCit("ConsultasLab3.txt",ios::in);
    ofstream aRep("ReporteLab3.txt",ios::out);

    while(aMed>>medicos[cMed]) cMed++;

    while(aPac>>pacientes[cPac]) cPac++;

    int dniCita;
    while(true){
        dniCita = aCit >> cita;
        if(dniCita==-1) break;

        cita <= medicos;
        for(int i=0; i<cPac; i++)
            if(pacientes[i].dni==dniCita)
                pacientes[i]+=cita;
    }

    aRep << fixed << left;
    aRep.precision(2);

    for(int i=0; i<cPac; i++){
        ++pacientes[i];
        aRep << pacientes[i];
    } 

    return 0;
}
