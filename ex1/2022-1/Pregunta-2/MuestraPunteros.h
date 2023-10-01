/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MuestraPunteros.h
 * Author: cueva
 *
 * Created on 10 de mayo de 2022, 06:54 PM
 */

#ifndef MUESTRAPUNTEROS_H
#define MUESTRAPUNTEROS_H
void imprimepedidos(void *);
void imprimeproductos(void *);
void imprimerepfinal(void *);

void imprimereporte(void *cli);
void imprimirPedidos(void *ped, ofstream &ach);
void impFecha(int fecha, ofstream &ach);

#endif /* MUESTRAPUNTEROS_H */
