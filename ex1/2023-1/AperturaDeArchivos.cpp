#include <iostream>
#include <fstream>
using namespace std;

void AperturaDeUnArchivoDeTextosParaLeer(ifstream &archivo,
                                         const char *nombreDelArchivo)
{
  archivo.open(nombreDelArchivo, ios::in);
  if (!archivo)
  {
    cout << "No se pudo abrir " << nombreDelArchivo << endl;
    exit(1);
  }
}

void AperturaDeUnArchivoDeTextosParaEscribir(ofstream &archivo,
                                             const char *nombreDelArchivo)
{

  archivo.open(nombreDelArchivo, ios::out);
  if (!archivo)
  {
    cout << "No se pudo abrir " << nombreDelArchivo << endl;
    exit(1);
  }
}