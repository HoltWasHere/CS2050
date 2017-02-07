/* 
 * File:   Lab3.c
 * Author: hastg2
 *         Holt Skinner
 * Lab Section A
 * Created on September 16, 2015, 3:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void collatzDriver();
void collatz(int);
void hexConverterDriver();
int hexConverter(int);

int main(void) {

    collatzDriver();//Call function and get input from user
    
    hexConverterDriver();//Call hex converter driver function
    
    return (EXIT_SUCCESS);
}

void collatzDriver()
{
    int input;
    
    while(1)
    {
        printf("\nEnter a positive number for the Collatz sequence or -1 to quit: ");
        scanf("%d", &input);
        
        if(input == -1)//If -1 is entered, quit
        {
            return;
        }
        
        while(input <= 0)
        {
            printf("Invalid input. Try again: ");
            scanf("%d", &input);
            
            if(input == -1)//If -1 is entered, quit
            {
                return;
            }
        }//End input<=0 while
        
        collatz(input);//Call function, send it input
        
    }// End input != -1 while

}

void collatz(int num)
{
    
    if(num == 1)
    {
        printf("1\n");
        return;
    }//End if
    
    else 
    {
        printf("%d -> ", num);
        if(num%2 == 0)//If it's even
        {
            collatz(num/2);
        }//End if
        
        else//If it's odd
        {
            collatz((num*3)+1);
        }//end small else
        
    }//End large else
    return;
}//End collatz

void hexConverterDriver()
{
    int input;
    
    while(1)
    {
        printf("\nEnter a number in hex to be converted to decimal or -1 to quit: ");
        scanf("%d", &input);
        
        if(input == -1)//If -1 is entered, quit
        {
            return;
        }
        
        while(input <= 0)
        {
            printf("Invalid input. Try again: ");
            scanf("%d", &input);
            if(input == -1)//If -1 is entered, quit
            {
                return;
            }
        }//End input<=0 while
        
        printf("\nYour number in decimal is %d\n", hexConverter(input));
    }// End input != -1 while
    return;
}

int hexConverter(int hex)
{
        if(hex<10)//Base Case
    {
        return hex;
    }
    int i=0, hexhold=hex, num;//Counter and save the original number value
    
    while(hexhold > 0)//Find the number of digits
    {
        hexhold/=10;
        i++;
    }//End while
    

    
    int mSig = hex/pow(10,(i-1));//Strip off last few digits
    
    int rest = hex%(int)pow(10,(i-1));//Remainder
    
    num = (mSig*pow(16, (i-1))) + hexConverter(rest); //Convert first digit to base 16 and send the rest back
    
    return num;
}