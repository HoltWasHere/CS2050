#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int check_size(int);
void initialize_array(int size);
void print_array(int size);
int replace(int num, int i, int size);
int a[100]={};
int main()
{
	int size, num, i;
	srand(time(NULL));
	printf("Enter the size of the input:");
	scanf("%d", &size);
	while (check_size(size)==0)
	{
		printf("Invalid input. Enter the size of the input again:");
		scanf("%d", &size);
	}/*End Check Size While*/
	initialize_array(size);
	print_array(size);
	printf("Enter the index:\n");
	scanf("%d", &i);
	printf("Enter the new number:\n");
	scanf("%d", &num);
	if (replace(num, i, size)==-1)
	{	
		printf("Invalid index! Index should be smaller than the input size.");
	}
	else
	{
		replace(num, i, size);
		printf("Array after replacement operation\n");
		print_array(size);
	}
return 0;
}
	
int check_size(int size)
{
	if (size>100||size<1)
	return 0;
	else
	return 1;
}
void initialize_array(int size)
{
	int i;/*Counter*/
	for (i=0; i<size; i++)
	a[i]=rand()%10;
}
void print_array(int size)
{
	int i;/*Counter*/
	for (i=0; i<size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int replace(int num, int i, int size)
{
	if (i>size)
	return -1;
	else
	{
		a[i]=num;
		return 1;
	}
}
