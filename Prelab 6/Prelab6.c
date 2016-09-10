/* 
 * File:   Prelab6.c
 * Author: Holt
 *         Hastg2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//these are the dimensions of the matrix, to be mainly used for the 2D matrix. 
//If you wish to experiment with different values, just change the 8 in the below lines
//to whatever you like. Make it non-square, and see what happens!
#define ROWS 8
#define COLUMNS 8



/*
 * HEY, YOU! DON'T SCROLL DOWN YET! READ THIS!
 * 
 * WHEN YOU ARE DONE, GO BACK AND LOOK CLOSELY AT THE FUNCTIONS. THE SHUFFLE FUNCTIONS RETURN
 * VOID, YET THE MATRIX IS STILL SHUFFLED! WHY IS THAT?! IT IS VERY IMPORTANT YOU FIGURE OUT 
 * WHY THIS WORKS, SO WHEN YOU ARE DONE WITH FILLING IN CODE, THIS IS PART 2. 
 * 
 * Your answer to part 2 here: 
 * 
 * The double pointer causes the matrix to be called by reference, so nothing needed to be returned to shuffle the matrix.
 * 
 * ALSO
 * 
 * YOU MIGHT BE CONFUSED ON WHAT THOSE DEFINE THINGS ARE ABOVE. THEY ARE BASICALLY CONSTANTS.
 * FEEL FREE TO USE THEM IN THE CODE YOU ADD...THEY MIGHT BE USEFUL! LOOK AROUND IN THIS CODE 
 * TO SEE HOW YOU MIGHT USE THEM. 
 */



/*
 * Alright, so for this prelab you will be dealing with random numbers and characters in a 2D matrix.
 * 
 * There will be 2 ways you will do this: using a double pointer, and using a single pointer. The double pointer
 * will point to an array of pointers, each of which will be pointing to an array of elements. The array of pointers
 * signify the rows, and each pointer is pointing to a 'column' of elements. 
 * 
 * NOTE: YOU MIGHT SET IT UP WITH ROWS AND COLUMNS FLIPPED. In other words, to get an element, you will either do
 * arr[row][column] or arr[column][row]. For our purposes, it doesn't matter. Experiment with the sizes of the array 
 * to see which is which! See above on how to change the dimensions. 
 * 
 * For the single pointer, the pointer will be pointing to one array, with all the elements laid out in a line, but
 * we will treat it as a 2D matrix (think of the 2D matrix as pulled apart and flattened out). Basically the first
 * 8 elements in the array will be row 1, the next 8 will be row 2, and so on. 
 * 
 * 
 * Below, you will find all the functions you need, with incomplete logic. You are to fill in what you need to make it 
 * work. Pay attention to the code that you are instructed to not touch! You will be provided with all variables that 
 * you need to utilize to be successful. Look for the giant line of *s for places that you should have stuff written.
 * 
 * I REPEAT: CHANGE NOTHING UNLESS YOU ARE TOLD TO DO SO! 
 * 
 * If you did it right, you should be able to run the program and get nice output with no seg faults. I am aware that
 * Netbeans sometimes tries to save you, so make sure you go back over your code once you get good output to make sure
 * you do it correctly. *********HINT********: The secret to doing really well in labs from now on is to draw out all
 * your pointers and arrays, and to be able to follow your code EXACTLY AS WRITTEN (not as intended!) and follow your 
 * pointers around. I guarantee that you will be able to be a more successful coder AND debugger if you are able to do
 * this technique. Start with this prelab!
 * 
 */

//each space in the array is one of these squares. You need to fill in the number and the character for each. 
typedef struct square
{
    int i;
    char c;
} Square;

//prototypes. See below for more details
Square** initializeMatrix(void);
void printMatrixNumbers(Square**);
void printMatrixLetters(Square**);
void shuffleMatrix(Square**);

Square* initialize1DMatrix(void);
void print1DMatrixLetters(Square*);
void print1DMatrixNumbers(Square*);
void shuffle1DMatrix(Square*);


//Don't touch this code!
int main(void)
{
    srand(time(NULL));

    Square** matrix = initializeMatrix();
    
    while(1)
    {
        printf("Print which set?: ");
        printf("\n1. letters\n2. numbers\n3. shuffle matrix\n4. move to 1D matrix");
        printf("\n>");
        int choice;
        scanf("%d", &choice);

        if(choice == 1)
        {
            printMatrixLetters(matrix);
        }
        else if(choice == 2)
        {
            printMatrixNumbers(matrix);
        }
        else if(choice == 3)
        {
            shuffleMatrix(matrix);
        }
        else if(choice == 4)
        {
            break;
        }
        else
        {
            printf("Didn't understand that input. Try again\n\n");
        }
    }

    Square* matrix2 = initialize1DMatrix();
    printf("\n\nNow for the 1D array:\n\n");
    
    while(1)
    {
        int choice;
        printf("Print which set?: ");
        printf("\n1. letters\n2. numbers\n3. shuffle matrix\n4. quit");
        printf("\n>");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            print1DMatrixLetters(matrix2);
        }
        else if(choice == 2)
        {
            print1DMatrixNumbers(matrix2);
        }
        else if(choice == 3)
        {
            shuffle1DMatrix(matrix2);
        }
        else if(choice == 4)
        {
            break;
        }
        else
        {
            printf("Didn't understand that input. Try again\n\n");
        }
    }
    
    return 0;
}
//End of main code


