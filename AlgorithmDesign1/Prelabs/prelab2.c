#include <stdio.h>
int main()
{
	int num1, num2, sum, product;
	/*Entering First Number*/
	printf("Enter a number:\n"); 	
	scanf("%d",&num1);
	/*Invalid Response Safety Net for num1*/
	while (num1<=0)
		{
			printf("Invalid number enter the number again:\n");
			scanf("%d", &num1);
		}
	/*Entering Second Number*/
	printf("Enter the second number:\n");
	scanf("%d", &num2);
	/*Invalid Response Safety Net for num 2*/
	
	while (num2<=0)
	{	printf("Invalid number enter the number again:\n");
		scanf("%d", &num2);
	}	

	product = num1*num2;
	sum = num1+num2;

	printf("The product is: %d\n The sum is: %d\n", product, sum);
 
	return 0;
}
