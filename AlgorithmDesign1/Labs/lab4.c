/*Holt Skinner
 * HASTG2
 * Lab 4
 * Lab K
 *HackMizzou*/
#include <stdio.h>

int main()
{

	int type, year, counter;
	float compoundinterest, amount, rate, interest, x, z, h, n, p;
	
	/*Entering Account Type*/
	printf("Bank account type\n"
		"(1) Checking\n"
		"(2) Savings\n"
		"(3) Fixed Deposit\n"
		"Please make a selection:");
	scanf("%d", &type);
		/*Invalid Account Type Response Safety Net*/
		while (type<1 || type>3)
		{
			printf("Incorrect choice, please choose again\n");
			printf("Bank account type\n"
			"(1) Checking\n"
			"(2) Savings\n"
			"(3) Fixed Deposit\n"
			"Please make a selection:");
			scanf("%d", &type);
		}
	/*Assigning Rates to Account Types*/
	switch (type)
	{
		case 1:
			rate = .01;
		break;
		
		case 2:
			rate = .03;
		break;
		
		case 3:
			rate = .07;
		break;
	}
	
	/*Entering Year*/
	printf("Enter a year:");
	scanf("%d", &year);
		/*Invalid Year Response Safety Net*/
		while (year<1 || year>10)
		{
			printf("Incorrect value, year should be between 1-10\n");
			printf("Enter a year:");
			scanf("%d", &year);
		}
	
	/*Entering Amount*/
	printf("Enter the amount:");
	scanf("%f", &amount);
		
	/*Invalid amount safety net*/
		
		while (amount <=0)
		{
			printf("Incorrect value, enter the amount again:\n");
			scanf("%f", &amount);
		}
	x=1;
	for (counter=1; counter<=year; counter++)
		{
			x=x*(1+rate);
		}
	compoundinterest = amount*x;
	interest = compoundinterest - amount;
	printf("Total amount after 3 years is: $%.2f\n", compoundinterest);
	printf("Total interest earned on the amount $%.2f is $%.2f\n", amount, interest);
	
	printf("Bonus Part\n"
		"Enter a number:");
	scanf("%f", &h);
	printf("Enter an exponent:");
	scanf("%f", &n);
	h = power(h, n);
	printf("pow(%.2f, %.2f)=%f)", h, n, p);
return 0;
}/*End Main*/

float power(float h, float n)
{
	int thepowfactor;
	float p=1;
	for (thepowfactor=1, thepowfactor<=n, thepowfactor++)
		{
			p=p*h;
		}
return p;
}	
