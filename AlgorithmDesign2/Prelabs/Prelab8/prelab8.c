/* 
 * File:   prelab8.c
 * Author: Holt Skinner
 *          hastg2
 * Created on October 22, 2015, 4:20 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Integer_
{
    int num;
    struct Integer_* nextInt;
    struct Integer_* prevInt;
} Integer;

Integer* addInt(int, Integer*);
void printNumbers(Integer*);
void freeNumbers(Integer*);
Integer* deleteInt(Integer*);

int main(int argc, char** argv) {

    int option, num;
    
    Integer* stackTop = NULL;
    
    while(1)
    {
    printf("\nSelect an Option\n"
            "1: Add a Number\n"
            "2: Take a Number Off\n"
            "3: Print Numbers\n"
            "4: Quit\n"
            "Option:\n"
            ">");//Menu
    scanf("%d", &option);

        switch(option)
        {
        case 1:
            
            printf("Insert your Number:");
            scanf("%d", &num);
            stackTop = addInt(num, stackTop);
            break;
        
        case 2:
            
            stackTop = deleteInt(stackTop);
            break;
            
        case 3:
            
            printNumbers(stackTop);
            break;
            
        case 4:
            
            freeNumbers(stackTop);
            return 0;
            
        default:
            
            printf("\nInvalid Option, Try Again\n");                                 
            break;       
    }//End Switch        
}//End While
    
    return (EXIT_SUCCESS);
}

Integer* addInt(int num, Integer* stackTop)
{    
    Integer* new;
    if(stackTop == NULL)//New list
    {
        stackTop = malloc(sizeof(Integer));//Create new node
        stackTop->num = num;//Initialize
        stackTop->prevInt = NULL;
        stackTop->nextInt = NULL;
        return stackTop;
    }
    else//Not empty list
    {        
        
        new = malloc(sizeof(Integer));//Create new node
        new->num = num;
        new->prevInt = stackTop;//Set previous stackTop as the previous int
        new->nextInt = NULL;//Signify top
        stackTop->nextInt = new;
        return new;//Will make new the new Top
        
    }
}
Integer* deleteInt(Integer* stackTop)
{
    if(stackTop == NULL)
    {
        printf("\nThe list is empty\n");
        return;
    }
    stackTop->prevInt->nextInt = NULL;
    stackTop = stackTop->prevInt;
    return stackTop;
}
void printNumbers(Integer* stackTop)
{
    if(stackTop == NULL)
    {
        printf("\nThe list is empty\n");
        return;
    }
    Integer* temp = stackTop;
    
    while(temp->prevInt != NULL)//Go to bottom of stack
    {
        temp = temp->prevInt;
    }
    printf("\n");
    while(temp != NULL)
    {
        printf("%d->", temp->num);
        temp = temp->nextInt;
    }
    
    printf("\n");
    return;
}
void freeNumbers(Integer* stackTop)
{
    Integer* temp;
    while(stackTop != NULL)
    {
        temp = stackTop;
        stackTop = stackTop->prevInt;
        free(temp);
    }
    free(stackTop);
}
