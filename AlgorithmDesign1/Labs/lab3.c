/*Holt Skinner
 * Lab 3
 * Lab K
 *Cheetos*/


#include <stdio.h>
#include <math.h>

int main()
{
	int side1, side2, side3, sentinal;
	float perimeter, area;
	
	while (sentinal !=-1)
		{
			/*Priming the Pump*/
			printf("Enter the first side\n");
			scanf("%d", &side1);

			while (side1<=0)
				{
					printf("Invalid value enter the number again\n");
					scanf("%d", &side1);
				}
				/*End side 1 while*/

			/*Priming the Pump*/
			printf("Enter the second side\n");
			scanf("%d", &side2);

			while (side2<=0)
				{
					printf("Invalid value enter the number again\n");
					scanf("%d", &side2);
				}
				/*End side 2 while*/

			/*Priming the Pump*/
			printf("Enter the third side\n");
			scanf("%d", &side3);

			while (side3<=0)
				{
					printf("Invalid value enter the number again\n");
					scanf("%d", &side3);
				}
				/*End side 3 while*/
				
				
			if (side1>=side2+side3||side2>=side1+side3||side3>=side1+side2)
				{
						printf("Three sides do not form a triangle\n"
						"Do you want to continue (type -1 to exit):\n");
					scanf("%d", &sentinal);	
				}	
				/*End if*/	
 			else
				{	perimeter =(float)((side1+side2+side3)/2);
					area=(float)(sqrt((perimeter)*(perimeter-side1)*(perimeter-side2)*(perimeter-side3)));

					printf("Area of the triangle is %f\n"
					"Do you want to continue (type -1 to exit):\n", area);
					scanf("%d", &sentinal);	
						
				}
				/*End else*/					
	
	} /*End full While*/

return 0;
}

