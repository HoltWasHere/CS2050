/* 
 * File:   prelab7.c
 * Author: Holt Skinner
 *          hastg2
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

void readStates(State*, char*);
void printStateInfo(State*, int);
void findTotalPercentage(State*, float*);
void freeStates(State*);

int main(int argc, char** argv) {

    if(argc != 2)
    {
        printf("Insufficient Arguments\n");
        return 1;
    }
    int id;
    State* states;
    
    states = malloc((sizeof(State) * 51));
    
    readStates(states, argv[1]);
    
    while(1)
    {
        printf("Put in a state ID to get information or -1 to quit: ");
        scanf("%d", &id);
        if(id<=0)
        {
            break;
        }
        printStateInfo(states, id);
        
    }
    float percent = 0.0;
    findTotalPercentage(states, &percent);
    freeStates(states);
    return (EXIT_SUCCESS);
}

void readStates(State* states, char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        printf("Could not open file %s\n", filename);
        fclose(fp);
        return;
    }
    
    int i=0;//Counter
    for(i=0; i<51; i++)
    {
        
        fscanf(fp, "%d", &states[i].lengthOfState);
        
        states[i].name = malloc(sizeof(char)*(states[i].lengthOfState));
        
        fscanf(fp, "%s %ld %ld", states[i].name, &states[i].population, &states[i].populationOver18); 
        
    }
    fclose(fp);
    return;
}

void printStateInfo(State* states, int id)
{
    printf("------State info------\n"
            "State name: %s\n"
            "Length of the name: %d\n"
            "Total population: %ld\n"
            "Total population over 18: %ld\n", 
            states[id-1].name, 
            (states[id-1].lengthOfState) - 1,
            states[id-1].population,
            states[id-1].populationOver18);
    return;
}

void findTotalPercentage(State* states, float* percent)
{
    int i = 0;
    double total = 0, over18 = 0;
    
    for(i; i<51; i++)
    {
        total += states[i].population;
        over18 += states[i].populationOver18;
    }
    *percent = (float)((over18/total)*100);
    printf("\nPercentage of US that is 18+: %.2f%\n", *percent);
    return;
}

void freeStates(State* states)
{
    int i = 0;
    for(i=0; i<51; i++)
    {
        free(states[i].name);
    }
    free(states);
    return;
}

