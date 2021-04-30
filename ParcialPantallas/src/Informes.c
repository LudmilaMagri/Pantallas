/*
 * Informes.c
 *
 *  Created on: 27 abr. 2021
 *      Author: ludmi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "Funciones.h"
#include "Contratacion.h"
#include "Informes.h"
#define CANT_CLIENTES 1000
static const char TXT_TIPOS [2][4] ={"LCD","LED"};

/*
 * \brief Actualiza los datos de ... en una posicion del array
 * \param array Array de... a ser actualizados
 * \param limite Limite del array de ..
 * \param indice Posicion a ser actualizado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_imprimirPantallasContratadasByCuit(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit)
{
	int retorno = -1;
	int i;
	int indiceArrayPantalla;
	int idPantalla;
	if (arrayContrataciones!= NULL && limiteContrataciones>=0 &&arrayPantallas != NULL && limiteContrataciones>=0 && auxCuit != NULL)
	{
		for (i=0; i<limiteContrataciones; i++)
		{
			if (arrayContrataciones[i].isEmpty==0)
			{
				if (strncmp(arrayContrataciones[i].cuit, auxCuit, CUIT_LEN) ==0)//comparo a ver si son iguales los cuits que ingreso el usuario
				{
					retorno = 0;
					idPantalla = arrayContrataciones[i].idPantalla;  //del array de contrataciones obtengo el id de esa pantalla
					indiceArrayPantalla= pan_buscarId(arrayPantallas, limiteContrataciones, idPantalla); //busco en el array de pantallas el indice donde estan los datos de esas pant
					printf ("\n ID CONT: %d - NOMBRE ARCHIVO: %s - CUIT: %s - DIAS: %d - ID PANT: %d - ", arrayContrataciones[i].idContratacion, arrayContrataciones[i].nombreArchivo,arrayContrataciones[i].cuit, arrayContrataciones[i].dias, arrayContrataciones[i].idPantalla);
					printf ("IDPANT: %d - NOMBRE PANTALLA: %s - DIRECCION: %s - PRECIO: %.2f - TIPO: %s", arrayPantallas[indiceArrayPantalla].id, arrayPantallas[indiceArrayPantalla].nombre, arrayPantallas[indiceArrayPantalla].direccion, arrayPantallas[indiceArrayPantalla].precio, TXT_TIPOS[arrayPantallas[indiceArrayPantalla].tipo]);
				}
			}
		}
	}
	return retorno;
}

int info_imprimirContratacionesConImporte(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit)
{
	int retorno = -1;
	int i;
	int indiceArrayPantalla;
	int idPantalla;
	float auxImporte;

	if (arrayContrataciones!= NULL && limiteContrataciones>=0 &&arrayPantallas != NULL && limiteContrataciones>=0 && auxCuit != NULL)
	{
		for (i=0; i<limiteContrataciones; i++)
		{
			if (arrayContrataciones[i].isEmpty==0)
			{
				if (strncmp(arrayContrataciones[i].cuit, auxCuit, CUIT_LEN) ==0)//comparo a ver si son iguales los cuits que ingreso el usuario
				{
					retorno = 0;
					idPantalla = arrayContrataciones[i].idPantalla;  //del array de contrataciones obtengo el id de esa pantalla
					indiceArrayPantalla= pan_buscarId(arrayPantallas, limiteContrataciones, idPantalla); //busco en el array de pantallas el indice donde estan los datos de esas pant
					auxImporte = arrayContrataciones[i].dias * arrayPantallas[indiceArrayPantalla].precio;
					printf ("\n ID CONT: %d - NOMBRE ARCHIVO: %s - CUIT: %s - DIAS: %d - ID PANT: %d - IMPORTE: %.2f", arrayContrataciones[i].idContratacion, arrayContrataciones[i].nombreArchivo,arrayContrataciones[i].cuit, arrayContrataciones[i].dias, arrayContrataciones[i].idPantalla, auxImporte);
				}
			}
		}
	}
	return retorno;
}
int info_imprimirContratacionesPorCliente(Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit)
{
	int retorno = -1;
	char listaCuit[CANT_CLIENTES][CUIT_LEN];
	int i;
	int j;
	int flagCuit;
	int indiceCuitLibre =0;
	float auxDeuda;
	float deudaMax;
	int indiceClienteDeudaMax;
	//lista de no repetidos
	/*for (i=0;i<CANT_CLIENTES;i++)
	{
		strncpy(listaCuit[i],"",CUIT_LEN); //cargo un vacio para no tener basura
	}*/

	for (i=0; i<limiteContrataciones;i++)
	{
		flagCuit = 0;
		if (arrayContrataciones[i].isEmpty==0) //si no esta vacio, lo analizo. Si esta vacio vuelvo al for
		{
			for (j=0; j<indiceCuitLibre;j++) //recorro con la j las dist posiciones de la lista de cuits
			{
				if (strncmp (arrayContrataciones[i].cuit, listaCuit[j], CUIT_LEN)==0) //quiere decir que esta
				{
					flagCuit = 1;; //si es igual entra aca y no lo agrega a la lista
					break;
				}
			}
			if (flagCuit ==0) //cada vez que agrego un cuit
			{
				strncpy(listaCuit[indiceCuitLibre],arrayContrataciones[i].cuit, CUIT_LEN);
				indiceCuitLibre++;
			}
		}
	}
	for(j=0; j<indiceCuitLibre;j++)
	{
		printf ("\n El cliente con cuit %s\n\n", listaCuit[j]);
		info_imprimirContratacionesConImporte(arrayContrataciones, limiteContrataciones, arrayPantallas, limitePantalla, listaCuit [j]);
	}


	for(j=0; j<indiceCuitLibre;j++)
	{
		info_calcularDeudaCliente(arrayContrataciones, limiteContrataciones, arrayPantallas, limitePantalla, listaCuit[j], &auxDeuda);
		if (i ==0 || auxDeuda> deudaMax)
		{
			deudaMax = auxDeuda;
			indiceClienteDeudaMax = j;
		}
	}
	printf ("\n El cliente con mas deuda es: %s - DEBE: %.2f\n\n", listaCuit[indiceClienteDeudaMax], deudaMax);
	return retorno;
}

