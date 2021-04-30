/*
 * Informes.h
 *
 *  Created on: 27 abr. 2021
 *      Author: ludmi
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int info_imprimirPantallasContratadasByCuit(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit);

int info_imprimirContratacionesConImporte(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit);

int info_imprimirContratacionesPorCliente(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit);

int info_calcularDeudaCliente (Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit, float* deuda);

#endif /* INFORMES_H_ */
