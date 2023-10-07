#ifndef PREGUNTA3_H
#define PREGUNTA3_H

void CargaCursos(int *alumnosCod, void *&alumnoVeces, const char *nomArch);

void ActualizaVeces(void *alumnoVeces);

void ImprimeAlumno(void *alumnoVeces);

int buscarAlumno(int *codigos, int codigo);

void agregarCurso(void *almVez, void *curso, int &cantidad);

void inicializar(int *alumnosCod, void *&alumnoVeces);

void *crearAlumnoVez(int codigo);

void reducirMemoria(void **arrAlm, int *cantidad);

int calcOcurrenciasPrevias(void *cursos, void *curso);

void shift(void *cursos, int idx);

#endif /*PREGUNTA3_H*/