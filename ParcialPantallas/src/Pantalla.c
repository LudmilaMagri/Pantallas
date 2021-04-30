/*
 * utn.c
 *
 *  Created on: 24 abr. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "Funciones.h"

static const char TXT_TIPOS [2][4] ={"LCD","LED"};

/*
 * \brief Imprime los datos de..
 * \param pElemento Puntero al elemento que se busca imprimir
 * \param limite Limite del array de ..
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_imprimir (Pantalla* pElemento)
{
	int retorno = -1;
	if (pElemento != NULL && pElemento->isEmpty == 0){
		retorno = 0;
		printf ("\n Id: %d - Nombre: %s -Direccion: %s - Precio: %.2f  - Tipo: %s", pElemento->id, pElemento->nombre, pElemento->direccion, pElemento->precio, TXT_TIPOS[pElemento->tipo]);
	}
	return retorno;
}
/*
 * \brief Imprime el array de...
 * \param array Array de ... a ser actualizado
 * \param limite Limite del array de ..
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_imprimirArray (Pantalla* array, int limite)
{
	int retorno = -1;
	int i;
	if (array != NULL && limite >0){
		retorno = 0;
		for (i=0; i<limite; i++)
		{
			pan_imprimir(&array [i]);
		}
	}
	return retorno;
}
/*
 * \brief Inicializa el array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_inicializarArray (Pantalla* array, int limite)
{
	int retorno = -1;
	int i;
	if(array != NULL && limite>0){
		retorno = 0;
		for (i=0; i<limite; i++){
			array [i].isEmpty = 1;
		}
	}
	return retorno;
}
/*
 * \brief Da de alta un ... en una posicion del array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \param indice Posicion a ser actualizado
 * \param id Identificador a ser asignado al ...
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_altaArray(Pantalla* array, int limite, int indice, int* id)
{
	int retorno = -1;
	Pantalla bufferPant;
	if (array != NULL && limite>0 && indice<limite && indice >= 0 && id != NULL){
		if (utn_getNombre(bufferPant.nombre,NOMBRE_LEN, "\nIngrese nombre", "\nError", 3)==0 &&
			utn_getDireccion(bufferPant.direccion, DIRECCION_LEN, "\nDireccion?:", "\nError", 3) ==0 &&
			utn_getNumeroFlotante(&bufferPant.precio, "\nPrecio?", "\nError", 0, 100000, 3)==0 &&
			utn_getNumeroInt(&bufferPant.tipo, "Tipo?", "Error", 0, 3, 3)==0)
		{
			bufferPant.id =*id;
			bufferPant.isEmpty = 0;
			array[indice] = bufferPant;
			(*id)++;
			retorno = 0;
		}
	}

	return retorno;
}
/*
 * \brief Actualiza los datos de ... en una posicion del array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \param indice Posicion a ser actualizado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_modificarArray (Pantalla* array, int limite, int indice)
{
	int retorno = -1;
	Pantalla bufferPant;
	if (array!=NULL && limite>0 && indice<limite && indice>=0 && array[indice].isEmpty ==0){
		if (utn_getNombre(bufferPant.nombre,NOMBRE_LEN, "\nIngrese nombre", "\nError", 3)==0 &&
			utn_getDireccion(bufferPant.direccion, DIRECCION_LEN, "\nIngrese direccion", "\nError", 3) ==0 &&
			utn_getNumeroFlotante(&bufferPant.precio, "\nPrecio?", "\nError", 0, 100000, 3)==0 &&
			utn_getNumeroInt(&bufferPant.tipo, "TIPO?", "ERROR", 0, 3, 3)==0)
		{
			bufferPant.id = array[indice].id;
			bufferPant.isEmpty = 0;
			array[indice] = bufferPant;
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief Actualiza una posicion del array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \param indice Posicion a ser actualizado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int pan_bajarArray (Pantalla* array, int limite, int indice)
{
	int retorno = -1;

	if (array != NULL && limite >0 && indice <limite && indice >= 0 && array[indice].isEmpty ==0){
		array[indice].isEmpty = 1;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Busca un ID en un array y devuelve la posicion en que se encuentra
 * \param array Array de...
 * \param limite Limite del array de ..
 * \param valorBuscado Valor que ingreso el usuario a ser buscado
 * \return Retorna -1 (ERROR) o la posicion del indice en la que se encuentre el id (EXITO)
 */
int pan_buscarId (Pantalla* array, int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite>0 && valorBuscado>=0){
		for (i=0; i<limite; i++){
			if (array[i].id == valorBuscado){
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}
/*
 * \brief Buscar la primera posicion que este vacia
 * \param array Array de...
 * \param limite Limite del array de ..
 * \return Retorna -1 (ERROR) o el indice de la posicion vacia
 */
int pan_getEmptyIndex (Pantalla* array, int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite>0){
		respuesta = 0;
		for (i=0; i<limite; i++){
			if (array[i].isEmpty == 1){
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}

/*
 * \brief Ordenar el array de ... por ...
 * \param array Array de ..
 * \param limite Limite del array de ..
 * \return Retorna
 */
int pan_ordenarPorNombre (Pantalla* array, int limite)
{
	int respuesta = -1;
	int i;
	Pantalla buffer;
	int flagSwap;
	if(array != NULL && limite>0)
	{
		do
		{
			flagSwap = 0;
			for (i=0; i<limite-1; i++)
			{
				if(array [i].isEmpty || array[i+1].isEmpty)
				{
					continue;
				}
				if (strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) >0)
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1] = buffer;
				}
			}
			limite--;
		}while (flagSwap);
	}
	return respuesta;
}
/*
 * \brief Ordenar el array de ... por ... y por ..
 * \param array Array de ..
 * \param limite Limite del array de ..
 * \return Retorna el
 */
int pan_ordenarPorNombreAltura (Pantalla* array, int limite)
{
	int respuesta = -1;
		int i;
		Pantalla buffer;
		int flagSwap;
		if(array != NULL && limite>0)
		{
			do
			{
				flagSwap = 0;
				for (i=0; i<limite-1; i++)
				{
					if(array [i].isEmpty || array[i+1].isEmpty)
					{
						continue;
					}
					if (strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) >0 ||
						(strncmp(array[i].nombre, array[i+1].nombre, NOMBRE_LEN) ==0 &&
						array[i].precio > array [i+1].precio))
					{
						flagSwap = 1;
						buffer = array[i];
						array[i] = array[i+1];
						array[i+1] = buffer;
					}
				}
				limite--;
			}while (flagSwap);
		}
		return respuesta;
}

int pan_altaArrayForzada (Pantalla* array, int limite, int indice, int* id, char* nombre, char* direccion, float precio, int tipo)
{
	int respuesta = -1;
	Pantalla bufferPantalla;

	if (array != NULL && limite >0 && indice <limite && indice >= 0 && id != NULL)
	{
		strncpy(bufferPantalla.direccion, direccion, DIRECCION_LEN);
		strncpy(bufferPantalla.nombre, nombre, NOMBRE_LEN);
		bufferPantalla.precio = precio;
		bufferPantalla.tipo = tipo;
		respuesta = 0;
		bufferPantalla.id = *id;
		bufferPantalla.isEmpty=0;
		array[indice] = bufferPantalla;
		(*id)++;
	}
	return respuesta;
}





