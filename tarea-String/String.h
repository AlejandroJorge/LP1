#ifndef STRING_H
#define STRING_H

class String
{
private:
  char *content;
  int length;

public:
  String();
  String(const char *content);
  String(const class String &anotherString);
  ~String();
};

#endif /*STRING_H*/