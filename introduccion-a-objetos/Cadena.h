#ifndef CADENA_H
#define CADENA_H

class Cadena
{
private:
  char *cad;
  int longitud;

public:
  Cadena();
  ~Cadena();
  int getLongitud() const;
  void setCad(const char *cad);
  void getCad(char *cad) const;
  void imprimir() const;
  void copia(const class Cadena &);
};

#endif /*CADENA_H*/