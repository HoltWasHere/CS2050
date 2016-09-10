/* 
 * File:   Prelab3.c
 * Author: Holt Skinner
 *          Hastg2
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int num);
int costFunction(int num);
void collatz(int);

int main(int argc, char** argv) {

    int mode=1;
    
    while(mode > 0)
    {
        printf("\nThe Ultimate Calcumalator!\n\n\t0:Quit\n\t1:Factorials!\n\t2:Cost Per Steps\n\t3:Collatz Conjecture\n");
        scanf("%d", &mode);
        
        switch(mode)
        {
            case 0:
                    break;
            
            case 1:
            {
                    int input1;
                    printf("Input the number you want to find the factorial:");
                    scanf("%u", &input1);
                    if(input1 < 0)
                    {
                        break;
                    }
                    int Factorial = factorial(input1);
                    printf("\nThe factorial of %d is %d.\n", input1, Factorial);
                    break;
            }//End Case 1
            
            case 2:
            {
                    int input2;
                    printf("How many steps are there to complete the task?");
                    scanf("%d", &input2);
                    if(input2<0)
                    {
                        break;
                    }
                    int cost = costFunction(input2);
                    printf("The cost is $%d.\n", cost);
                    break;
            }//End case 2
            
            case 3: 
            {
                int input3;
                printf("What number do you want to input?");
                scanf("%d", &input3);
                while (input3 <= 0)
                {
                    printf("Invalid Input, Try Again:");
                    scanf("%d", &input3);
                }
                collatz(input3);
                break;
            }
                    
            
            default: printf("Invalid Option, try again.\n");
                    break;
                    
        }//End Switch         
    }//End While
 
    return (EXIT_SUCCESS);
}

int factorial(int num)
{    
    if (num == 1 || num == 0)
    {
        return 1;
    }
    
    else 
    {
        int Factorial = num * (factorial(num-1));
        return Factorial;
    }
    
}

int costFunction(int num)
{
    
    if(num == 0)
    {
        return 2;
    }
    else
    {
        int cost = costFunction(num-1) + (4*num);
        return cost;
    }
    
}

void collatz(int num)
{
    
    if(num == 1)
    {
        printf("1\n");
        return;
    }
    else 
    {
        printf("%d -> ", num);
        if(num%2 == 0)//If it's even
        {
            collatz(num/2);
        }
        else//If it's odd
        {
            collatz((num*3)+1);
        }
    }
}