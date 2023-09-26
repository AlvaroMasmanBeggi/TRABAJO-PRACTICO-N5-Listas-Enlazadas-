#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30


struct ListadoDeImagenes
{
	int Codigo;
	char Nombre[MAX];
	char Extension[MAX];
	int Bytes;
	float Precio;
	struct ListadoDeImagenes *Siguiente;
};


//declaracion de las funciones a usar//



struct ListadoDeImagenes *AgregarImagen();

void MostrarTodasImagenes(struct ListadoDeImagenes *NodoActual);

void EliminarImagen(struct ListadoDeImagenes **PrimerNodo,struct ListadoDeImagenes **UltimoNodo,int codigo);

void MostrarUnaImagen(struct ListadoDeImagenes *NodoAImprimir);

void BuscarPorCodigo(struct ListadoDeImagenes *PrimerNodo,int codigo);

void BuscarPorNombre(struct ListadoDeImagenes *PrimerNodo,char *Nombre);

void BuscarPorExtension(struct ListadoDeImagenes *PrimerNodo, char *Extension);

void BuscarPorBytes(struct ListadoDeImagenes *PrimerNodo, int Bytes);

void BuscarPorPrecio(struct ListadoDeImagenes *PrimerNodo, float Precio);

int CantidadDeElementos(struct ListadoDeImagenes *PrimerNodo);

void MostrarTodasImagenesOrdenadas(struct ListadoDeImagenes *NodoInicial);

struct ListadoDeImagenes *LeerDesdeArchivo(FILE *Archivo);

void SobrescribirArchivo(struct ListadoDeImagenes *PrimerNodo, FILE *Archivo);

struct ListadoDeImagenes *EncontrarUltimoNodo(struct ListadoDeImagenes *PrimerNodo);



//programa principal//


