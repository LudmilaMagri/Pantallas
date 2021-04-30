/*
 ============================================================================
 Desarrollar una app que permita gestionar un array de Clientes
 Realizar
 * ALTAS
 * BAJAS
 * MODIFICACIONES

 La app debera permitir ordenar el array por Nombre del Cliente
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "Funciones.h"
#include "Contratacion.h"
#include "Informes.h"

#define PANT_LEN 100
#define CONTR_LEN 1000

int main(void) {

	setbuf(stdout, NULL);

	Pantalla arrayPantalla [PANT_LEN];
	Contratacion arrayContratacion [CONTR_LEN];
	int idPantalla = 0;
	int idContrataciones = 0;
	int opcion;
	int auxiliarIndice;
	int auxiliarIndiceCont;
	int auxiliarId;
	char auxiliarCuit [CUIT_LEN];
	int auxiliarIdContratacion;

	if (pan_inicializarArray(arrayPantalla, PANT_LEN) == 0)
	{
		printf ("Array inicializado correctamente.");
	}
	if (con_inicializarArray(arrayContratacion, CONTR_LEN)== 0)
	{
		printf ("\nArray inicializado correctamente.");
	}

	pan_altaArrayForzada(arrayPantalla, PANT_LEN, 0, &idPantalla, "Pantalla 1", "Defensa 123", 11.43, 0);
	pan_altaArrayForzada(arrayPantalla, PANT_LEN, 1, &idPantalla, "Pantalla 2", "Mitre 1343", 1.43, 1);
	pan_altaArrayForzada(arrayPantalla, PANT_LEN, 2, &idPantalla, "Pantalla 3", "Abdala 444", 10.232, 0);
	pan_altaArrayForzada(arrayPantalla, PANT_LEN, 3, &idPantalla, "Pantalla 4", "Zapiola 333", 1.43, 1);
	pan_altaArrayForzada(arrayPantalla, PANT_LEN, 4, &idPantalla, "Pantalla 5", "Brown 144", 10.232, 0);

	con_altaArrayForzada(arrayContratacion, CONTR_LEN, 0, &idContrataciones, 0, "Archivo1.mov", "22-2222222-3", 100);
	con_altaArrayForzada(arrayContratacion, CONTR_LEN, 1, &idContrataciones, 1, "Archivo2.mov", "21-3444343-3", 10);
	con_altaArrayForzada(arrayContratacion, CONTR_LEN, 2, &idContrataciones, 0, "Archivo2.mov", "21-3444343-3", 10);
	con_altaArrayForzada(arrayContratacion, CONTR_LEN, 3, &idContrataciones, 1, "Archivo3.mov", "13-1111111-3", 130);
	con_altaArrayForzada(arrayContratacion, CONTR_LEN, 4, &idContrataciones, 0, "Archivo3.mov", "13-1111111-3", 100);

	do
	{
		if (!utn_getNumeroInt(&opcion,
							"\n1.  Cargar una pantalla "
							"\n2.  Modificar datos de una pantalla "
							"\n3.  Baja de una pantalla "
							"\n4.  Contratar una publicidad"
							"\n5.  Modificar condiciones de publicacion"
							"\n6.  Cancelar contratacion"
							"\n7.  Consultar facturacion"
							"\n8.  Listar contrataciones"
							"\n9.  Listar pantallas"
							"\n10. Informar"
							"\n11. Salir",
							"\nError opcion invalida", 1, 11, 2))
		{
			switch (opcion)
			{
			case 1:
				auxiliarIndice = pan_getEmptyIndex(arrayPantalla, PANT_LEN);
				if (auxiliarIndice >= 0 &&pan_altaArray(arrayPantalla, PANT_LEN, auxiliarIndice, &idPantalla)==0)
					printf ("\nCarga realizada con exito\n");
				else
					printf ("\nNO HAY MAS LUGAR");
				break;
			case 2:
				pan_imprimirArray(arrayPantalla, PANT_LEN);
				if (utn_getNumeroInt(&auxiliarId,"\n Indique el ID de la pantalla a modificar", "\n Id invalido", 0, idPantalla, 2)==0)
				{
					auxiliarIndice=pan_buscarId(arrayPantalla, PANT_LEN, auxiliarId);
					if (auxiliarIndice>= 0 && pan_modificarArray(arrayPantalla, PANT_LEN, auxiliarIndice)== 0)
						printf ("\n Modificacion realizada con exito \n");
				}
				break;
			case 3:
					pan_imprimirArray(arrayPantalla, PANT_LEN);
					if (utn_getNumeroInt(&auxiliarId, "\nIndique el ID de la pantalla a eliminar", "\nID inválido", 0, idPantalla, 2)== 0 &&
						pan_buscarId(arrayPantalla, CANT_TARJ, auxiliarId) != -1)
					{
						auxiliarIndice = pan_buscarId(arrayPantalla, PANT_LEN, auxiliarId);
						if (auxiliarIndice >= 0 && pan_bajarArray(arrayPantalla, PANT_LEN, auxiliarIndice)==0)
							printf ("\nBaja realizada con exito\n");

					}
					break;
			case 4:
					auxiliarIndiceCont= con_getEmptyIndex(arrayContratacion, CONTR_LEN);
					if (auxiliarIndiceCont>= 0){
						pan_imprimirArray(arrayPantalla, PANT_LEN);
						if (utn_getNumeroInt(&auxiliarId, "\nIndique el ID de la pantalla que quiere publicar", "\nID inválido", 0, idPantalla, 2)== 0 &&
							pan_buscarId(arrayPantalla, PANT_LEN, auxiliarId)!= -1){

							con_altaArray(arrayContratacion, CONTR_LEN, auxiliarIndiceCont, &idContrataciones, auxiliarId);
						}
						else
							printf ("\nId inválido");
					}
					break;
					/*Se pedirá que se ingrese el cuit del cliente y se
					listaran todas las pantallas de video que el cliente tiene contratadas mostrando todos sus
					campos.*/
			case 5:
					if(utn_getCuit(auxiliarCuit, CUIT_LEN, "Ingrese CUIT", "Error", 3)==0 &&
						info_imprimirPantallasContratadasByCuit(arrayContratacion, CONTR_LEN, arrayPantalla, PANT_LEN, auxiliarCuit)==0)
					{
					if (utn_getNumeroInt(&auxiliarIdContratacion, "Ingrese Id de contratacion a modificar", "ERROR", 0, 10000, 3)==0)
					{
						auxiliarIndiceCont=con_buscarId(arrayContratacion, CONTR_LEN, auxiliarIdContratacion);
					}
						if (auxiliarIndiceCont!=-1)
						{
							con_modificarArray(arrayContratacion, CONTR_LEN, auxiliarIndiceCont);
						}
					}
					else
					{
						printf ("\n No se encontro el cuit ingresado");
					}
						break;

				/*
				Luego de ingresar el ID de la contratacion, se permitirá modificar la cantidad de días
				contratados para la misma*/
				break;
			case 6:
					if(utn_getCuit(auxiliarCuit, CUIT_LEN, "Ingrese CUIT", "Error", 3)==0 &&
						info_imprimirPantallasContratadasByCuit(arrayContratacion, CONTR_LEN, arrayPantalla, PANT_LEN, auxiliarCuit)==0)
					{
					if (utn_getNumeroInt(&auxiliarIdContratacion, "Ingrese Id de contratacion a eliminar", "ERROR", 0, 10000, 3)==0)
					{
						auxiliarIndiceCont=con_buscarId(arrayContratacion, CONTR_LEN, auxiliarIdContratacion);
					}
						if (auxiliarIndiceCont!=-1)
						{
							con_bajarArray(arrayContratacion, CONTR_LEN, auxiliarIndiceCont);
						}
					}
					else
					{
						printf ("\n No se encontro el cuit ingresado");
					}
				break;
				/*Consulta facturación: Se deberá ingresar el cuit del cliente y se deberá listar el importe
				a pagar por cada contratación.*/
			case 7:
					if (utn_getCuit(auxiliarCuit, CUIT_LEN, "\nIngrese Cuit", "\nERROR", 3)==0){

						info_imprimirContratacionesConImporte(arrayContratacion, CONTR_LEN, arrayPantalla, PANT_LEN, auxiliarCuit);
					}
				break;
				/*Listar contrataciones: Se deberán listar las contrataciones indicando nombre de la
				pantalla, nombre de video, cantidad de días y cuit de cliente.*/
			case 8:
				con_imprimirArray(arrayContratacion, CONTR_LEN);
				break;
			case 9:
				pan_imprimirArray(arrayPantalla, PANT_LEN);
				break;

			case 10:
				info_imprimirContratacionesPorCliente(arrayContratacion, CONTR_LEN, arrayPantalla, PANT_LEN, auxiliarCuit);

			}
		}
	}while (opcion !=11);

	return EXIT_SUCCESS;
}
