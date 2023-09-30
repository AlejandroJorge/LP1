#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Utilidades.h"
#define BUFFSIZE 300

void estructurasParaLosLibros_CargaDeDatos(char **&codigo, char **&titulo, int *&cantEnBib, double *&precio)
{
  // archivo
  ifstream arch;
  abrir(arch, "Libros.csv");

  // buffers
  char *codigoBuff[BUFFSIZE]{};
  char *tituloBuff[BUFFSIZE]{};
  int cantEnBibBuff[BUFFSIZE]{};
  double precioBuff[BUFFSIZE]{};
  int size = 0;

  // lectura
  char *codigoL, *tituloL;
  int cantL;
  double precioL;
  while (true)
  {
    codigoL = leerCadena(arch, ',');
    // KC34197,Las_demoliciones_de_Paris,Zkenia/Chung/Zuniga,2014,15,294.26
    if (arch.eof())
    {
      delete codigoL;
      break;
    }
    tituloL = leerCadena(arch, ',');
    while (arch.get() != ',')
      ;
    while (arch.get() != ',')
      ;
    arch >> cantL;
    arch.get();
    arch >> precioL >> ws;

    codigoBuff[size] = codigoL;
    tituloBuff[size] = tituloL;
    cantEnBibBuff[size] = cantL;
    precioBuff[size] = precioL;
    size++;
  }
  size++;

  // memoria
  codigo = new char *[size];
  titulo = new char *[size];
  cantEnBib = new int[size];
  precio = new double[size];

  // copiado
  for (int i = 0; i < size; i++)
  {
    codigo[i] = codigoBuff[i];
    titulo[i] = tituloBuff[i];
    cantEnBib[i] = cantEnBibBuff[i];
    precio[i] = precioBuff[i];
  }
  codigo[size - 1] = nullptr;
}

void estructurasParaLosLibros_Reporte(char **codigo, char **titulo, int *cantEnBib, double *precio)
{
  ofstream arch;
  abrir(arch, "ReporteLibros.txt");
  arch << fixed << left;
  arch.precision(2);

  arch << setw(20) << "CODIGO";
  arch << setw(50) << "TITULO";
  arch << setw(10) << "CANTIDAD";
  arch << setw(10) << "PRECIO";
  arch << endl;

  for (int i = 0; codigo[i]; i++)
  {
    arch << setw(20) << codigo[i];
    arch << setw(50) << titulo[i];
    arch << setw(10) << cantEnBib[i];
    arch << setw(10) << precio[i];
    arch << endl;
  }
}

void usuariosDeLaBiblioteca_CargaDeDatos(int *&carne, char *&tipo, char **&nombre)
{
  // archivo
  ifstream arch;
  abrir(arch, "Usuarios.csv");

  // buffers
  int carneBuff[BUFFSIZE]{};
  char tipoBuff[BUFFSIZE]{};
  char *nombreBuff[BUFFSIZE]{};
  int size = 0;

  // lectura
  int carneLeido;
  char tipoLeido, *nombreLeido;
  while (true)
  {
    // 17750908E,Hernandez_Barrios_Emilio
    arch >> carneLeido;
    if (arch.eof())
      break;
    tipoLeido = arch.get();
    arch.get();
    nombreLeido = leerCadena(arch, '\n');

    carneBuff[size] = carneLeido;
    nombreBuff[size] = nombreLeido;
    tipoBuff[size] = tipoLeido;
    size++;
  }
  // memoria
  carne = new int[size];
  nombre = new char *[size];
  tipo = new char[size];

  // copiado
  for (int i = 0; i < size; i++)
  {
    carne[i] = carneBuff[i];
    nombre[i] = nombreBuff[i];
    tipo[i] = tipoBuff[i];
  }
}

void usuariosDeLaBiblioteca_Reporte(int *carne, char *tipo, char **nombre)
{
  ofstream arch;
  abrir(arch, "ReporteUsuarios.txt");
  arch << fixed << left;
  arch.precision(2);

  arch << setw(20) << "CARNE";
  arch << setw(10) << "TIPO";
  arch << setw(50) << "NOMBRE";
  arch << endl;

  for (int i = 0; carne[i]; i++)
  {
    arch << setw(20) << carne[i];
    arch << setw(10) << tipo[i];
    arch << setw(50) << nombre[i];
    arch << endl;
  }
}

void librosYUsuariosInhabilitados_Reporte(char **codigo, char **titulo, int *&cantEnBib, double *precio, int *carne, char *tipo, char **nombre)
{
  int *carneDeuda, *cantDeuda;
  char **nombreDeuda;
  double *montoDeuda;

  double *montoPorDeuda;

  ofstream arch;
  abrir(arch, "ReporteFinal.txt");
  arch << fixed << left;
  arch.precision(2);

  imprimirLinea(arch, '=');
  arch << setw(30) << ""
       << "ESTUDIANTES DEUDORES" << endl;
  imprimirLinea(arch, '-');
  cargarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, codigo, precio, cantEnBib, carne, nombre, montoPorDeuda, 'E');
  imprimirReporte(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, arch);
  liberarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda);

  imprimirLinea(arch, '=');
  arch << setw(30) << ""
       << "DOCENTES DEUDORES" << endl;
  imprimirLinea(arch, '-');
  cargarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, codigo, precio, cantEnBib, carne, nombre, montoPorDeuda, 'D');
  imprimirReporte(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, arch);
  liberarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda);

  imprimirLinea(arch, '=');
  arch << setw(30) << ""
       << "ADMINISTRATIVOS DEUDORES" << endl;
  imprimirLinea(arch, '-');
  cargarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, codigo, precio, cantEnBib, carne, nombre, montoPorDeuda, 'A');
  imprimirReporte(carneDeuda, cantDeuda, nombreDeuda, montoDeuda, arch);
  liberarDatos(carneDeuda, cantDeuda, nombreDeuda, montoDeuda);

  imprimirLinea(arch, '=');
  arch << setw(30) << ""
       << "STOCK DE LIBROS DE LA BIBLIOTECA" << endl;
  imprimirLinea(arch, '-');
  imprimirStockLibros(codigo, titulo, cantEnBib, precio, montoPorDeuda);
}