int main(int argc, char *argv[]) 
{

	//seccion donde declaro todas las variables que voy a usar//
	

	struct ListadoDeImagenes *NodoInicial=NULL;
	
	struct ListadoDeImagenes *NodoFinal=NULL;			//Siempre inicializar punteros en NULL//
	
	struct ListadoDeImagenes *NodoTemporal=NULL;
	
	int seleccionador, salir=0, Codigo_Eliminador=0, Selector_Busqueda=0, Codigo_Buscar, Bytes_Buscar,Decision_Inicial=0, Cantidad_Imagenes=0;;
	
	char Buscar_Nombre[MAX],Buscar_Extension[MAX];
	
	float Buscar_Precio=0.0;
	
	FILE *ArchivoImagen;
	
	
	//verifico que en el archvo existan datos que puedan servir para cargar en el sistema//
	
	
	NodoInicial=LeerDesdeArchivo(ArchivoImagen);
	
	if(NodoInicial!=NULL)
	{
		NodoTemporal=NodoInicial;
		NodoFinal=EncontrarUltimoNodo(NodoTemporal);  //necesito conocer donde va aestar mi nodo final de la lista leida//
		
		printf("\nSE ENCONTRO UNA BASE CON IMAGENES: \n");
		
		NodoTemporal=NodoInicial;
		MostrarTodasImagenes(NodoTemporal);
		
		NodoTemporal=NodoInicial;
		Cantidad_Imagenes=CantidadDeElementos(NodoTemporal);
		
		printf("\n¿DESEA RECUPERARLA...?\n1-SI\n2-NO\n");
		scanf("%d",&Decision_Inicial);
	}
	else
	{
		printf("\nLA BASE DE DATOS DE IMAGENES ESTA VACIA\n");
	}
	
	
	if(Decision_Inicial==2)
	{
		free(NodoInicial);
		NodoInicial=NULL;
		NodoFinal=NULL;
		
		Cantidad_Imagenes=0;
	}
	
	system("pause");
	system("cls");
	
	//una vez decidido que hacer con lo del archivo, ingreso al programa principal//
	
	while(salir!=1)
	{
		printf("\n\nMENU PRINCIPAL\n\n1-Agregar Nueva Imagen\n2-Mostrar todas las imagenes\n3-Eliminar imagen\n4-Buscar\n5-Mostrar Lista 		Ordenada Alfabeticamente\n6-Guardar y actualizar el Archivo\n7-Salir\n");
		scanf("%d",&seleccionador);
		fflush(stdin);
		switch(seleccionador)
		{
			case 1:
					NodoTemporal=AgregarImagen();
					
					if(NodoInicial==NULL) // si es el primer nodo
					{
						NodoInicial = NodoTemporal;
						NodoInicial->Siguiente=NULL;						
						
					}else // para el resto de los nodos
					{ 
						NodoFinal->Siguiente = NodoTemporal;
					}
					
					NodoFinal = NodoTemporal;
					
					system("cls");
					break;
					
			case 2: 
					NodoTemporal=NodoInicial;
					MostrarTodasImagenes(NodoTemporal);
					
					printf("\n\n");
					system("pause");
					system("cls");
					break;
					
			case 3:
					NodoTemporal=NodoInicial;
					MostrarTodasImagenes(NodoTemporal);
					
					printf("\n\nINGRESE EL CODIGO DE LA IMAGEN A ELIMINAR: ");
					scanf("%d",&Codigo_Eliminador);
					
					EliminarImagen(&NodoInicial,&NodoFinal,Codigo_Eliminador);
					
					printf("\n\n");
					system("pause");
					system("cls");
					break;
					
			case 4: 
					printf("\nPor que desea buscar...\n\n1-Codigo\n2-Nombre\n3-Extension\n4-Peso en Bytes\n5-Precio\n");
					scanf("%d",&Selector_Busqueda);
					switch(Selector_Busqueda)
					{
						case 1:
								printf("\nIngrese el codigo a buscar: ");
								scanf("%d",&Codigo_Buscar);
								NodoTemporal=NodoInicial;
								BuscarPorCodigo(NodoTemporal,Codigo_Buscar);
								
								system("pause");
								system("cls");
								break;
								
						case 2: 
								fflush(stdin);
								printf("\nIngrese el nombre del archivo: ");
								gets(Buscar_Nombre);
								fflush(stdin);
								NodoTemporal=NodoInicial;
								BuscarPorNombre(NodoTemporal,Buscar_Nombre);
								
								system("pause");
								system("cls");
								break;
								
						case 3: 
								fflush(stdin);
								printf("\nIngrese el nombre de la extension: ");
								gets(Buscar_Extension);
								fflush(stdin);
								NodoTemporal=NodoInicial;
								BuscarPorExtension(NodoTemporal,Buscar_Extension);
								
								system("pause");
								system("cls");
								break;
								
						case 4:
								fflush(stdin);
								printf("\nIngrese la cantidad de Bytes: ");
								scanf("%d",&Bytes_Buscar);
								fflush(stdin);
								NodoTemporal=NodoInicial;
								BuscarPorBytes(NodoTemporal,Bytes_Buscar);
								
								system("pause");
								system("cls");
								break;
								
						case 5:
								fflush(stdin);
								printf("\nIngrese el precio: ");
								scanf("%f",&Buscar_Precio);
								fflush(stdin);
								NodoTemporal=NodoInicial;
								BuscarPorPrecio(NodoTemporal,Buscar_Precio);
								
								system("pause");
								system("cls");
								break;
					}
					break;
					
			case 5: 
					NodoTemporal=NodoInicial;
					MostrarTodasImagenesOrdenadas(NodoTemporal);
					printf("\nMensaje: Imagenes ordenadas, presione la opcion 2 para visualizar\n"); 
					system("pause");
					system("cls");
					break;
					
			case 6:	
					NodoTemporal=NodoInicial;
					SobrescribirArchivo(NodoTemporal,ArchivoImagen);
					printf("\nMensaje: Se guardo y actualizo correctamente el archivo\n");
					system("pause");
					system("cls");
					break;
					
			case 7:
					salir=1;
					break;
				
			default: break;
		}
	}
	
return 0;
}


//codigo de las funciones del programa//

//funcion para agregar una imagen y por ende un nodo//

struct ListadoDeImagenes *AgregarImagen()
{
	
	struct ListadoDeImagenes *NuevaImagen=(struct ListadoDeImagenes *) malloc(sizeof(struct ListadoDeImagenes));
	NuevaImagen->Siguiente=NULL;
	
