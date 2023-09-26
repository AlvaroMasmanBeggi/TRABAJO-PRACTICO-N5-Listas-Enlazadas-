#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//declaro los tipo de datos estructura que voy a usar//

struct BaseDeSensores
{
	char MarcaSensor[MAX];
	char TipoSensor[MAX];
	char UnidadMedida[MAX];
}SensorTipo[2];

struct Mediciones
{
	char Fecha[15];
	char Hora[15];
	struct BaseDeSensores Sensor;
	float ValorMedido;
	char Comentarios[150];
	struct Mediciones *Siguiente;
	struct Mediciones *Anterior;
};

//declaro las funciones que voy a usar//

struct Mediciones *Agregar_Medicion(struct Mediciones *UltimoNodo);

void Mostrar_Todas_Mediciones(struct Mediciones *PrimerNodo);

void Eliminar_Medicion(struct Mediciones **PrimerNodo, struct Mediciones **UltimoNodo);

void CargarBaseDeDatos(void);

void MostrarBaseDeDatos(void);

void Mostrar_Una_Medicion(struct Mediciones *Actual);

void BuscarPorSensor(struct Mediciones *PrimerNodo);

void BuscarPorValorMedido(struct Mediciones *PrimerNodo);

void OrdenarMediciones(struct Mediciones *PrimerNodo);

void GuardarEnArchivo(struct Mediciones *PrimerNodo, FILE *Archivo);

struct Mediciones *LeerDesdeArchivo(FILE *Archivo);

struct Mediciones *EncontrarUltimoNodo(struct Mediciones *PrimerNodo);


void ImprimirAlReves(struct Mediciones *UltimoNodo);


//programa principal//

int main(int argc, char *argv[]) 
{
	
	//declaro los datos que vamos a usar//
	
	struct Mediciones *NodoInicial=NULL;
	
	struct Mediciones *NodoFinal=NULL;
	
	struct Mediciones *NodoTemporal=NULL;
	
	
	
	int seleccionador=0, salir=0, Tipo_De_Busqueda=0, Decision_Inicial;
	
	FILE *ArchivoDeMediciones;
	
	//cargo el sistema con la base de datos que tenemos de los sensores//
	
	CargarBaseDeDatos();
	
	//verificamos antes de entrar al programa que el archivos tenga datos//
	
	NodoInicial=LeerDesdeArchivo(ArchivoDeMediciones);
	
	if(NodoInicial!=NULL)
	{
		NodoTemporal=NodoInicial;
		NodoFinal=EncontrarUltimoNodo(NodoTemporal); //reubico el nodo final de la lista que rescate del archivo//
		
		printf("\nSE ENCONTRO UNA BASE CON MEDICIONES: \n");
		
		NodoTemporal=NodoInicial;
		Mostrar_Todas_Mediciones(NodoTemporal);
		
		printf("\n¿DESEA RECUPERARLA...?\n1-SI\n2-NO\n");
		scanf("%d",&Decision_Inicial);
	}
	else
	{
		printf("\nLA BASE DE DATOS ESTA VACIA\n");
	}
	
	if(Decision_Inicial==2)
	{
		free(NodoInicial);
		free(NodoFinal);
		NodoInicial=NULL;
		NodoFinal=NULL;
	}
	
	system("pause");
	system("cls");
	
	
	//ingreso al menu y al programa//
	
	
	while(salir!=1)
	{
		printf("\n\nMENU PRINCIPAL\n\n1-Agregar Nueva Medicion\n2-Mostrar todas las Mediciones\n3-Eliminar una Medicion\n4-Buscar Medicion\n5-Ordenar Mediciones Segun Fecha\n6-Guardar En Un Archivo\n7-Mostrar Mediciones desde el final hacia adelante\n8-Salir\n");
		scanf("%d",&seleccionador);
		switch(seleccionador)
		{
			case 1: 
					NodoTemporal=Agregar_Medicion(NodoFinal);
					
					if(NodoInicial==NULL)
					{
						NodoInicial=NodoTemporal;
						NodoInicial->Siguiente=NULL;
						NodoInicial->Anterior=NULL;
					}
					else
					{
						NodoFinal->Siguiente = NodoTemporal;
						NodoTemporal->Siguiente = NULL;
						NodoTemporal->Anterior = NodoFinal;
					}
					
					NodoFinal=NodoTemporal;
					
					system("cls");
					break;
					
			case 2: 
					NodoTemporal=NodoInicial;
					Mostrar_Todas_Mediciones(NodoTemporal);
					printf("\n\n");
					system("pause");
					system("cls");
					break;
					
			case 3: 
					Eliminar_Medicion(&NodoInicial,&NodoFinal);
					printf("\n\n");
					system("pause");
					system("cls");
					break;
					
			case 4: 
					printf("\n1-Buscar por Tipo de Sensor\n2-Valor Medido\n");
					scanf("%d",&Tipo_De_Busqueda);
					switch(Tipo_De_Busqueda)
					{
						case 1: 
								NodoTemporal=NodoInicial;
								BuscarPorSensor(NodoTemporal);
								printf("\n\n");
								system("pause");
								system("cls");
								break;
						case 2:
								NodoTemporal=NodoInicial;
								BuscarPorValorMedido(NodoTemporal);
								printf("\n\n");
								system("pause");
								system("cls");
								break;
							
						default: break;
					}
					break;
					
			case 5:
					OrdenarMediciones(NodoInicial);
					printf("\nSe ordenaron correctamente todas las mediciones de mas antiguo a mas reciente. Presione opcion 2 para ver.\n\n");
					system("pause");
					system("cls");
					break;
					
			case 6: 
					NodoTemporal=NodoInicial;
					GuardarEnArchivo(NodoTemporal,ArchivoDeMediciones);
					printf("\nSe guardo correctamente los datos en el archivo\n\n");
					system("pause");
					system("cls");
					break;
					
			case 7: 
					NodoTemporal=NodoFinal;
					ImprimirAlReves(NodoTemporal);
					system("pause");
					system("cls");
					break;
					
			case 8: 
					salir=1;
					break;
					
			default: break;
		}
	}
	
	return 0;
}

