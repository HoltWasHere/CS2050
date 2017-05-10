//Holt Skinner
//HASTG2 (#Hashtag):)
//Lab K
//Homework 2-Casino//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display_menu();
int errorCheck(int);
int throw_dice();
int even_odd(int dice, int option);
int lucky_seven(int x, int option);
int guess_number(int x, int guess);
int main()
{
	int money, game, dice, option, bet;
	srand(time(NULL));
	money=100;
	while ((game!=4)&&(money>0))//While to allow quit option/avoid playing without money//
	{
		display_menu();
		scanf("%d", &game);
		errorCheck(game);
		dice=throw_dice();
		while (errorCheck(game)==0)//While to prevent invalid responses//
		{
			printf("Invalid choice\n");
			display_menu();
			scanf("%d", &game);
		}
		switch (game)//Switch statement for choosing game//
		{	
			case 1: 
				printf("Take a guess (1) Even (2) Odd: ");
				scanf("%d", &option);
				printf("You have $%d to bet.\nHow much do you want to bet? $", money);
				scanf("%d", &bet);
				
				if ((even_odd(dice, option))==1)
				{
					printf("You win! Your guess is correct. The sum of the dice is %d.\n", dice);
					money=money+2*bet;
				}
				else
				{
					printf("You lost! Your guess is incorrect. The sum of the dice is %d.\n", dice);
					money=money-bet;
				}
			break;//End Case 1//
			case 2: 
				printf("Enter your guess (1) Lucky 7 (2) Above 7 (3) Below 7: ");
				scanf("%d", &option);

				printf("You have $%d to bet.\nHow much do you want to bet? $", money);
				scanf("%d", &bet);
	 		
				if((lucky_seven(dice, option))==1)
				{
					printf("You win! Your guess is correct. The sum of the dice is %d.\n", dice);
					if (option==1)
					money=money+7*bet;
					else 
					money=money+2*bet;
				}
				else
				{
					printf("You lost! Your guess is incorrect. The sum of the dice is %d.\n", dice);
					money=money-bet;
				}
			break;//End Case 2//
			case 3:
				printf("Guess a number between 2-12: ");
				scanf("%d", &option);
				printf("You have $%d to bet.\nHow much you you want to bet? $", money);
				scanf("%d", &bet);
	 		
				if((guess_number(dice, option))==1)
				{
					printf("You win! Your guess is correct. The sum of the dice is %d.\n", dice);
					money=money+5*bet;
				}
				else
				{
					printf("You lost! Your guess %d is incorrect. The sum of the dice is %d.\n", option, dice);
					money=money-bet;
				}
			break;//End Case 3//
 
		}//End Switch//
					
	}//End Quit Option/Money While Loop//
	if(money<=0)
	printf("You lost all of your money!\n");
	printf("Total money after gambling is $%d.\n", money);

return 0;
}
void display_menu()
{
	printf("Welcome to the casino!\nGames you can play\n1:Even/Odd\n2:Lucky seven\n3:Guess the number\n4:Exit\nPlease select an option:");
}
int errorCheck(int game)
{
	if (game>4 || game<1)
		return 0;
	else
		return 1;
}
int throw_dice()
{
	int dice;
	dice=(((rand()%6)+1)+((rand()%6)+1));
	return dice;
}
int even_odd(int dice, int option)
{
	if ((dice%2==0 && option==1)||(dice%2==1 && option==2))//If both even or both odd, the user wins//
		return 1;
	else//Otherwise, they lose//
		return 0;
}
int lucky_seven(int dice, int option)
{
	if ((dice==7 && option==1)||(dice>7 && option==2)||(dice<7 && option==3))//If the user wins//
	return 1;
	else//If the user loses//
	return 0;
}
int guess_number(int dice, int option)
{
	if (dice==option)//If the user wins//
		return 1;
	else//If the user loses//
		return 0;
}

