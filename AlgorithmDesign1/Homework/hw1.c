/*Homework 1*/
/*Tax Calculator*/
/*Holt Skinner*/
/*HASTG2*/
/*Lab K*/

#include <stdio.h>
int main()
{
	int status, income, rate;
	float tax, netincome;

	/*Entering Filing Status*/
	printf("Filing Status\n"
		"(1) Single\n"
		"(2) Married\n"
		"(3) Head of Household\n"
		"(0) Quit Program\n"
		"Please make selection: \n");
	scanf("%d" ,&status);	
		while (status < 0 || status > 3)
		{
			printf("Invalid choice, make a selection again: \n");
			scanf("%d", &status);
		}
	if (status == 0)
		printf("Exiting the tax calculator.\n");
	else
	{
		
		printf("Enter the annual income: \n");
		scanf("%d", &income);
		while (income <= 0)
		{
			printf("Invalid income, enter the income again. \n");
			scanf("%d", &income);
		}
		
	switch (status)
	
	{	
		case 1:
			if (income >=0 && income <20000)
				{rate=10;}
					if (income >=20000 && income<50000)
						{rate=20;}
							if (income >= 50000 && income < 100000)
								{rate=30;}
									if (income >=100000 && income< 250000)
										{rate=35;}
											if (income >=250000)
												{rate=40;}
		break; /*End Case 1*/
										
		case 2:
		
			if (income >=0 && income <30000)
				{rate=10;}
					if (income >=30000 && income<60000)
						{rate=20;}
							if (income >= 60000 && income < 125000)
								{rate=30;}
									if (income >= 125000 && income< 300000)
										{rate=35;}
											if (income >=300000)
												{rate=40;}
		break; /*End Case 2*/				 									
		case 3:
			
			if (income >=0 && income <50000)
				rate=10;
					if (income >=50000 && income<100000)
						rate=20;
							if (income >= 100000 && income < 250000)
								rate=30;
									if (income >= 250000 && income< 500000)
										rate=35;
											if (income >=500000)
												rate=40;
		break; /*End Case 3*/									 	 
	}/*End Switch*/
	
	tax =(float)income*(float)rate/100;
	netincome = (float)income - tax;
	
	printf("Your tax rate is:%d%%\n", rate);
	printf("You pay %.2f in taxes\n", tax);
	printf("After taxes, your net income is:%.2f\n", netincome);
}/*End Else*/				

return 0;
}
