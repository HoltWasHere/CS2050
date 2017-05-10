/* 
 * File:   main.c
 * Author: Holt
 *
 * Created on August 29, 2015, 8:56 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _car
{
    char color[20];
    char model[20];
    char brand[20];
    int year;
} Car; //Create Car Structure with color, model, brand, and year.

typedef struct _person
{
    char firstName[20];
    char lastName[20];
    int heightInInches;
} Person; //Data for each driver

Car* readCars(char* filename); //Takes in input filename, gives out car info
Person* readPeople(char* filename); //Takes in filename, gives out people info
void printData(Car* cars, Person* people); //Prints out data
void writePeopleToFile(Person* people);//Takes in people, prints the info to a file

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Invalid Input\n");
        return 1;
    }
    
    Car *prius = readCars(argv[1]); //Array of Cars from text file
    
    if (prius == NULL)//If there's a problem with the readCars function
    {
        printf("Error 1");
        return 1;
    }
    Person *holt = readPeople(argv[2]);//Array of people from text file
    
    if (holt == NULL)//If there's a problem with the readPeople function
    {
        printf("Error 2");
        return 1;
    }
    printData(prius, holt);//Print out onto screen
    
    writePeopleToFile(holt);//Write People Array into output.txt
    return (EXIT_SUCCESS);
}

Car* readCars(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", filename);
        return NULL;
    }
    
    Car* car_p = malloc(sizeof(Car)*256);
    
    int i=0;
    
    while (1)
    {
        fscanf(fp, "%d %s %s %s", &car_p[i].year, car_p[i].color, car_p[i].brand, car_p[i].model);
        
        i++;
        if (feof(fp))
        {
            break;
        }    
    }
    
    fclose(fp);
    return car_p;
}

Person* readPeople(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", filename);
        return NULL;
    }
   Person* person_p = malloc(sizeof(Person)*256);
    int i=0;
    
    while (1)
    {
        fscanf(fp, "%s %s %d", person_p[i].firstName, person_p[i].lastName, &person_p[i].heightInInches);
        
        i++;
        if (feof(fp))
        {
            break;
        }    
    }
    
    fclose(fp);
    
    return person_p;
}

void printData(Car* cars, Person* people)
{
    printf("%d %s %s %s\n%s %s %d\n", cars->year, cars->color, cars->brand, cars->model, 
            people->firstName, people->lastName, people->heightInInches);
    return;
}

void writePeopleToFile(Person* people)
{
    FILE* fp = fopen("output.txt", "a");
    
    if (fp == NULL)
    {
        printf("Cannot print to file\n");
        return;
    }
    
    fprintf(fp, "%s %s %d", people->firstName, people->lastName, people->heightInInches);
    
    fclose(fp);
    return;
}