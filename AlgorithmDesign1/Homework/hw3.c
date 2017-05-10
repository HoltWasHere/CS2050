//Holt Skinner
//HASTG2 (Hashtag)
//Homework 3
//LAB K//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
void display_menu();
int check_option(int option);
int check_size(int size);
void initialize_2Darray(int x[][MAX], int size);
void print_2Darray(int x[][MAX], int size);
void initialize_1Darray(int y[], int size);
void print_1Darray(int y[], int size);
int search_min(int x[][MAX], int r, int c, int size);
int count_match(int x[][MAX], int y[], int size, int r);
int closest_row(int x[][MAX], int y[], int size);
void sort_1Darray(int y[], int size);
void sort_2Darray(int x[][MAX], int size);
int main()
{
	srand(time(NULL));
	int option, size, r, c;
	int x[MAX][MAX], y[MAX];
	printf("Enter the size:");
	scanf("%d", &size);
	while (check_size(size)==0)//Makes user enter valid size//
	{
		printf("Invalid input enter the size of the array again:");
		scanf("%d", &size);
	}
	while (option!=6)//While to keep going until user inputs 6 to quit//
	{
		display_menu();
		scanf("%d", &option);
		while (check_option(option)==0)//Makes user input correct option//
		{
			printf("Invalid input, enter option again:");
			scanf("%d", &option);
		}
		initialize_2Darray(x, size);
		initialize_1Darray(y, size);
		switch (option)
		{
			case 1://Search min//
			printf("Search Minimum Operation\n");
			printf("2D array\n");
			print_2Darray(x, size);
			printf("Enter the row:");
			scanf("%d", &r);
			printf("Enter the column:");
			scanf("%d", &c);
			printf("The smallest number present in the row %d and column %d is %d.\n", r, c, search_min(x, r, c, size));
			break;//End case 1//

			case 2://Count match//
			printf("Count Match Operation\n");
			printf("2D array\n");
			print_2Darray(x, size);
			printf("1D array\n");
			print_1Darray(y, size);
			printf("Enter the row:");
			scanf("%d", &r);
			if (count_match(x, y, size, r)==0)//No numbers present//
			{
				printf("There are no numbers from the 1D array present in the 2D array.\n");
			}
			else
			{
				if (count_match(x, y, size, r)==1)//Grammar Nazi safety net\If one is present//
				{
					printf("There is %d number from the 1D array present in row %d of the 2D array.\n", count_match(x, y, size, r), r);
				}
				else//If there's more than one present//
					{
						printf("There are %d numbers from the 1D array present in row %d of the 2D array.\n", count_match(x, y, size, r), r);
					}//End small else//
			}//End large else//	
			break;//End case 2//	
			
			case 3://Closest row//
			printf("Closest Row Operation\n");
			printf("2D array\n");
			print_2Darray(x, size);
			printf("1D array\n");
			print_1Darray(y, size);
			printf("Row closest to the 1D array is row %d\n", closest_row(x, y, size));
			break;//End case 3//
			
			case 4://Sort 1D array//
			printf("Sort 1D Array Operation\n");
			printf("1D Array before sorting\n");
			print_1Darray(y, size);
			sort_1Darray(y, size);
			printf("1D Array after sorting\n");
			print_1Darray(y, size);
			break;//End case 4//
			
			case 5://SOrt 2D array//
			printf("Sort 2D Array Operation\n");
			printf("2D Array before sorting\n");
			print_2Darray(x, size);
			sort_2Darray(x, size);
			printf("2D Array after sorting\n");
			print_2Darray(x, size);
			break;//End case 5//
		}//End switch//
	}//End Large while//
return 0;
}
void display_menu()
{
	printf("Array operations, your options are:\n1:Search Min\n2:Count Matches\n3:Closest Row\n4:Sort 1D Array\n5:Sort 2D Array\n6:Exit\nEnter the operation you want to perform:");
}
int check_size(int size)
{
	if (size>=1 && size<=100)
	return 1;
	else
	return 0;
}
int check_option(int option)
{
	if (option>=1 && option<=6)
	return 1;
	else
	return 0;
}
void initialize_2Darray(int x[][MAX], int size)
{
	int i, j;//Row & column Counter//
	for (i=0; i<size; i++)//Row cycle//
	{
		for(j=0; j<size; j++)//Column cycle//
		{
			x[i][j]=(rand()%10);
		}//End column for//
	}//End row for//
}
void print_2Darray(int x[][MAX], int size)
{
	int i, j;//Row and column counter//
	for (i=0; i<size; i++)//Row cycle//
	{
		for(j=0; j<size; j++)//Column cycle//
		{
			printf("%3d", x[i][j]);
		}//End Column for//
		printf("\n"); 
	}//End row for//
}			
void initialize_1Darray(int y[], int size)
{
	int i;//Counter//
	for (i=0; i<size; i++)
	{
		y[i]=(rand()%10);
	}
}
void print_1Darray(int y[], int size)
{
	int i;//Counter//
	for (i=0; i<size; i++)
	{
		printf("%3d", y[i]);
	}
	printf("\n");
}
int search_min(int x[][MAX], int r, int c, int size)
{
	int i, j;
	int min=100;
	--r;
	--c;//Safety net for weird array numbering system//
	for (i=0; i<size; i++)
	{
		if (x[i][c]<min)
		min=x[i][c];
		for (j=0; j<size; j++)
		{
			if (x[r][j]<min)
			min=x[r][j];
		}
	}
return min;
}
int count_match(int x[][MAX], int y[], int size, int r)
{
	int i, j, match;//Counters//
	match=0;
	--r;//Wierd numbering system safety net//
	for (i=0; i<size; i++)//Cycle through 1D array//
	{
		for (j=0; j<size; j++)//Cycle through 2D array//
		{
			if (y[i]==x[r][j])
			++match;
		}//End inner for//
	}//End outer for//
return match;
}
int closest_row(int x[][MAX], int y[], int size)
{
	int i, j, d, t, w;
	d=101;//Minimum//
	w=0;//Holder//
	for (i=0; i<size; i++)//Rows//
	{	
		t=0;//Reset the total after each row//
		for (j=0; j<size; j++)//Columns for one row//
		{
			t+=(abs((x[i][j])-y[j]));//Assigns total of absolute difference to total//
		}//End inner for// 
		if (t<d)
		{
			d=t;//Assigns current total to minimum//
			w=i;//Assigns index to holder//
		}//End if//

	}//End outer for//
return ++w;
}
void sort_1Darray(int y[], int size)
{
	int i, j, hold;
	for (j=1; j<size; j++)
	{
		for (i=0; i<size-1; i++)
		{
			if (y[i]>y[i+1])
			{
				hold=y[i];
				y[i]=y[i+1];
				y[i+1]=hold;
			}//End if//
		}//End inner for//
	}//End outer for//
}
void sort_2Darray(int x[][MAX], int size)
{
	int i;
	for (i=0; i<size; i++)//Count rows//
	{
		sort_1Darray(x[i], size);
	}
}