	printf("\nIngrese el codigo de la nueva imagen: ");
	scanf("%d",&NuevaImagen->Codigo);
	fflush(stdin);
	printf("\nIngrese el nombre de la nueva imagen: ");
	gets(NuevaImagen->Nombre);
	fflush(stdin);
	printf("\nIngrese la extension de la nueva imagen: ");
	gets(NuevaImagen->Extension);
	fflush(stdin);
	printf("\nIngrese la cantidad de bytes de la nueva imagen: ");
	scanf("%d",&NuevaImagen->Bytes);
	fflush(stdin);
	printf("\nIngrese el precio de la nueva imagen: ");
	scanf("%f",&NuevaImagen->Precio);
	fflush(stdin);
		
	return(NuevaImagen);
}

//funcion para imprimir por pantalla todos los nodos de la lista//

void MostrarTodasImagenes(struct ListadoDeImagenes *NodoActual)
{
	int i=0;
	
	while(NodoActual!=NULL)
	{
		printf("\n\n-------------------IMAGEN N°%d--------------------\n\n",i);
		printf("\n\nCodigo de la imagen: %d",NodoActual->Codigo);
		
		printf("\n\nNombre de la imagen: ");
		puts(NodoActual->Nombre);
		
		printf("\nExtension de la imagen: ");
		puts(NodoActual->Extension);
		
		printf("\nBytes de la imagen: %d",NodoActual->Bytes);
		
		printf("\n\nPrecio de la imagen: %.2f",NodoActual->Precio);
		printf("\n\n---------------------------------------------------\n\n");
		
		NodoActual=NodoActual->Siguiente;
		i++;
	}
}

//funcion para eliminar algun nodo segun su codigo//

void EliminarImagen(struct ListadoDeImagenes **PrimerNodo,struct ListadoDeImagenes **UltimoNodo,int codigo)  
{
	struct ListadoDeImagenes *Actual = *PrimerNodo; 
	struct ListadoDeImagenes *Anterior = NULL;
	
	if(Actual != NULL  &&  Actual->Codigo == codigo)  //si es el primero//
	{
		*PrimerNodo=Actual->Siguiente; 
		free(Actual);
		printf("\nMensaje: Se encontro al primer elemento de la lista\n");
		printf("\nImagen eliminada satisfactoriamente\n");
		return;
	}
	
	while(Actual != NULL  &&  Actual->Codigo != codigo)  //si no es el primero, recorro hasta encontrar algo//
	{
		Anterior=Actual;			
		Actual=Actual->Siguiente;
	}
	
	if(Actual == NULL)	
	{
		printf("\nNo se encontro ninguna imagen con el codigo: %d",codigo);
		return;
	}
	
	if(Actual==*UltimoNodo) // es el ultimo nodo ?
	{
		*UltimoNodo=Anterior;
		(*UltimoNodo)->Siguiente=NULL;
		free(Actual);	
		printf("\nMensaje: Se encontro al ultimo elemento de la lista\n");
		printf("\nImagen eliminada satisfactoriamente\n");
		return;
	}
	else
	{
		Anterior->Siguiente=Actual->Siguiente; 
		free(Actual);
		printf("\nMensaje: Se encontro un elemento del medio de la lista\n");
		printf("\nImagen eliminada satisfactoriamente\n");
		return;
	}
}

void MostrarUnaImagen(struct ListadoDeImagenes *NodoAImprimir)
{
	printf("\n\n-------------------IMAGEN ENCONTRADA--------------------\n\n");
	printf("\n\nCodigo de la imagen: %d",NodoAImprimir->Codigo);
	
	printf("\n\nNombre de la imagen: ");
	puts(NodoAImprimir->Nombre);
	
	printf("\nExtension de la imagen: ");
	puts(NodoAImprimir->Extension);
	
	printf("\nBytes de la imagen: %d",NodoAImprimir->Bytes);
	
	printf("\n\nPrecio de la imagen: %.2f",NodoAImprimir->Precio);
	printf("\n\n---------------------------------------------------\n\n");
}

