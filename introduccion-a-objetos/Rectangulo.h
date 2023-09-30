#ifndef RECTANGULO_H
#define RECTANGULO_H

class Rectangulo
{
private:
  double base;
  double altura;

public:
  Rectangulo(double altura, double base);
  double getBase();
  double getAltura();
  double area();
  double perimetro();
  Rectangulo &setBase(double base);
  Rectangulo &setAltura(double altura);
  Rectangulo &mostrarPropiedades();
};

#endif /*RECTANGULO_H*/