/*
 * utn.c
 *
 *  Created on: 24 abr. 2021
 *      Author: ludmi
 */

#include "Contratacion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"

/*
 * \brief Imprime los datos de..
 * \param pElemento Puntero al elemento que se busca imprimir
 * \param limite Limite del array de ..
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_imprimir (Contratacion* pElemento)
{
	int retorno = -1;
	if (pElemento != NULL && pElemento->isEmpty == 0){
		retorno = 0;
		printf ("\n IdContr: %d - Nombre de video: %s -CUIT: %s - IdPantalla: %d - Cantidad dias: %d ",
				pElemento->idContratacion, pElemento->nombreArchivo, pElemento->cuit, pElemento->idPantalla, pElemento->dias);
	}
	return retorno;
}
/*
 * \brief Imprime el array de...
 * \param array Array de ... a ser actualizado
 * \param limite Limite del array de ..
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_imprimirArray (Contratacion* array, int limite)
{
	int retorno = -1;
	int i;
	if (array != NULL && limite >0){
		retorno = 0;
		for (i=0; i<limite; i++){
			con_imprimir(&array [i]);
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
int con_inicializarArray (Contratacion* array, int limite)
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

/*Se listaran todas las pantallas y se le pedirá al usuario que
elija la pantalla donde se quiere publicar, ingresando su ID. Luego se pedirán los datos
asociados a la publicidad: cuit del cliente, cantidad de días que dura la publicación y
nombre del archivo de video (p.ej. Video1.avi).*/

/*
 * \brief Da de alta un ... en una posicion del array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \param indice Posicion a ser actualizado
 * \param id Identificador a ser asignado al ...
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_altaArray(Contratacion* array, int limite, int indice, int* idContratacion, int idPantalla)
{
	int retorno = -1;
	Contratacion bufferCont;
	if (array != NULL && limite>0 && indice<limite && indice >= 0 && idContratacion != NULL){
		if (utn_getDescripcion(bufferCont.nombreArchivo,NOMBRE_LEN, "\nIngrese nombre", "\nError", 3)==0 &&
			utn_getCuit(bufferCont.cuit, CUIT_LEN, "\nIngrese cuit:", "\nError", 3) ==0 &&
			utn_getNumeroInt(&bufferCont.dias, "Ingrese cantidad de dias", "Error", 0, 10000, 3)==0)
		{
			bufferCont.idContratacion =*idContratacion;
			bufferCont.idPantalla = idPantalla;
			bufferCont.isEmpty = 0;
			array[indice] = bufferCont;
			(*idContratacion)++;
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
int con_modificarArray (Contratacion* array, int limite, int indice)
{
	int retorno = -1;
	int dias;
	if (array!=NULL && limite>0 && indice<limite && indice>=0 && array[indice].isEmpty ==0){
		if (utn_getNumeroInt(&dias, "Dias?", "Error", 1, 365, 3)==0){
				retorno=0;
				array[indice].dias = dias;
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
int con_bajarArray (Contratacion* array, int limite, int indice)
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
int con_buscarId (Contratacion* array, int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite>0 && valorBuscado>=0){
		for (i=0; i<limite; i++){
			if (array[i].idContratacion == valorBuscado){
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
int con_getEmptyIndex (Contratacion* array, int limite)
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
 * \return Retorna el
 */
int con_ordenarPorNombre (Contratacion* array, int limite)
{
	int respuesta = -1;
	int i;
	Contratacion buffer;
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
				if (strncmp(array[i].nombreArchivo, array[i+1].nombreArchivo, NOMBRE_LEN) >0)
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
int con_ordenarPorNombreAltura (Contratacion* array, int limite)
{
	int respuesta = -1;
		int i;
		Contratacion buffer;
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
					if (strncmp(array[i].nombreArchivo, array[i+1].nombreArchivo, NOMBRE_LEN) >0 ||
						(strncmp(array[i].nombreArchivo, array[i+1].nombreArchivo, NOMBRE_LEN) ==0 &&
						array[i].dias > array [i+1].dias))
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
int con_altaArrayForzada (Contratacion* array, int limite, int indice, int* idContratacion,
							int idPantalla,char* nombre, char* cuit,
							int dias)
{
	int respuesta = -1;
	Contratacion bufferContr;

	if (array != NULL && limite >0 && indice <limite && indice >= 0 && idContratacion != NULL)
	{
		strncpy(bufferContr.nombreArchivo, nombre, NOMBRE_LEN);
		strncpy(bufferContr.cuit, cuit, CUIT_LEN);
		bufferContr.dias = dias;
		bufferContr.idContratacion = *idContratacion;
		bufferContr.idPantalla =idPantalla;
		bufferContr.isEmpty=0;
		array[indice] = bufferContr;
		(*idContratacion)++;
		respuesta = 0;
	}
	return respuesta;
}


