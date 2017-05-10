#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
int check_error(int size);
void initialize_2Darray(int array[][MAX], int size);
int smallest_number(int array[][MAX], int size);
void print_2Darray(int array[][MAX], int size);
int main()
{
	srand(time(NULL));
	int array[MAX][MAX];
	int size;
	printf("Enter the size of the array:");
	scanf("%d", &size);
	while (check_error==0)
	{
		printf("Invalid input, enter the size of the array again:");
		scanf("%d",  &size);
	}//End error while//
	initialize_2Darray(array, size);
	print_2Darray(array, size);
	printf("Smallest number in the array is %d\n", smallest_number(array, size));
return 0;
}
int check_error(int size)
{
	if (size<=100 && size>0)
	return 1;
	else
	return 0;
}
void initialize_2Darray(int array[][MAX], int size)
{
	int i, j;//Counter//
	for(i=0; i<=size; i++)
	{
		for(j=0; j<=size; j++) 
			array[i][j]=(rand()%101);
	}
}
void print_2Darray(int array[][MAX], int size)
{
	int i, j;
	printf("Input array\n");
	for(i=0; i<=size; i++)
	{
		for(j=0; j<=size; j++)
		{
			printf("%3d ", array[i][j]);
		}
		printf("\n");
	}
}
int smallest_number(int array[][MAX], int size)
{
	int i, j, min;
	min=100;
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			if(array[i][j]<min)
			min=array[i][j];
		}
	}
return min;
}		
