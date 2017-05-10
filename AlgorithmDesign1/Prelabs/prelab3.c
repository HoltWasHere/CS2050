#include <stdio.h>

int main(void)

{	int x;
	
	printf("Enter a number, -1 to end:\n ");
	scanf("%d", &x);
	while (x != -1)
	{	
		printf("The number entered is :%d \n",x );
		printf("Enter a number, -1 to end: \n");
		scanf("%d", &x);
	}
		printf("The number entered is -1 \n" "Exiting the program \n");
	return 0;

}
