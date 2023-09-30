#include <iostream>
#include <fstream>
using namespace std;

void imprimenumero(void *ptrNum, ofstream &arch)
{
  arch << "Numero: " << *(int *)ptrNum << endl;
}

int cmpnumero(const void *ptrNumA, const void *ptrNumB)
{
  int a = **(int **)ptrNumA, b = **(int **)ptrNumB;
  return b - a;
}

void *leenumero(ifstream &arch)
{
  int num;
  arch >> num;
  if (arch.eof())
    return nullptr;
  return new int(num);
}