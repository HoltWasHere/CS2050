#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void displayMenu();
int errorCheck(int);
int generateNumber(void);
int cube(int);
float division(int, int);
int main()
{	
	srand(time(NULL));
	int o, r, c, x, y;
	float d;
	displayMenu();
	printf("Enter your choice:");
	scanf("%d", &o);
	while (errorCheck(o)==0)
	{
		printf("Invalid choice enter the choice again:");
		scanf("%d", &o);
	}
	x=generateNumber();
	if (o==1)
	{
		printf("Cube of %d is %d\n", x, cube(x));
	}
	else 
	{
		y=generateNumber();
		printf("Div(%d,%d)=%.2f\n", x, y, division(x,y));
	}
return 0;
}


void displayMenu()
{
	printf("Please select an operation\n1: Cube\n2: Division\n");
}

int errorCheck(int o)

{

	if (o<1 || o>2)
	return 0;
	else 
	return 1;
}

int generateNumber(void)
{
	int x;
	x=rand()%10;
return x;
}

int cube(int x)
{
	int c;
	c=pow(x, 3);
return c;
}

float division(int x, int y)
{
	float d;
	if (x==0 || y==0)
	return 0;
		else
		{
			if (x>y)	
			d=(float)x/(float)y;
				else
				d=(float)y/(float)x;
		return d;
		}
}
