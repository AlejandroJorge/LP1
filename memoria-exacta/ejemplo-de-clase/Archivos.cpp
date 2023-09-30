#include <iostream>
#include <fstream>
using namespace std;

void abrirArchvo(ifstream &arch, const char *nombreArch)
{
  arch.open(nombreArch, ios::in);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombreArch << endl;
  }
}
void abrirArchvo(ofstream &arch, const char *nombreArch)
{
  arch.open(nombreArch, ios::out);
  if (!arch.is_open())
  {
    cout << "No se pudo abrir " << nombreArch << endl;
  }
}