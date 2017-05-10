/*Holt Skinner
 * HASTG2 (Hashtag)
 * Lab 8w/bonus
 * Lab K
 * Bill Clinton*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
int check_error(int size);
void initialize_2Darray(int array[][MAX], int size);
void print_2Darray(int array[][MAX], int size);
int check_index(int index, int size);
int find_columnmax(int array[][MAX], int c, int size);
float calculate_columnaverage(int array[][MAX], int c, int size);
int find_rowmin(int array[][MAX], int r, int size);
void sort_2Darray(int array[][MAX], int size);//Bonus//
int main()
{
	srand(time(NULL));
	int array[MAX][MAX];
	int size, index, r;
	printf("Enter the size of the 2D array:");
	scanf("%d", &size);
	while (check_error(size)==0)
	{
		printf("Invalid input enter the size of the array again:");
		scanf("%d", &size);
	}//End error while//
	initialize_2Darray(array, size);
	print_2Darray(array, size);
	printf("Enter the column (1-%d):", size);
	scanf("%d", &index);
	while (check_index(index, size)==0)
	{
		printf("Invalid column index enter the column again:");
		scanf("%d", &index);
	}
	printf("The largest number present in column %d is %d.\n", index, find_columnmax(array, index, size));
	printf("The average of numbers present in column %d is %.2f.\n", index, calculate_columnaverage(array, index, size));
	for (r=1; r<=size; r++)
	{

		printf("Minimum number present in row %d is %d.\n", r, find_rowmin(array, r-1, size));
	}
	printf("Bonus Part!\n");/*Bonus*/
	printf("Array before sorting\n");
	print_2Darray(array, size);
	printf("\n");
	sort_2Darray(array, size);
	printf("Array after sorting\n");
	print_2Darray(array, size);/*End Bonus in main*/
return 0;
}
int check_error(int size)
{
	if (size>=1 && size<=100)
	return 1;
	else
	return 0;
}
void initialize_2Darray(int array[][MAX], int size)
{
	int i, j;//Counters//
	for (i=0; i<size; i++)//Row//
	{
		for (j=0; j<size; j++)//Column//
			array[i][j]=rand()%100;
	}
}
void print_2Darray(int array[][MAX], int size)
{
	int i, j;
	printf("2D Array\n");
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			printf("%3d", array[i][j]);
		}
		printf("\n");
	}
}
int check_index(int index, int size)
{	
	if (index>=1 && index<=size)
	return 1;
	else
	return 0;
}
int find_columnmax(int array[][MAX], int c, int size)
{
	--c;/*Safety net for wierd array numbering system*/
	int i, j, max=0;
	for (i=0; i<size; i++)
	{
		if (array[i][c]>max)
		max=array[i][c];
	}
return max;
}
float calculate_columnaverage(int array[][MAX], int c, int size)
{
	--c;
	int i;
	float hold=0, average;
	for (i=0; i<size; i++)
	{
		hold+=array[i][c];
	}
	average=hold/size;
return average;
}
int find_rowmin(int array[][MAX], int r, int size)
{
	int j, min=100;
	for (j=0; j<size; j++)
	{
		if (array[r][j]<min)
		min=array[r][j];
	}
return min;
}
void sort_2Darray(int array[][MAX], int size)//Bonus function//
{
	int i, j, p, hold;
	for (p=1; p<size; p++)//Pass//
	{
		for (i=0; i<size-1; i++)//Row Counter//
		{
			for (j=0; j<size-1; j++)
			{
				if (array[i][j]>array[i][j+1])
				{
					hold=array[i][j];
					array[i][j]=array[i][j+1];
					array[i][j+1]=hold;
				}//End if//
			}//End small for//
		}//End medium for//
	}//End big for//
}

