//Holt Skinner
//HASTG2 (Hashtag)
//LabK Lab 5
//tablet//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int generateNumber();
void displayMenu();
int errorCheck(int option);
int checkGuess(int guess, int answer);
void printResult(int result, int answer);
int option, guess, answer, result, replay;
int main()
{
	srand(time(NULL));
	displayMenu();
	scanf("%d", &option);
	while (errorCheck(option)==0)//Checking for Errors//
	{
		printf("Invalid guess enter your choice again:");
		scanf("%d", &option);
	}//End Error Check While//
	answer=generateNumber();
	result=checkGuess(option, answer);
	printResult(result, answer);
		
return 0;
}//End Main//

void displayMenu()
{
	printf("Please take a guess\n0: Heads\n1: Tails\nEnter your guess:");
}

int errorCheck(int option)
{
	if (option==0 || option==1)
	return 1;
	else
	return 0;
}

int generateNumber(void)
{
	answer=rand()%2;
return answer;
}
int checkGuess(int guess, int answer)
{
	if (guess==answer)
	return 1;
	else
	return 0;
}
void printResult(int result, int answer)
{	
	if (result==1)

	{	
		if(answer==1)
		{
			printf("Your choice was tails and it is a correct guess\n");
		}
		else
		{
			printf("Your choice was heads and it is a correct guess\n");
		}
	}	
	else
	{	
		if (answer==0)
		{
			printf("Your choice was tails and it is an incorrect guess\n");
		}
		else
		{
			printf("Your choice was heads and it is an incorrect guess\n");
		}
	}
}
