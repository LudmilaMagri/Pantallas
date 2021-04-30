/*
 * utn.h
 *
 *  Created on: 24 abr. 2021
 *      Author: ludmi
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

#define NOMBRE_LEN 50
#define DIRECCION_LEN 100

#define TIPO_LCD 0
#define TIPO_LED 1

typedef struct
{
	char nombre [NOMBRE_LEN];
	char direccion [DIRECCION_LEN];
	float precio;
	int tipo;
	int isEmpty;
	int id;
}Pantalla;

int pan_imprimir (Pantalla* pElemento);
int pan_inicializarArray (Pantalla* array, int limite);
int pan_altaArray(Pantalla* array, int limite, int indice, int* id);
int pan_getEmptyIndex (Pantalla* array, int limite);
int pan_imprimirArray (Pantalla* array, int limite);
int pan_buscarId (Pantalla* array, int limite, int valorBuscado);
int pan_modificarArray (Pantalla* array, int limite, int indice);
int pan_bajarArray (Pantalla* array, int limite, int indice);
int pan_ordenarPorNombre (Pantalla* array, int limite);


int pan_altaArrayForzada (Pantalla* array, int limite, int indice, int* id, char* nombre, char* direccion, float precio, int tipo);

#endif /* PANTALLA_H_ */
