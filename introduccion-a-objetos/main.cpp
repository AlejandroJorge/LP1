#include <iostream>
#include <iomanip>
using namespace std;
#include "Rectangulo.h"

int main()
{

  Rectangulo miRectangulo = Rectangulo(5, 4);

  miRectangulo
      .setAltura(10)
      .setBase(8.5)
      .mostrarPropiedades()
      .setBase(3)
      .setAltura(8)
      .mostrarPropiedades();

  return 0;
}