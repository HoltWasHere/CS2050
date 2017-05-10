#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_error(int);
void initialize_array(int[], int);
void print_array(int[], int);
int count_numbers(int[], int, int);
void frequency(int[], int[], int);
int main()
{
	srand(time(NULL));
	int size, value, i;
	int a[100], b[10];
	printf("Enter the size of the input:");
	scanf("%d", &size);
	while (check_error(size)==0)

	{
		printf("Invalid input enter the size of the input again:");
		scanf("%d", &size);
	}
	initialize_array(a, size);
	print_array(a, size);
	frequency(a, b, size);
	for(i=0; i<10; i++)
	{
		if(b[i]!=0)
		printf("Count of %d is %d\n", i, b[i]); 
	}
return 0;
}
int check_error(int size)
{
	if ((size<=100)&&(size>=1))
	return 1;
	else
	return 0;
}
void initialize_array(int a[], int size)
{
	int i;
	for (i=0; i<size; i++)
	a[i]=rand()%10;
}
void print_array(int a[], int size)
{
	int i;
	printf("Input array\n");
	for (i=0; i<size; i++)
	printf("%d ", a[i]);
	printf("\n");
}
void frequency(int a[], int b[], int size)
{
	int i, j, value, freq;
	value=0;
	j=0;
	for(value=0; value<10; value++)//Counter to cycle through each integer value//
	{
		freq=0;
		for(i=0; i<size; i++)//cycles through places in array a//
		{
			if(value==a[i])
			++freq;
		}
			b[j]=freq;
			++j;
	}

}

