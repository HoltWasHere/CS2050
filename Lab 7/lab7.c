/* 
 * File:   lab7.c
 * Author: hastg2
 *         Holt Skinner
 * Created on October 14, 2015, 3:02 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct state
{
    int lengthOfState;
    char* name;
    long int population;
    long int populationOver18;
} State;

typedef struct division
{
    char* name;
    State** states;
    int numStates;
    int lengthOfName;
} Division;

State* readStates(char*);
Division* readDivisions(State*, char*, int*);
int printAndSelectDivision(Division*, int);
void printStatesInDivision(Division*, int);
void freeMemory(Division*, State*, int);


void calculateHighestPercentDivision(Division* divisions, int numofDivs);

int main(int argc, char** argv) {

    if(argc != 3)
    {
        printf("Insufficient Arguments\n");
        return 1;
    }    
    
    State* states = readStates(argv[1]);//Create array of states
    
    if(states == NULL)//Check for file errors, and exits
    {
        return 1;
    }
    
    int numofDivs = 0;//Length of division array
    
    Division* divisions = readDivisions(states, argv[2], &numofDivs);//Create array of divisions
    
    if (divisions == NULL)//Check for file errors, frees malloced stuff and exits
    {
        freeMemory(divisions, states, numofDivs);
        return 1;
    }
    int selection = 0;
    
    while(1)//Run until user decides to quit
    {
        selection = printAndSelectDivision(divisions, numofDivs);
        
        if(selection ==9)
        {
            break;
        }
        
        printStatesInDivision(divisions, selection);
    }
  
    
    calculateHighestPercentDivision(divisions, numofDivs);

    freeMemory(divisions, states, numofDivs);//Prevent memory leaks!
    
    return (EXIT_SUCCESS);
}

State* readStates(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        printf("Could not open file %s\n", filename);
        fclose(fp);
        return NULL;
    }
    
    State* states = malloc(sizeof(State)*51);
    
    int i=0;//Counter
    for(i=0; i<51; i++)
    {
        
        fscanf(fp, "%d", &states[i].lengthOfState);//getting length of state name from file
        states[i].name = malloc(sizeof(char)*states[i].lengthOfState); //getting space for character array to hold name of state
        fscanf(fp, "%s %ld %ld", states[i].name, &states[i].population, &states[i].populationOver18); //reading in other info
        
    }
    
    return states;
}

Division* readDivisions(State* states, char* filename, int* numofDivs)
{
    FILE* fp = fopen(filename, "r");
    
    if(fp == NULL)//Error check for file problems
    {
        printf("Could not open file %s\n", filename);
        fclose(fp);
        return NULL;
    }
    
    fscanf(fp, "%d", numofDivs);//Read off number of divisions from file
    
    Division* divisions = malloc(sizeof(Division)* *numofDivs);//Reserve space for 9 divisions
    
    int i=0, j=0;//Counters
    int stateIndex=-1;
    for(i=0; i<*numofDivs; i++)//Cycle through number of divisions times, read in all info and save it
    {
        
        fscanf(fp, "%d %d", &divisions[i].lengthOfName, &divisions[i].numStates);
        //getting length of division name and num of states from file
        divisions[i].name = malloc(sizeof(char)* divisions[i].lengthOfName);//Malloc space for name of division
        fscanf(fp, "%s", divisions[i].name);//Save name
        divisions[i].states = malloc(sizeof(State*)*divisions[i].numStates);//Malloc array of pointers
        
        for(j=0; j<divisions[i].numStates; j++)//Read off state indexes and place pointer to states in divisions
        {
            fscanf(fp, "%d", &stateIndex);
            divisions[i].states[j] = &states[stateIndex];
            
        }  
    }    
    return divisions;
}

int printAndSelectDivision(Division* divisions, int numofDivs)
{
    int i = 0, selection;
    printf("Make a Selection:\n");
    
    for(i=0; i< numofDivs; i++)
    {
        printf("%d: %s\n", i, divisions[i].name);//Print out indexes and names
    }
    printf("9: Quit\n>");
    scanf("%d", &selection);//Get user input
    
    while(selection >9 || selection <0)//Error check
    {
        printf("Invalid selection, try again.");
        printf(">");
        scanf("%d", &selection);
    }
    return selection;
}

void printStatesInDivision(Division* divisions, int selection)
{
    int i=0;
    
    for(i=0; i<divisions[selection].numStates; i++)
    {
        printf("\n------State info------\n"
            "State name: %s\n"
            "Length of the name: %d\n"
            "Total population: %ld\n"
            "Total population over 18: %ld\n\n", 
            divisions[selection].states[i]->name,
            divisions[selection].states[i]->lengthOfState,
            divisions[selection].states[i]->population,
            divisions[selection].states[i]->populationOver18);      
    }
        
    return;
}
void freeMemory(Division* divisions, State* states, int numofDivs)
{
    int i=0;
    
    for(i=0; i<51; i++)
    {
        free(states[i].name);
    }
    
    free(states);
    if(divisions != NULL)
    {
        for(i=0; i<numofDivs; i++)
        {
            free(divisions[i].states);
            free(divisions[i].name);
        }
    }
    free(divisions);
    return;
}

void calculateHighestPercentDivision(Division* divisions, int numofDivs)
{
    int i =0, j=0, hold =0;
    long int total = 0, over18 = 0;
    double percent =0, max =0;
    for(i =0; i<numofDivs; i++)
    {
        for(j=0; j<divisions[i].numStates; j++)
        {
            total += divisions[i].states[j]->population;
            over18 += divisions[i].states[j]->populationOver18;
        }
        percent = (float)over18/(float)total;
        if(percent >max)
        {
            max =percent;
            hold =i;
        }
    }
    printf("%s\n%.2f%% Population Over 18 \n", divisions[hold].name, max*100);
}