//codigo de las funciones declaradas//

struct Mediciones *Agregar_Medicion(struct Mediciones *UltimoNodo)
{

	int TipoDeSensorUsado=0;
	
	struct Mediciones *NuevoNodo=(struct Mediciones *)malloc(sizeof(struct Mediciones));
	NuevoNodo->Anterior=UltimoNodo;
	NuevoNodo->Siguiente=NULL;
	
	
	fflush(stdin);
	printf("\nIngrese la fecha de la medicion (dia/mes/año): ");
	gets(NuevoNodo->Fecha);
	fflush(stdin);
	printf("\nIngrese la hora de la medicion (hora:minutos): ");
	gets(NuevoNodo->Hora);
	fflush(stdin);
	
	MostrarBaseDeDatos();

	
	printf("\n\nIngrese el tipo de sensor usado: ");
	scanf("%d",&TipoDeSensorUsado);
	switch(TipoDeSensorUsado)
	{
		case 1: 
				strcpy(NuevoNodo->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor);	
				strcpy(NuevoNodo->Sensor.TipoSensor,SensorTipo[0].TipoSensor);
				strcpy(NuevoNodo->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida);
				break;
		
		case 2: 
				strcpy(NuevoNodo->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor);	
				strcpy(NuevoNodo->Sensor.TipoSensor,SensorTipo[1].TipoSensor);
				strcpy(NuevoNodo->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida);
				break;
		
		case 3: 
				strcpy(NuevoNodo->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor);	
				strcpy(NuevoNodo->Sensor.TipoSensor,SensorTipo[2].TipoSensor);
				strcpy(NuevoNodo->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida);
				break;
		
		default: break;
	}
	
	printf("\nIngrese el valor medido: ");
	scanf("%f",&NuevoNodo->ValorMedido);
	fflush(stdin);
	
	printf("\nIngrese algun comentario sobre la medicion: ");
	gets(NuevoNodo->Comentarios);
	fflush(stdin);
	
	return(NuevoNodo);	
}


void CargarBaseDeDatos(void)
{

	strcpy(SensorTipo[0].MarcaSensor,"Philips");
	strcpy(SensorTipo[0].TipoSensor,"Lluvia");
	strcpy(SensorTipo[0].UnidadMedida,"Milimetros");
	
	strcpy(SensorTipo[1].MarcaSensor,"Samsung");
	strcpy(SensorTipo[1].TipoSensor,"Temperatura");
	strcpy(SensorTipo[1].UnidadMedida,"Celsius");
	
	strcpy(SensorTipo[2].MarcaSensor,"Siemens");
	strcpy(SensorTipo[2].TipoSensor,"Presion");
	strcpy(SensorTipo[2].UnidadMedida,"Bar");
}


