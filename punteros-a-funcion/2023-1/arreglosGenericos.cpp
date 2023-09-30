#include <iostream>
#include <fstream>
using namespace std;

void llenarArreglo(void *arr, const char *nomArch)
{
  ifstream arch(nomArch, ios::in);
  if (!arch)
  {
    cout << "No se pudo abrir " << nomArch << endl;
    exit(1);
  }
  void *elemento;
  while (true)
  {
    }
}