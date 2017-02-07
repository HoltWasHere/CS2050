/* 
 * File:   lab4.c
 * Author: hastg2
 *          Holt Skinner
 * Created on September 23, 2015, 3:04 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct cellphone //20 phones in total
{
    char brand[20];
    char model[20];
    int priceNoContract;
    float screenDiameterInches;
    float customerRating;
    int numInStock;
} Phone;


void driver(char* filename);//Driver Function
Phone* readPhones(char* filename);
void printPhones(Phone* phones);
Phone* sortPhones(Phone* phones, int sortChoice);
Phone* selectionSort(Phone* phones, int sortChoice); //Bonus!!!


int main(int argc, char** argv) {
    
    if (argc != 2)
    {
        printf("Insufficient Arguments");
        return 1;
    }

    driver(argv[1]);
    
    return (EXIT_SUCCESS);
}

void driver(char* filename)
{
           
    Phone *phones = readPhones(filename);//Read in phones and store it into an array
    printPhones(phones);//Send it phone array and print it out
    
    int sortChoice = 0, toggle;
    
    while(1)
    {
        printf("----------------------------------------------"
                "\nHow would you like to sort these phones?\n"
                "1: Price\n"
                "2: Screen Diameter\n"
                "3: Rating\n"
                "4: Quit\n"
                "Option: ");
        scanf("%d", &sortChoice);//Printing out options 
        
        while (sortChoice<1 || sortChoice>4)
        {
            printf("Invalid Input, Try Again:");
            scanf("%d", &sortChoice);
        }
        
        if (sortChoice == 4)//If they quit
        {
            printf("Quitting...");
            free(phones);
            return;
        }
        
        printf("\nWhat type of sort do you want to use?\n"
                "0: Selection\n"
                "1: Insertion\n"
                "Option: ");
        scanf("%d", &toggle);
        
        if (toggle == 1)//insertion sort
        {
            phones = sortPhones(phones, sortChoice);// Call sort phones, return sorted array
        }
        else//Selection sort
        {
            phones = selectionSort(phones, sortChoice);
        }
        
        printPhones(phones);//Print out sorted array
   
    }//End large while    
    
    free(phones);
    return;
}
Phone* readPhones(char* filename)
{
    
    FILE* fp = fopen(filename, "rb");//Open File
    if(fp == NULL)//Error check
    {
        printf("Cannot open file phones.txt\n");
        return;
    }
    
    Phone* phones = malloc(sizeof(Phone)*20);//Create array of phones
    fread(phones, sizeof(Phone), 20, fp);//read in 20 phones
    
    return phones;
}
void printPhones(Phone* phones)
{
    int i=0;
    for(i=0; i<20; i++) //Print out phone data
    {
        printf("\n%s %s\nPrice: $%d\nScreen Size: %.2fin\nRating: %.2f\nIn Stock: %d\n", phones[i].brand, phones[i].model, phones[i].priceNoContract, phones[i].screenDiameterInches, phones[i].customerRating, phones[i].numInStock);
    }
    return;
}

Phone* sortPhones(Phone* phones, int sortChoice)
{
    int i, j;//Counters
    Phone temp;
    
    switch (sortChoice)
    {
        case 1: //Sort by price
        {
            printf("--------------Phones sorted by Price--------------------");//Label
            
            for(i=1; i<20; i++)
            {
                temp = phones[i];//Save current element
                j = i-1;
        
                while((temp.priceNoContract < phones[j].priceNoContract) && (j>=0))
                {
                    phones[j+1] = phones[j];
                    j=j-1;
                }//End While
                
                phones[j+1]=temp;
            }//End for
            
            break;
        }//End case 1
        
        case 2://Sort by screen size
        {
            printf("--------------Phones sorted by Screen Size--------------------");
            
            for(i=1; i<20; i++)
            {
                temp = phones[i];//Save current element
                j = i-1;
        
                while((temp.screenDiameterInches < phones[j].screenDiameterInches) && (j>=0))
                {
                    phones[j+1] = phones[j];
                    j=j-1;
                }//End While
                
                phones[j+1]=temp;
            }//End for    
            break;
        }//End case 2   
        
        case 3://Sort by rating
        {
            printf("--------------Phones sorted by Rating--------------------");
            
            for(i=1; i<20; i++)
            {
                temp = phones[i];//Save current element
                j = i-1;
        
                while((temp.customerRating < phones[j].customerRating) && (j>=0))
                {
                    phones[j+1] = phones[j];
                    j=j-1;
                }//End While
                
                phones[j+1]=temp;
            }//End for   
            break;
        }//End case 3
        
        default: break;
        
    }//End Switch       

    return phones;
}

Phone* selectionSort(Phone* phones, int sortChoice)
{
    int lh, rh, i;//Counters
    Phone temp;
    

    switch (sortChoice)
    {
        case 1://Sort by price
        {
            printf("--------------Phones sorted by Price--------------------");//Label

            for(lh=0; lh < 20; lh++)
            {
                rh = lh;
                for(i = lh; i<20; i++)
                {
                    if(phones[i].priceNoContract < phones[rh].priceNoContract)
                    {
                        rh = i;
                    }
                }
                temp = phones[lh];
                phones[lh] = phones[rh];
                phones[rh] = temp;
            }
            break;
        }//End Case 1
        
        case 2://Sort by screen diameter
        {
            printf("--------------Phones sorted by Screen Diameter--------------------");//Label

            for(lh=0; lh < 20; lh++)
            {
                rh = lh;
                for(i = lh; i<20; i++)
                {
                    if(phones[i].screenDiameterInches < phones[rh].screenDiameterInches)
                    {
                        rh = i;
                    }
                }
                temp = phones[lh];
                phones[lh] = phones[rh];
                phones[rh] = temp;
            }
            break;            
        }//End Case 2
        
        case 3://Sort by rating
        {
            printf("--------------Phones sorted by Rating--------------------");//Label

            for(lh=0; lh < 20; lh++)
            {
                rh = lh;
                for(i = lh; i<20; i++)
                {
                    if(phones[i].customerRating < phones[rh].customerRating)
                    {
                        rh = i;
                    }
                }
                temp = phones[lh];
                phones[lh] = phones[rh];
                phones[rh] = temp;
            }
            break;            
        }//End Case 3 
        
    }//End switch

    return phones;    
}