void Mostrar_Todas_Mediciones(struct Mediciones *PrimerNodo)
{

	int i=0;
	
	struct Mediciones *Temporal=PrimerNodo;
	
	while(Temporal!=NULL)
	{
		printf("\n---------MEDICION N°%d---------\n",i);
		
		printf("\n\nFecha de la Medicion:");
		puts(Temporal->Fecha);
		
		printf("\n\nHora de la medicion: ");
		puts(Temporal->Hora);
		
		printf("\n--DATOS DEL SENSOR USADO--\n");
		printf("\nMarca: ");
		puts(Temporal->Sensor.MarcaSensor);
		
		printf("\nTipo: ");
		puts(Temporal->Sensor.TipoSensor);
		
		printf("\nUnidad de Medida: ");
		puts(Temporal->Sensor.UnidadMedida);
		
		printf("\n\nValor Medido: %.2f",Temporal->ValorMedido);
		
		printf("\nComentario acerca de la Medicion: ");
		puts(Temporal->Comentarios);
		
		printf("\n-------------------------------\n");
		
		Temporal=Temporal->Siguiente;
		i++;
	}
	
}

void Eliminar_Medicion(struct Mediciones **PrimerNodo, struct Mediciones **UltimoNodo)
{

	int Medicion_Eliminar=0,Posicion=0;
	
	struct Mediciones *Actual = *PrimerNodo; 
	struct Mediciones *Anterior = NULL;
	
	Mostrar_Todas_Mediciones(Actual);
	
	Actual=*PrimerNodo;
	
	printf("\nINGRESE EL NUMERO DE MEDICION A ELIMINAR: ");
	scanf("%d",&Medicion_Eliminar);
	
	
	if(Actual != NULL  &&  Medicion_Eliminar==0)  //si es el primero//
	{
		*PrimerNodo=Actual->Siguiente;
		
		(*PrimerNodo)->Siguiente=Actual->Siguiente->Siguiente;
		(*PrimerNodo)->Anterior=NULL;
		
		free(Actual);
		printf("\nMensaje: Se encontro al primer elemento de la lista\n");
		printf("\nMedicion eliminada satisfactoriamente\n");
		return;
	}
	
	while(Actual != NULL  && Posicion!=Medicion_Eliminar)  //si no es el primero, recorro hasta encontrar algo//
	{
		Anterior=Actual;			
		Actual=Actual->Siguiente;
		Posicion++;
	}
	
	if(Actual == NULL)	
	{
		printf("\nHa ingresado un valor incorrecto");
		return;
	}
	
	if(Actual==*UltimoNodo) // es el ultimo nodo ?
	{
		*UltimoNodo=Anterior;
		
		(*UltimoNodo)->Siguiente=NULL;
		(*UltimoNodo)->Anterior=Actual->Anterior;
		
		free(Actual);	
		printf("\nMensaje: Se encontro al ultimo elemento de la lista\n");
		printf("\nMedicion eliminada satisfactoriamente\n");
		return;
	}
	else
	{
		Anterior->Siguiente=Actual->Siguiente; 
		
		Actual->Siguiente->Anterior=Anterior;
		
		free(Actual);
		printf("\nMensaje: Se encontro un elemento del medio de la lista\n");
		printf("\nImagen eliminada satisfactoriamente\n");
		return;
	}
}

void Mostrar_Una_Medicion(struct Mediciones *Actual)
{

	printf("\n-------------------------------");
	
	printf("\n\nFecha de la Medicion:");
	puts(Actual->Fecha);
	
	printf("\n\nHora de la medicion: ");
	puts(Actual->Hora);
	
	printf("\n--DATOS DEL SENSOR USADO--\n");
	printf("\nMarca: ");
	puts(Actual->Sensor.MarcaSensor);
	
	printf("\nTipo: ");
	puts(Actual->Sensor.TipoSensor);
	
	printf("\nUnidad de Medida: ");
	puts(Actual->Sensor.UnidadMedida);
	
	printf("\n\nValor Medido: %.2f",Actual->ValorMedido);
	
	printf("\nComentario acerca de la Medicion: ");
	puts(Actual->Comentarios);
	
	printf("\n-------------------------------");
}

