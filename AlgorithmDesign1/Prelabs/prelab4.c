#include <stdio.h>

int main()
{
	int shape, side;
	float area; 	
		printf(	"Area calculation\n"
			"(1) Square\n"
			"(2) Cube\n"
			"(3) Circle\n"
			"Please make selection:");
		scanf("%d", &shape);

	while (shape<=0 || shape>3)
	
	{
		printf("Incorrect Choice\n"
			"Area calculation\n"
			"(1) Square\n"
			"(2) Cube\n"
			"(3) Circle\n"
			"Please make selection:");
		scanf("%d", &shape);
	}/*End While*/

	switch (shape)
	{		
		case 1:
			printf("Enter a positive number:\n");
			scanf("%d", &side);
			
			while (side <=0)
			{
				printf("Number can't be negative or zero\n");
				printf("Enter a positive number:\n");
				scanf("%d", &side);
			}
	
			area=side*side;
			printf("Length of the side of square is %d\n", side);
			printf("Area of square is %f\n", area);
		break;
		
		case 2:
			printf("Enter a positive number:\n");
			scanf("%d", &side);
			
			while (side <=0)
			{
				printf("Number can't be negative or zero\n");
				printf("Enter a positive number:\n");
				scanf("%d", &side);
			}
			area = 6*side*side;
			printf("Length of the side of cube is %d\n", side);
			printf("Area of cube is %f\n", area);
		break;
	
		case 3:
			printf("Enter a positive number:\n");
			scanf("%d", &side);
			
			while (side <=0)
			{
				printf("Number can't be negative or zero\n");
				printf("Enter a positive number:\n");
				scanf("%d", &side);
			}
			area =(float)3.1415926535897932384626433*side*side;/*#Nerd Alert*/
			printf("Radius of circle is %d\n", side);
			printf("Area of circle is %f\n", area);
		break;
	}	/*End Switch*/
return 0;
}	
