/* 
 * File:   Prelab4.c
 * Author: Holt Skinner
 *          Hastg2
 * Created on September 19, 2015, 6:54 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct computer
{
	char serialNumber[8];
	int price;
	int GBofRAM;
	int GBofHardDrive;
} Computer;

Computer* readComputers(char* filename);
void printComputers(Computer* comps);
Computer* insertionSortByPrice(Computer* comps);
Computer* selectionSortByPrice(Computer* comps);

int main(int argc, char** argv) {

    if(argc != 2)
    {
        printf("Insufficient Arguments\n");
        return 1;
    }
    
    Computer* comps = readComputers(argv[1]);//Read in computer data and save it
    printComputers(comps);//Print out original computer data
    
    comps = insertionSortByPrice(comps);//Sorts computer data by RAM
    printComputers(comps);//Prints out sorted comp data
    
    comps = readComputers(argv[1]);//ReRead in stuff, create"new" array
    comps = selectionSortByPrice(comps);//Sort by Price DESENDING 
    printComputers(comps);//Print out newly sorted data
    return (EXIT_SUCCESS);
}

Computer* readComputers(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    if (fp == NULL)//File error check
    {
        printf("Cannot open file computerdata.txt\n");
        return;
    }
    
    Computer* comps = malloc(sizeof(Computer)* 6);//Array of computers
    int i;//Counter
    
    for(i=0; i<5; i++)//Load array with computer data from file
    {
        fscanf(fp, "%s %d", comps[i].serialNumber, &comps[i].price);
        fscanf(fp, "%d %d", &comps[i].GBofRAM, &comps[i].GBofHardDrive);

    }
    fclose(fp);
    printf("Computers read in successfully.\n");
    
    return comps;
}

void printComputers(Computer* comps)
{
    int i;//Counter
    for (i=0; i<5; i++)//print array of computers
    {
        printf("Computer %d: \nSerial Number: %s\nPrice: $%d\nGB of RAM: %d \nGB of Hard Drive: %d\n\n", i+1, comps[i].serialNumber, comps[i].price, comps[i].GBofRAM, comps[i].GBofHardDrive);
    }
    return;
}

Computer* insertionSortByPrice(Computer* comps)//Sorts by RAM
{
    int i, j;//Counters
    Computer temp;
    
    for(i=1; i<5; i++)
    {
        temp = comps[i];//Save current element
        j = i-1;
        
        while((temp.price < comps[j].price) && (j>=0))
        {
            comps[j+1] = comps[j];
            j=j-1;
        }
        comps[j+1]=temp;
    }
    
    return comps;
}

Computer* selectionSortByPrice(Computer* comps)
{
    int lh, rh, i;//Counters
    Computer temp;
    
    for(lh=0; lh < 5; lh++)
    {
        rh = lh;
        for(i = lh; i<5; i++)
        {
            if(comps[i].price > comps[rh].price)
            {
                rh = i;
            }
        }
        temp = comps[lh];
        comps[lh] = comps[rh];
        comps[rh] = temp;
    }
    return comps;
}