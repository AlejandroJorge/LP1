#include <iostream>
using namespace std;

void mostrarNumero(const void *elem)
{
  cout << *(int *)elem << endl;
}

int cmpNumeros(const void *ptrA, const void *ptrB)
{
  void *elemA = *(void **)ptrA;
  void *elemB = *(void **)ptrB;

  int a = *(int *)elemA;
  int b = *(int *)elemB;
  return a - b;
}

int main()
{

  int N = 100;
  void *arr[N];
  for (int i = 0; i < N; i++)
    arr[i] = new int((i + 17) * (151 - i) * 31 % 100);

  for (int i = 0; i < N; i++)
    cout << "Elemento " << i << ": " << *(int *)arr[i] << endl;

  qsort(arr, N, sizeof(void *), cmpNumeros);

  for (int i = 0; i < N; i++)
    cout << "Elemento " << i << ": " << *(int *)arr[i] << endl;

  return 0;
}