/*
 * ME GENERO UN FOR PARA IMPRIMIR SOLO EL CUIT PARA VER SI SALIO TODO BIEN
	for(j=0; j<indiceCuitLibre;j++)
	{
		printf("\nCLIENTE - CUIT %s", listaCuit[j]);
	}
*/


int info_calcularDeudaCliente (Contratacion* arrayContrataciones, int limiteContrataciones, Pantalla* arrayPantallas, int limitePantalla, char* auxCuit, float* deuda)
{
	int retorno = -1;
	int i;
	int indiceArrayPantalla;
	int idPantalla;
	float auxDeuda=0;

	if (arrayContrataciones!= NULL && limiteContrataciones>=0 &&arrayPantallas != NULL && limiteContrataciones>=0 && auxCuit != NULL)
	{
		for (i=0; i<limiteContrataciones; i++)
		{
			if (arrayContrataciones[i].isEmpty==0)
			{
				if (strncmp(arrayContrataciones[i].cuit, auxCuit, CUIT_LEN) ==0)//comparo a ver si son iguales los cuits que ingreso el usuario
				{
					idPantalla = arrayContrataciones[i].idPantalla;  //del array de contrataciones obtengo el id de esa pantalla
					indiceArrayPantalla= pan_buscarId(arrayPantallas, limiteContrataciones, idPantalla); //busco en el array de pantallas el indice donde estan los datos de esas pant
					auxDeuda = auxDeuda + (arrayContrataciones[i].dias * arrayPantallas[indiceArrayPantalla].precio);
				}
			}
		}
		retorno = 0;
		*deuda=auxDeuda;
	}
	return retorno;
}
