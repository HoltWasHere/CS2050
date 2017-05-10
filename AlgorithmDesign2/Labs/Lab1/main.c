/* 
 * File:   main.c
 * Author: hastg2
 *
 * Created on August 26, 2015, 3:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function Prototypes
void readFile(char* filename); //Read data from file
void calculation(int x, int y, char* operation); //Do the calculation
void writeToFile(int x, int y, int z, char* operation); //Write data to file

int main(int argc, char** argv) {

    if (argc != 2)
    {
        printf("Invalid Input\n");
        return 1;
    }
    readFile(argv[1]);
 
    return (EXIT_SUCCESS);
}

void readFile(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", filename);
        return;
    }
    
    int num1, num2;
    char operation[80];
    while (1)
    {
        fscanf(fp, "%d %d", &num1, &num2);
        fscanf(fp, "%s", operation);
        if (feof(fp))
        {
            break;
        }     
        calculation(num1, num2, operation);
    }
    
    fclose(fp);
}
void calculation(int x, int y, char* operation)
{
    if (strcmp(operation, "Add") == 0)
    {
        writeToFile(x, y, x+y, "+");
    }    
    else if (strcmp(operation, "Subtract") == 0)
    {
        writeToFile(x, y, x-y, "-");
    }    
}
void writeToFile(int x, int y, int z, char* operation)
{
    FILE* fp = fopen("output.txt", "a");
    if (fp == NULL)
    {
        printf("Cannot write to file.");
        return;
    }
    
    fprintf(fp, "%d %s %d = %d\n", x, operation, y, z);
    
    fclose(fp);
}