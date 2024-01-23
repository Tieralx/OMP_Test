// OMP_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Tecnologico de Monterrey 
//MNA
//Tarea 1. Programación de una solución paralela
//Materia: Computo en la nube
//Profesor titular: Dr. Eduardo Antonio Cendejas Castro 
//Profesor Tutor: Mtro. Samuel Medina García
//Nombre: Alejandro Emmanuel Silva Ortega A01794545

#include <iostream>
#include <omp.h>

#define sz 3000 // tamaño de los arreglos
#define chunk 200 // tamaño de las secciones de los arreglos que se usaran en cada hilo
#define shw 10 // registros a imprimir con los resultados
#define rndsz 60 // rango de teneracion de numeros aleatorios

void printarray(float* d);

void main()
{
	srand(time(0));
	float random = rand() % rndsz; //inicializacion de variable random, se usara para popular los arreglos

	std::cout << "Suma de arreglos en paralelo, con numeros aleatorios entre 0 y " << rndsz << ", mostrando " << shw << " registros de " << sz << "\n";
	float arr1[sz], arr2[sz], res[sz], threads[sz]; // inicializacion de arreglos arr1 y arr2 contendran los datos a sumar, res contendra los 
													//resultados de la sumatoria, threads sera usada para mostrar la cantidad de hilos usados en el proceso
	int i; 


	for (i = 0; i < sz; i++) // llenar los arreglos con numeros aleatorios
	{
		random = rand() % rndsz;
		arr1[i] = random;
		random = rand() % rndsz;
		arr2[i] = random;
	}
	
	int piece = chunk; 

	//creacion de for para uso en paralelo y configuracion de espacios privados y compartidos
	#pragma omp parallel for \
	shared(arr1,arr2,res,piece,threads) private (i) \
	schedule(static, piece)

	
	for (i = 0; i < sz; i++) //suma de arreglos
	{
		res[i] = arr1[i] + arr2[i];
		threads[i] = omp_get_num_threads(); // muestra los hilos usados en la funcion
	}

	std::cout << "Arreglo 1 " << std::endl;
	printarray(arr1);
	std::cout << "mas arreglo 2 " << std::endl;
	printarray(arr2);
	std::cout << "suman " << std::endl;
	printarray(res);
	std::cout << "Se usaron los siguientes hilos para generar estas sumas"<<std::endl;
	printarray(threads);


	
}
void printarray(float* d) //funcion para imprimir los arreglos
{
	for (int i = 0; i < shw; i++)
		std::cout << d[i] << "-";
	std::cout << std::endl;
}


