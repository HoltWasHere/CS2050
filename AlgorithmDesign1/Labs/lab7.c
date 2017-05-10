/*Holt Skinner
 * LabK
 * Lab7
 * HASTG2(Hashtag)
 * Mason*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_error(int size);
void initialize_array(int inputArray[], int size);
void print_array(int inputArray[], int size);
int count_numbers(int inputArray[], int size, int numToBeSearched);
void frequency(int inputArray[], int secondArray[], int size);
int mode(int secondArray[]);
void print_histogram(int secondArray[]);
int main()
{
	srand(time(NULL));
	int size, numToBeSearched, i;
	int inputArray[100], secondArray[10];
	printf("Enter the size of the input:");
	scanf("%d", &size);
	while (check_error(size)==0)
	{
		printf("Invalid input enter the size of the input again:");
		scanf("%d", &size);
	}
	initialize_array(inputArray, size);
	print_array(inputArray, size);
	frequency(inputArray, secondArray, size);
	printf("Mode for the array is number %d\n", mode(secondArray));
	print_histogram(secondArray);
return 0;
}
int check_error(int size)
{	/*Checks for errors*/
	if((size<=100)&&(size>=1))
	return 1;
	else
	return 0;
}
void initialize_array(int inputArray[], int size)
{	/*initializes array with random numbers from 0-9*/
	int i;/*Counter*/
	for (i=0; i<size; i++)
	inputArray[i]=rand()%10;
}
void print_array(int inputArray[], int size)
{	/*Prints array*/
	int i;/*Counter*/
	printf("Input array\n");
	for (i=0; i<size; i++)/*cycles through array and prints each value*/
	printf("%d ", inputArray[i]);
	printf("\n");/*Print newline after the array is complete*/
}
void frequency (int inputArray[], int secondArray[], int size)
{
	int i, j, numToBeSearched, freq;/*Counters for array positions in array 1 and 2, values to cycle through, and the frequency or new values in array 2*/
	numToBeSearched=0;/*Start counting values at zero*/
	j=0;/*Start postion in array 2 at zero*/
	for(numToBeSearched=0; numToBeSearched<10; numToBeSearched++)/* Cycles through each integer value*/
	{
		freq=0;
		for(i=0; i<size; i++)/*Cycles through places in array*/
		{
			if(numToBeSearched==inputArray[i])
			++freq;
		}/*End Array Placement for*/
		
		secondArray[j]=freq;
		++j;
	}/*End integer value for*/
}/*End frequency Function*/
int mode(int secondArray[])
{
	int i, j, max;/*Counter and maximum frequency(mode)*/
	max=0;/*Initialize max*/
	for(i=0; i<10; i++)
	{
		if(secondArray[i]>max)
		{
			max=secondArray[i];/*If current number is larger than current max, then the current number is new max*/
			j=i;/*Saves the counter of the maximum*/
		}
	}/*End for*/
return j;
}	
void print_histogram(int secondArray[])
{
	int i, j;/*Counters*/
	for(i=0; i<10; i++)/*cycles through integer values*/
	{
		printf("%d:", i);
		for(j=1; j<=secondArray[i]; j++)
		printf("%c", '*');/*End Asterisk for*/
		printf("\n");
	}/*End integer value for*/
}
