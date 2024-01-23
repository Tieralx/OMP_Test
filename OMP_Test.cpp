// OMP_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

#define sz 1000
#define chunk 100
#define shw 100

void printarray(float* d);

int main()
{
	srand(time(0));
	float random = rand() % 100;

	std::cout << "Suma de arreglos en paralelo\n";
	float arr1[sz], arr2[sz], res[sz];
	int i;

	for (i = 0; i < sz; i++)
	{
		random = rand() % 100;
		arr1[i] = random;
		random = rand() % 100;
		arr2[i] = random;
	}
	
	int piece = chunk;

	#pragma omp parallel for \
	shared(arr1,arr2,res,piece) private (i) \
	schedule(static, piece)

	for (i = 0; i < sz; i++)
		res[i] = arr1[i] + arr2[i];

	std::cout << "Arreglo 1 " << std::endl;
	printarray(arr1);
	std::cout << "mas arreglo 2 " << std::endl;
	printarray(arr2);
	std::cout << "suman " << std::endl;
	printarray(res);

	
}
void printarray(float* d)
{
	for (int i = 0; i < shw; i++)
		std::cout << d[i] << "-";
	std::cout << std::endl;
}


