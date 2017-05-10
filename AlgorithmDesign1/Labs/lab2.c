/* Holt Skinner
 * HASTG2
 * Lab 2
 * Section K
 * Fall is coming!*/

#include <stdio.h>
#include <math.h>

int main()

{
	int side1, side2, side3; 

 	
	/*Entering first side*/
	printf("Enter the first side:\n");
	scanf("%d", &side1);
		/*Invalid response safety net for side 1*/
		while (side1<=0)
			{
				printf("Invalid value enter the side again:\n");
				scanf("%d",&side1);
			}
	/*Entering second side*/
	printf("Enter the second side:\n");
	scanf("%d", &side2);
		/*Invalid response safety net for side 2*/
		while (side2<=0)
			{
				printf("Invalid value enter the side again:\n");
				scanf("%d", &side2);
			}

	/*Entering third side*/
	printf("Enter the third side:\n");
	scanf("%d", &side3);
		/*Invalid response safety net for side 3*/
		while (side3<=0)
			{
				printf("Invalid value enter the side again:\n");
				scanf("%d", &side3);
			}

	/*Assigning semi-perimeter*/
	float p=((float)side1+side2+side3)/2;

	/*Assigning Area*/
	float area =(float)(sqrt(p*(p-side1)*(p-side2)*(p-side3)));

	/*Printing Area*/
	printf("The area of the triangle is %f \n",area);


	/*BONUS*/
	/*Not a triangle*/
	if ((side1+side2<=side3)||(side2+side3<=side1)||(side3+side1<=side2))
		{
			puts("Three sides do not form a triangle\n");

		}
	/*Sides do form triangle*/ 
	/*Find the type*/	
	 	else
			/*Equilateral*/
		{	
			{
				if(side1==side2==side3)
		
				{
					puts ("Triangle is an equilateral triangle\n");
				}
			
			}
			/*Isosceles*/
			{
				if((side1==side2)||(side2==side3)||(side1==side3))	
				{
					puts ("Triangle is an isosceles triangle\n");
				}
			}

			{	
				if(side1!=side2!=side3)
				{
					puts ("Triangle is a scalene triangle\n");
				}
			}
		}
        return 0;
}

