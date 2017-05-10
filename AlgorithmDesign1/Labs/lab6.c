/*Holt Skinner
 * HASTG2
 * LabK
 * Lab6
 * Homecoming!*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100 /*Define Max size of array*/
/*Define Array*/
int array[SIZE];
/*Prototypes*/
int check_input(int);
void initialize_array(int);
void print_array(int);
int max(int);
int min(int);
float average(int);
void compute_stats(int);
int search(int, int);
int count_numbers(int, int);
int main()
{

	int size, value, i;
	srand(time(NULL));
	printf("Enter the size of the input:");
	scanf("%d", &size);
	while (check_input(size)==0)
	{
		printf("Invalid input. Enter the size of the input again:");
		scanf("%d", &size);
	}/*End Check input While*/
	initialize_array(size);
	print_array(size);
	compute_stats(size);
	printf("Enter the number you want to search:");
	scanf("%d", &value);
	if (search(size, value)==-1)
	{
		printf("The number %d is not present in the array\n", value);
	}
	else
	{
		printf("The number %d is present at the index %d\n", value, search(size, value));
		printf("The number %d is present %d times in the array\n", value, count_numbers(size, value));
	}
return 0;
}
int check_input(int size)
{
	if(size<=0)
	return 0;
	else
	return 1;
}
void initialize_array(int size)
{
	int i;/*Counter*/
	for (i=0; i<size; i++)
	array[i]=rand()%10;
}
void print_array(int size)
{
	int i;/*Counter*/
	printf("Input array\n");
	for (i=0; i<size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
int max(int size)
{
	int i, maximum;/*Counter & Max Value*/
	maximum=0;/*Initialize max*/
	for (i=0; i<size; i++)
	{
		if(array[i]>maximum)/*If Current number is larger than current max, then the new number is the new max*/
		maximum=array[i];
	} 
return maximum;
}
int min(int size)
{
	int i, minimum;/*Counter and Min Value*/
	minimum=9;
	for (i=0; i<size; i++)
	{
		if (array[i]<minimum)/*If current number is lower than previous min, then the new minimum is current number*/
		minimum=array[i];
	}
return minimum;
}
float average(int size)
{
	int i; 
	float total, the_average;
	for (i=0; i<size; i++)
	{
		total+=array[i];
	}
	the_average=total/size;
return the_average;
}
void compute_stats(int size)
{	
	printf("Largest number is %d\n", max(size)); 
	printf("Smallest number is %d\n", min(size));
	printf("Average of numbers is %.3f\n", average(size));	
}
int search(int size, int value)
{
	int i;
	for (i=0; i<size; i++)
	{
		if (array[i]==value)
		return i;
	}
	return -1;
}
	 

int count_numbers(int size, int value)
{
	int i, frequency;
	frequency=0;
	for (i=0; i<size; i++)
		{
			if (value==array[i])
			frequency=frequency+1;
		}
return frequency;
} 