void MostrarBaseDeDatos(void)
{

	printf("\nLOS SENSORES REGISTRADOS SON: \n");
	printf("\nSENSOR 1:\n");
	printf("Marca: ");
	puts(SensorTipo[0].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[0].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[0].UnidadMedida);
	
	printf("\nSENSOR 2:\n");
	printf("Marca: ");
	puts(SensorTipo[1].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[1].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[1].UnidadMedida);
	
	printf("\nSENSOR 3:\n");
	printf("Marca: ");
	puts(SensorTipo[2].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[2].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[2].UnidadMedida);
}

void BuscarPorSensor(struct Mediciones *PrimerNodo)
{

	int Buscar_Sensor=0,control=0;
	
	struct Mediciones *Actual=PrimerNodo;
	
	MostrarBaseDeDatos();
	
	printf("\nIngrese el NUMERO DE SENSOR a buscar: ");
	scanf("%d",&Buscar_Sensor);
	
	switch(Buscar_Sensor)
	{
		case 1: 
				while(Actual!=NULL)
				{
					if((strcmp(Actual->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor))==0 && (strcmp(Actual->Sensor.TipoSensor,SensorTipo[0].TipoSensor))==0 && (strcmp(Actual->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida))==0)
					{
						Mostrar_Una_Medicion(Actual);
						control=1;
					}
					Actual=Actual->Siguiente;
				}
				if(control==0)
				{
					printf("\nNo se encontro ninguna medicion relacionada al Sensor 1\n");
				}
				break;
				
		case 2:
				while(Actual!=NULL)
				{
					if((strcmp(Actual->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor))==0 && (strcmp(Actual->Sensor.TipoSensor,SensorTipo[1].TipoSensor))==0 && (strcmp(Actual->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida))==0)
					{
						Mostrar_Una_Medicion(Actual);
						control=1;
					}
					Actual=Actual->Siguiente;
				}
				if(control==0)
				{
					printf("\nNo se encontro ninguna medicion relacionada al Sensor 2\n");
				}
				break;
				
		case 3:
				while(Actual!=NULL)
				{
					if((strcmp(Actual->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor))==0 && (strcmp(Actual->Sensor.TipoSensor,SensorTipo[2].TipoSensor))==0 && (strcmp(Actual->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida))==0)
					{
						Mostrar_Una_Medicion(Actual);
						control=1;
					}
					Actual=Actual->Siguiente;
				}
				if(control==0)
				{
					printf("\nNo se encontro ninguna medicion relacionada al Sensor 3\n");
				}
				break;
				
		default: 
				printf("\nHa ingresado un valor de sensor incorrecto");
				break;
	}
}

void BuscarPorValorMedido(struct Mediciones *PrimerNodo)
{


	struct Mediciones *Actual=PrimerNodo;
	
	float ValorABuscar=0;
	
	int Seleccionador=0;
	
	printf("\nIngrese el valor a buscar: ");
	scanf("%f",&ValorABuscar);
	printf("\n\nDesea buscar...\n1-Valores Menores a %.2f\n2-Valores Iguales a %.2f\n3-Valores Mayores a %.2f\n",ValorABuscar,ValorABuscar,ValorABuscar);
	scanf("%d",&Seleccionador);
	switch(Seleccionador)
	{
		case 1:
				while(Actual!=NULL)
				{
					if(Actual->ValorMedido < ValorABuscar )
					{
						Mostrar_Una_Medicion(Actual);
					}
					
					Actual=Actual->Siguiente;
				}
				break;
				
		case 2:
				while(Actual!=NULL)
				{
					if(Actual->ValorMedido == ValorABuscar )
					{
						Mostrar_Una_Medicion(Actual);
					}
					
					Actual=Actual->Siguiente;
				}
				break;
		case 3:
				while(Actual!=NULL)
				{
					if(Actual->ValorMedido > ValorABuscar )
					{
						Mostrar_Una_Medicion(Actual);
					}
					
					Actual=Actual->Siguiente;
				}
				break;
				
		default: break;
	}
}