//funciones para buscar. Funcionan comparando//

void BuscarPorCodigo(struct ListadoDeImagenes *PrimerNodo,int codigo)
{
	struct ListadoDeImagenes *Actual = PrimerNodo;
	int control=0;
	
	while(Actual!=NULL)
	{
		if(Actual->Codigo == codigo)
		{
			MostrarUnaImagen(Actual);
			control=1;
		}
		Actual=Actual->Siguiente;
	}
	
	if(control==0)
	{
		printf("\nNo se encontro ninguna imagen con el codigo: %d\n",codigo);
	}
}

void BuscarPorNombre(struct ListadoDeImagenes *PrimerNodo,char *Nombre)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	int control=0;
	
	while(Actual!=NULL)
	{
		if(strcmp(Nombre,Actual->Nombre)==0)
		{
			MostrarUnaImagen(Actual);
			control=1;
		}
		Actual=Actual->Siguiente;
	}
	
	if(control==0)
	{
		printf("\nNo se encontro ninguna imagen con el nombre: %s\n",Nombre);
	}
}

void BuscarPorExtension(struct ListadoDeImagenes *PrimerNodo, char *Extension)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	int control=0;
	
	while(Actual!=NULL)
	{
		if(strcmp(Extension,Actual->Extension)==0)
		{
			MostrarUnaImagen(Actual);
			control=1;
		}
		Actual=Actual->Siguiente;
	}
	
	if(control==0)
	{
		printf("\nNo se encontro ninguna imagen con la extension: %s\n",Extension);
	}
}

void BuscarPorBytes(struct ListadoDeImagenes *PrimerNodo, int Bytes)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	
	int seleccionador,control1=0,control2=0;
	printf("\n1-Mostrar imagenes mayores a %d Bytes\n2-Mostrar imagenes menores a %d Bytes\n",Bytes,Bytes);
	scanf("%d",&seleccionador);
	switch(seleccionador)
	{
		case 1: 
				while(Actual!=NULL)
				{
					if(Actual->Bytes>Bytes)
					{
						MostrarUnaImagen(Actual);
						control1=1;
					}
					Actual=Actual->Siguiente;
				}
				break;
				
		case 2:
				while(Actual!=NULL)
				{
					if(Actual->Bytes<Bytes)
					{
						MostrarUnaImagen(Actual);
						control2=1;
					}
					Actual=Actual->Siguiente;
				}
				break;
				
		default:break;
	}
		if(control1==0)
		{
			printf("\nNo se encontraron imagenes que superen los %d Bytes\n",Bytes);
		}
		if(control2==0)
		{
			printf("\nNo se encontraron imagenes que esten inferior %d Bytes\n",Bytes);
		}
}

void BuscarPorPrecio(struct ListadoDeImagenes *PrimerNodo, float Precio)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	
	int seleccionador,control=0;;
	printf("\n1-Mostrar imagenes mayores a %.2f Pesos\n2-Mostrar imagenes menores a %.2f Pesos\n",Precio,Precio);
	scanf("%d",&seleccionador);
	switch(seleccionador)
	{
	case 1: 
		while(Actual!=NULL)
		{
			if(Actual->Precio>Precio)
			{
				MostrarUnaImagen(Actual);
				control=1;
			}
			Actual=Actual->Siguiente;
		}
		
		if(control==0)
		{
			printf("\nNo se encontraron imagenes que superen los %.2f Pesos\n",Precio);
		}
		break;
		
	case 2:
		while(Actual!=NULL)
		{
			if(Actual->Precio<Precio)
			{
				MostrarUnaImagen(Actual);
				control=1;
			}
			Actual=Actual->Siguiente;
		}
		
		if(control==0)
		{
			printf("\nNo se encontraron imagenes que esten inferior %.2f Pesos\n",Precio);
		}
		break;
		
	default:break;
	}
}

//funcion que se usa para ver que cantidad de nodos tenemos en nuestro sistema//

int CantidadDeElementos(struct ListadoDeImagenes *PrimerNodo)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	
	int cantidad=0;
	
	while(Actual!=NULL)
	{
		cantidad++;
		Actual=Actual->Siguiente;
	}
	return(cantidad);
}

