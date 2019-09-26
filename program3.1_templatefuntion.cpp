
//3.1.1 template functions
// program 3.1; selection sort using templates

// TemplateFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <memory>

float RandomFloat(float a, float b);
void fillIntArray(int* a, int size);
void showIntArray(int* a, int size);
void fillFloatArray(float* f, int size);
void showFloatArray(float* f, int size);

using namespace std;

///// this is a template function which sorts the array of a generic type
template <class T>
void SelectionSort(T* a, const int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = i;
		for (int k = i + 1; k < n; k++)
			if (a[k] < a[j]) j = k;
		swap(a[i], a[j]);
	}
}


template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}




int main()
{
	////////
	int* intArray = new int[200];
	float* floatArray = new float[100];

	fillIntArray(intArray, 200);
	fillFloatArray(floatArray, 100);

	//showIntArray(intArray, 200);
	//showFloatArray(floatArray, 100);


	//// Testing selection sort function ////////
	//SelectionSort(intArray, 200);//// using selection sort to sort the integer arrray
	//SelectionSort(floatArray, 100); // using selection sort to sort the float array

	//showIntArray(intArray, 200);

	ChangeSizeID(intArray, 200, 100);


	cout << "\n Now showing the float Array:" << endl;

	//showFloatArray(floatArray, 100);



	return 0;
}


//// it fill an integer array with random integer 
void fillIntArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		*(a + i) = rand() % 100;
	}

}

//// this function prints all the elements of the arra
void showIntArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i << " = " << *(a + i) << endl;
	}
}

/// it fills a float array with random numbers
void fillFloatArray(float* f, int size)
{
	for (int i = 0; i < size; i++)
	{
		*(f + i) = RandomFloat(0, 100); //// generate a float random number from 0 to 100
	}
}

void showFloatArray(float* f, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i << " = " << *(f + i) << endl;
	}
}


//// gets a random float number in the range from a to b
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