void OrdenarMediciones(struct Mediciones *PrimerNodo)
{


	struct Mediciones *actual = PrimerNodo;
	struct Mediciones *minimo;
	struct Mediciones *temp;
	
	char tempFecha[15];
	char tempHora[15];
	struct BaseDeSensores tempSensor;
	float tempValorMedido;
	char tempComentarios[150];

	while (actual != NULL)
	{
		minimo = actual;
		temp = actual->Siguiente;
		
		while (temp != NULL)
		{
			if (strcmp(temp->Fecha, minimo->Fecha) < 0)
			{
				minimo = temp;
			}
			
			temp = temp->Siguiente;
		}
		
		// Intercambiar los campos de los nodos
		if (minimo != actual)
		{
			strcpy(tempFecha, actual->Fecha);
			strcpy(tempHora, actual->Hora);
			tempSensor=actual->Sensor;
			tempValorMedido = actual->ValorMedido;
			strcpy(tempComentarios, actual->Comentarios);
			
			
			strcpy(actual->Fecha, minimo->Fecha);
			strcpy(actual->Hora, minimo->Hora);
			actual->Sensor = minimo->Sensor;
			actual->ValorMedido = minimo->ValorMedido;
			strcpy(actual->Comentarios, minimo->Comentarios);
			
			
			strcpy(minimo->Fecha, tempFecha);
			strcpy(minimo->Hora, tempHora);
			minimo->Sensor = tempSensor;
			minimo->ValorMedido = tempValorMedido;
			strcpy(minimo->Comentarios, tempComentarios);
		}
		
		actual = actual->Siguiente;
	}
}

void GuardarEnArchivo(struct Mediciones *PrimerNodo, FILE *Archivo)
{


	struct Mediciones *Actual=PrimerNodo;
	
	if((Archivo=fopen("RegistroDeMediciones.txt","wb+"))!=NULL)
	{
		while(Actual!=NULL)
		{
			fwrite(Actual,sizeof(struct Mediciones),1,Archivo);
			Actual=Actual->Siguiente;
		}
	}
	else
	{
		printf("\nProblemas para abrir el archivo");
	}

	fclose(Archivo);
}

struct Mediciones *LeerDesdeArchivo(FILE *Archivo)
{
	struct Mediciones *Cabeza=NULL;
	struct Mediciones *Ultimo=NULL;
	struct Mediciones *Temp=NULL;
	
	int control=0;
	
	if((Archivo=fopen("RegistroDeMediciones.txt","rb+"))!=NULL)
	{
		do
		{
			struct Mediciones *NuevoNodo=(struct Mediciones *)malloc(sizeof(struct Mediciones));
			control=fread(NuevoNodo,sizeof(struct Mediciones),1,Archivo);
			
			Temp=NuevoNodo->Siguiente;; //guardo el siguiente del que estoy trabajando ara ver si existe un elemento a posterior en la condicion while//
	
			if(control==1)
			{
				if(Cabeza==NULL)
				{
					Cabeza=NuevoNodo;
					Cabeza->Siguiente=NULL;
					Cabeza->Anterior=NULL;
					Ultimo=NuevoNodo;
				}
				else
				{
					Ultimo->Siguiente = NuevoNodo;
					NuevoNodo->Siguiente = NULL;
					NuevoNodo->Anterior = Ultimo;
					Ultimo=NuevoNodo;
				}
			}
			else
			{
				return(Cabeza);
			}
		}while(Temp!=NULL);
	}
	else
	{
		printf("\nProblemas para abrir el archivo");
	}
	fclose(Archivo);
	return(Cabeza);
}

struct Mediciones *EncontrarUltimoNodo(struct Mediciones *PrimerNodo)
{
	struct Mediciones *Actual = PrimerNodo;
	struct Mediciones *UltimoNodo = NULL;
	
	while(Actual!=NULL)
	{
		UltimoNodo=Actual;
		Actual=Actual->Siguiente;
	}
	return(UltimoNodo);
}




void ImprimirAlReves(struct Mediciones *UltimoNodo)
{
	int i=0;
	
	struct Mediciones *Temporal = UltimoNodo;
	
	while(Temporal!=NULL)
	{
		
		printf("\n---------MEDICION N°%d---------\n",i);
		
		printf("\n\nFecha de la Medicion:");
		puts(Temporal->Fecha);
		
		printf("\n\nHora de la medicion: ");
		puts(Temporal->Hora);
		
		printf("\n--DATOS DEL SENSOR USADO--\n");
		printf("\nMarca: ");
		puts(Temporal->Sensor.MarcaSensor);
		
		printf("\nTipo: ");
		puts(Temporal->Sensor.TipoSensor);
		
		printf("\nUnidad de Medida: ");
		puts(Temporal->Sensor.UnidadMedida);
		
		printf("\n\nValor Medido: %.2f",Temporal->ValorMedido);
		
		printf("\nComentario acerca de la Medicion: ");
		puts(Temporal->Comentarios);
		
		printf("\n-------------------------------\n");
		
		Temporal=Temporal->Anterior;
		i++;
	
	}
}