//Alright, let's start doing things! This function will initialize the DOUBLE POINTER for the 2D Matrix, and 
//return the address back to main.
Square** initializeMatrix()
{
    //this will be used to randomize the matrix. See below for more info.
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    
    //I've got rows and columns in the matrix, as defined at the top of the program. 
    int row, column;
    
    /*********************************************************************************/
    //Here's the double pointer! You should probably have it point to something first! But what? CAREFUL!
    Square** matrix = malloc(sizeof(Square)*(ROWS));
    
    //Here's where that initial array of pointers all get their own array of elements, signifying columns.
    //How does each pointer get its own array to point to?
    for(row = 0; row < ROWS; row++)
    {
        /*********************************************************************************/
        //You should be doing something here! What is the for loop doing again?
        matrix[row] = malloc(sizeof(Square)*COLUMNS);
    }

    //Now it's time for all elements to get values!
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //Each element needs a number and a character assigned to it.
                //For the number, you should do a random number from 0-9. You should know how to do this.
                //For the character, use the array at the beginning of this function. Get a random number from
                //0-25, and use that as the index to get the character from the above array. 
                
                //Give that number and character to the matrix element here.
                matrix[row][column].i = rand()%10;
                matrix[row][column].c = letters[rand()%26];
            }
    }
    return matrix;
}

//Prints out each matrix element's number nicely. See the output for a pretty box.
void printMatrixNumbers(Square** matrix)
{
    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                printf("%d ", matrix[row][column].i);  
            }
            printf("\n");
    }
}

//Prints out each matrix element's letter nicely. See the output for a pretty box.
void printMatrixLetters(Square** matrix)
{
    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                printf("%c ", matrix[row][column].c);
            }
            printf("\n");
    }
}

//This function will take the randomly generated matrix, and shuffle around elements doing a very basic swap.
//Doesn't shuffle the matrix very well (in a random enough way), but that's fine...we'll just do it about 50000 times. 
void shuffleMatrix(Square** matrix)
{
    int randRow, randColumn, randRow2, randColumn2, passNumber = 0;
    Square tmp;
    
    for(passNumber; passNumber < 50000; passNumber++)
    {
        /*********************************************************************************/
        //Here you will get random numbers for each row/column pair. Each row/column pair will
        //get you one of the elements that will be swapped.
        randRow = rand()%(ROWS);
        randColumn = rand()%(COLUMNS);
        randRow2 = rand()%(ROWS);
        randColumn2 = rand()%(COLUMNS);
        
        //Once you know which 2 elements you will be swapping, swap them! You should know how 
        //to do this from sorting.
        tmp = matrix[randRow][randColumn];
        matrix[randRow][randColumn] = matrix[randRow2][randColumn2];
        matrix[randRow2][randColumn2] = tmp;
    }
}

//Here begins the 2D Matrix code to represent it using a single pointer! 
Square* initialize1DMatrix(void)
{
    //Same stuff as before. 
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    
    /*********************************************************************************/
    //Now we have a single pointer. This probably should be pointing to something...but what?
    Square* matrix = malloc(sizeof(Square)*(ROWS*COLUMNS));
    
    //Woah, what is this thing?! We've got the above pointer keeping track of where the beginning is,
    //but we need this other pointer to go down the line and assign values to each element. This is so that
    //all the elements will be changed, but we can still keep track of the beginning with the above variable!
    Square* ticker = matrix;

    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //USE THE TICKER! The ticker should always point to the current element that needs new
                //random values. Calculate the random values just like before, and assign the values
                //to the element that ticker is pointing to.
                matrix+ticker->i = rand()%10;
                matrix+ticker->c = letters[rand()%26];
                //then after that, how does the ticker get to the next element? POINTER MATH
                ticker++;
            }
    }
    return matrix;
}

//Prints out each matrix element's letter nicely. See the output for a pretty box.
void print1DMatrixLetters(Square* matrix)
{
    //IT'S THE TICKER AGAIN!
    Square* ticker = matrix; 
    
    int column, row;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                //BUT WAIT! I CAN ONLY USE THE TICKER! DON'T MOVE THE POINTER 'MATRIX'!
                printf("%c ", (matrix+ticker)->c);
                ticker++;
            }
            printf("\n");
    }
}

//Prints out each matrix element's number nicely. See the output for a pretty box.
void print1DMatrixNumbers(Square* matrix)
{
    //SO MANY TICKERS!
    Square* ticker = matrix; 
    
    int column, row;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                //BUT WAIT! I CAN ONLY USE THE TICKER! DON'T MOVE THE POINTER 'MATRIX'!
                printf("%d ", (matrix+ticker)->i);
                ticker++;                   
            }
            printf("\n");
    }
}

//This function will take the randomly generated matrix, and shuffle around elements doing a very basic swap.
//Doesn't shuffle the matrix very well (in a random enough way), but that's fine...we'll just do it about 50000 times. 
void shuffle1DMatrix(Square* matrix)
{
    //literally the same stuff as before.
    int randRow, randColumn, randRow2, randColumn2,passNumber = 0;
    Square tmp;
    
    for(passNumber; passNumber < 50000; passNumber++)
    {
        /*********************************************************************************/
        //Same thing as before. Get the row/column pairs for the 2 elements to be swapped
        
        //But....but it's a SINGLE POINTER! This is the hardest part of the whole prelab!
        //I can't treat the single pointer like the double pointer, so how do I use 
        //the row and column values to get to the element I need? Once you figure it out,
        //swap the two elements as before.
        
    }
}