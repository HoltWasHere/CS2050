/*
 * Holt Skinner
 hastg2
 Lab K
 Lab 1
 August 29, 2014
 */

#include <stdio.h>

int main ()
{
	int x,y,z,sum;


	//this is a print statement
	printf("\nEnter the first number: ");
	scanf("%d", &x);

	printf("\nEnter the second number: ");
	scanf("%d", &y);

	printf("\nEnter the third number: ");
	scanf("%d", &z);

	sum = x + y + z;

	printf("\nSum of the three numbers is %d.\n", sum);

	return 0;
}

