#ifndef RECTANGULO_H
#define RECTANGULO_H

class Rectangulo
{
private:
  double base;
  double altura;
  char *nombre;

public:
  Rectangulo();
  Rectangulo(double altura, double base, const char *nombre);
  Rectangulo(const char *nombre);
  ~Rectangulo();
  double getBase();
  double getAltura();
  void getNombre(char *nom) const;
  void setNombre(const char *nombre);
  double area();
  double perimetro();
  Rectangulo &setBase(double base);
  Rectangulo &setAltura(double altura);
  Rectangulo &mostrarPropiedades();
};

void f();

#endif /*RECTANGULO_H*/