//funcion que se usa para ordenar todos los nodos de manera alfabetica segun el nombre que los caracteriza//

void MostrarTodasImagenesOrdenadas(struct ListadoDeImagenes *NodoInicial)
{

struct ListadoDeImagenes *actual = NodoInicial;
struct ListadoDeImagenes *minimo;
struct ListadoDeImagenes *temp;
int tempCodigo;
char tempNombre[100];
char tempExtension[100];
int tempBytes;
float tempPrecio;

while (actual != NULL)
{
	minimo = actual;
	temp = actual->Siguiente;
	
	while (temp != NULL)
	{
		if (strcmp(temp->Nombre, minimo->Nombre) < 0)
		{
			minimo = temp;
		}
		
		temp = temp->Siguiente;
	}
	
	// Intercambiar los campos de los nodos
	if (minimo != actual)
	{
		tempCodigo = actual->Codigo;
		strcpy(tempNombre, actual->Nombre);
		strcpy(tempExtension, actual->Extension);
		tempBytes=actual->Bytes;
		tempPrecio=actual->Precio;
		
		actual->Codigo = minimo->Codigo;
		strcpy(actual->Nombre, minimo->Nombre);
		strcpy(actual->Extension, minimo->Extension);
		actual->Bytes=minimo->Bytes;
		actual->Precio=minimo->Precio;
		
		minimo->Codigo = tempCodigo;
		strcpy(minimo->Nombre, tempNombre);
		strcpy(minimo->Extension, tempExtension);
		minimo->Bytes=tempBytes;
		minimo->Precio=tempPrecio;
	}
	
	actual = actual->Siguiente;
}
}

//funcion que se usa para leer la lista enlazada y crearla si existen elementos en el archivo//

struct ListadoDeImagenes *LeerDesdeArchivo(FILE *Archivo)
{
	struct ListadoDeImagenes *Cabeza=NULL;
	struct ListadoDeImagenes *Ultimo=NULL;
	int control=0;
	
	if((Archivo=fopen("RegistroDeImagenes.txt","rb+"))!=NULL)
	{
		do
		{
			struct ListadoDeImagenes *NuevoNodo=(struct ListadoDeImagenes *)malloc(sizeof(struct ListadoDeImagenes));
			control=fread(NuevoNodo,sizeof(struct ListadoDeImagenes),1,Archivo);
	
			if(control==1)
			{
				if(Cabeza==NULL)
				{
					Cabeza=NuevoNodo;
					Ultimo=NuevoNodo;
				}
				else
				{
					Ultimo->Siguiente=NuevoNodo;
					Ultimo=NuevoNodo;
				}
			}
			else
			{
				return(Cabeza);
			}
		}while(Ultimo->Siguiente!=NULL);
	}
	else
	{
		printf("\nProblemas para abrir el archivo");
	}
	fclose(Archivo);
	return(Cabeza);
}

//funcion que se usa para escribir una lista enlazada en el archivo//

void SobrescribirArchivo(struct ListadoDeImagenes *PrimerNodo, FILE *Archivo)
{

	struct ListadoDeImagenes *NodoTemporal=PrimerNodo;
	
	if((Archivo=fopen("RegistroDeImagenes.txt","wb+"))!=NULL)
	{
		while(NodoTemporal!=NULL)
		{
			fwrite(NodoTemporal,sizeof(struct ListadoDeImagenes),1,Archivo);
			NodoTemporal=NodoTemporal->Siguiente;
		}
	}
	else
	{
		printf("\nProblemas para abrir el archivo");
	}

	fclose(Archivo);
}

//funcion que se usa para localizar el ultimo nodo a traves del primero. Se usa para cuando creamos una lista desde un archivo para tener el final de la misma//

struct ListadoDeImagenes *EncontrarUltimoNodo(struct ListadoDeImagenes *PrimerNodo)
{
	struct ListadoDeImagenes *Actual=PrimerNodo;
	struct ListadoDeImagenes *Ultimo=NULL;
	
	while(Actual!=NULL)
	{
		Ultimo=Actual;
		Actual=Actual->Siguiente;
	}
	return(Ultimo);
}


