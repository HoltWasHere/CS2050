/* 
 * File:   HW2.c
 * Author: Holt Skinner
 *          Hastg2
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct shield
{
    char name[50];
    int price;
    int defense;
    int weight;
    struct shield* nextShield;
} Shield;
typedef struct sword
{
    char name[50];
    int price;
    int damage;
    struct sword* nextSword;
} Sword;

typedef struct hero
{
    char name[30];
    int health;
    int defense;
    int speed;
    int attack;
    int luck;
    Shield* shield;
    Sword* sword;
} Hero;

typedef enum print_option
{
    SHIELDS,
    SWORDS,
    ALL
} print_option;

typedef struct category
{
    char name[20];
    int numInCategory;
} Category;


void Shop(Hero*);
Hero* getHeroes(void);
void printHeroes(Hero*, print_option);
void shieldSelection(Shield**, Hero*, int*);
void swordSelection(Sword**, Hero*, int*);
void printShields(Shield*);
void printSwords(Sword*);
Shield* readShields(FILE*, int*);
Sword* readSwords(FILE*, int*);
Shield* extractShieldFromList(Shield**, int);
Sword* extractSwordFromList(Sword**, int);
void freeShields(Shield*);
void freeSwords(Sword*);
void freeHeroes(Hero*);

//DO NOT TOUCH THIS FUNCTION
int main() {

    Hero* heroes = getHeroes();
    if(!heroes)
    {
    	return;
    }
    Shop(heroes);
    
    freeHeroes(heroes);
    return (EXIT_SUCCESS);
}

//DO NOT TOUCH THIS FUNCTION
void Shop(Hero* heroes)
{
    FILE* fp = fopen("shields.bin", "rb");
    
    if(!fp)
    {
        printf("shields failed to open\n");
        return;
    }

    FILE* fp2 = fopen("swords.bin", "rb");
    if(!fp2)
    {
        printf("swords failed to open\n");
        return;
    }

    int numShields = 0, numSwords = 0;
    
    Shield* shields = NULL;
    shields = readShields(fp, &numShields);
       
    if(fclose(fp) != 0)
    {
    	printf("Couldn't close the shields file...this is awkward.\nWill try to continue with the program.\n");
    }
    
    

    Sword* swords = NULL;
    swords = readSwords(fp2, &numSwords);
    if(fclose(fp2) != 0)
    {
    	printf("Couldn't close the swords file...this is awkward.\nWill try to continue with the program.\n");
    }

	if(!shields)
    {
    	printf("I got no list back from readShields! What happened?\n");
    	return;
    }

    //decent range to check for bad values.
    if(numShields > 40 || numShields < 5)
    {
    	printf("Your number of shields is invalid! What happened?\n");
    	return;
    }

    //This will seg fault if your list is bad!
    Shield* tmp = shields;
    while(tmp != NULL)
    {
    	tmp = tmp->nextShield;
    }

    if(!swords)
    {
    	printf("I got no list back from readSwords! What happened?\n");
    	return;
    }

	//decent range to check for bad values.
    if(numSwords > 40 || numSwords < 5)
    {
    	printf("Your number of swords is invalid! What happened?\n");
    	return;
    }

    //This will seg fault if your list is bad!
    Sword* tmp2 = swords;
    while(tmp2 != NULL)
    {
    	tmp2 = tmp2->nextSword;
    }

    while(1)
    {
		if(!shields)
	    {
	    	printf("I don't have a list of shields! What happened?\n");
	    	return;
	    }

	    //decent range to check for bad values.
	    if(numShields > 40 || numShields < 0)
	    {
	    	printf("Your number of shields is invalid! What happened?\n");
	    	return;
	    }

	    //This will seg fault if your list is bad!
	    Shield* tmp = shields;
	    while(tmp != NULL)
	    {
	    	tmp = tmp->nextShield;
	    }

	    if(!swords)
	    {
	    	printf("I don't have a list of swords! What happened?\n");
	    	return;
	    }

		//decent range to check for bad values.
	    if(numSwords > 40 || numSwords < 0)
	    {
	    	printf("Your number of swords is invalid! What happened?\n");
	    	return;
	    }

	    //This will seg fault if your list is bad!
	    tmp2 = swords;
	    while(tmp2 != NULL)
	    {
	    	tmp2 = tmp2->nextSword;
	    }

        printf("Welcome to the shop!\n\n1: Shields\n2: Swords\n3: View heroes\n4: Quit\n");
        
        printf("\nSelect an option: ");
        int choice;
        scanf("%d", &choice);
        
        while(choice < 1 || choice > 4)
        {
            printf("I did not understand that command. Try again: ");
            scanf("%d", &choice);
        }
        
        switch(choice)
        {
            case 1:
                shieldSelection(&shields, heroes, &numShields);
                break;
            case 2:
                swordSelection(&swords, heroes, &numSwords);
                break;
            case 3:
                printHeroes(heroes, ALL);
                break;
            case 4:
                freeShields(shields);
                freeSwords(swords);
                return;
            default:
            	printf("I wasn't supposed to get here! Fatal error.\n");
            	freeShields(shields);
                freeSwords(swords);
                return;
        }
        
    }
}

//DO NOT TOUCH THIS FUNCTION
Hero* getHeroes(void)
{
    FILE* fp = fopen("chosenHeroes.bin", "rb");
    if(!fp)
    {
    	printf("Heroes file did not open!\n");
    	return NULL;
    }

    Hero* heroes = malloc(sizeof(Hero)*3);
    if(!heroes)
    {
    	printf("Heroes failed to malloc! That's really bad!\n");
    	printf("Try closing some programs to free up memory\n");
    	return NULL;
    }

    int i = 3;
    int j = 0;
    int timeout = 10;
    while((j = fread(heroes, sizeof(Hero), i, fp)) != i)
    {
    	if(timeout == 0)
    	{
    		printf("I couldn't read data from the file. Try a different computer?\n");
    		return NULL;
    	}
    	i = i-j;
    	timeout--;
    }

    for(i = 0; i < 3; i++)
    {
    	heroes[i].shield = NULL;
    	heroes[i].sword = NULL;
    }

    if(fclose(fp) != 0)
    {
    	printf("Couldn't close the hero file...this is awkward.\nWill try to continue with the program.\n");
    }
    return heroes;
}

//DO NOT TOUCH THIS FUNCTION
void printHeroes(Hero* heroes, print_option option)
{
    int i;
    switch(option)
    {
        case ALL:
            for(i = 0; i < 3; i++)
            {
                printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                    i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                    heroes[i].defense, heroes[i].speed, heroes[i].luck);
                printf("Items for %s\n", heroes[i].name);
                if(heroes[i].shield != NULL)
                {
                    printf("\tShield: %s\n\t\tPrice: $%d\tDefense: %d\tWeight: %dkg\n",
                        heroes[i].shield->name, heroes[i].shield->price, 
                        heroes[i].shield->defense, heroes[i].shield->weight);
                }
                else
                {
                    printf("\tShield: None\n");
                }
                if(heroes[i].sword != NULL)
                {
                    printf("\tSword:\n\t%s\n\t\tPrice: $%d\tDamage: %d\n",
                        heroes[i].sword->name, heroes[i].sword->price, 
                        heroes[i].sword->damage);
                }
                else
                {
                    printf("\tSword: None\n");
                }
            }
            break;
        case SWORDS:
            for(i = 0; i < 3; i++)
            {
                if(heroes[i].sword == NULL)
                {
                    printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                        i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                        heroes[i].defense, heroes[i].speed, heroes[i].luck);
                    printf("Items for %s\n", heroes[i].name);
                    if(heroes[i].shield != NULL)
                    {
                        printf("\tShield: %s\n\t\tPrice: $%d\tDefense: %d\tWeight: %dkg\n",
                            heroes[i].shield->name, heroes[i].shield->price, 
                            heroes[i].shield->defense, heroes[i].shield->weight);
                    }
                    else
                    {
                        printf("\tShield: None\n");
                    }   
                    printf("\tSword:None\n");
                }
                else
                {
                	printf("\n%s has a sword already.\n", heroes[i].name);
                }
            }
            break;
        case SHIELDS:
            for(i = 0; i < 3; i++)
            {
                if(heroes[i].shield == NULL)
                {
                    printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                        i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                        heroes[i].defense, heroes[i].speed, heroes[i].luck);
                    printf("Items for %s\n\tShield: None\n", heroes[i].name);   
                    if(heroes[i].sword != NULL)
                    {
                        printf("\tSword: %s\n\t\tPrice: $%d\tDamage: %d\n",
                            heroes[i].sword->name, heroes[i].sword->price, 
                            heroes[i].sword->damage);
                    }
                    else
                    {
                        printf("\tSword: None\n");
                    }
                }
                else
                {
                	printf("\n%s has a shield already.\n", heroes[i].name);
                }
            }
            break;
    }
}

void freeHeroes(Hero* heroes)
{
    int i = 0;
    for(i; i < 3; i++)
    {
        if(heroes[i].shield != NULL)
        {
            free(heroes[i].shield);
        }
        if(heroes[i].sword != NULL)
        {
            free(heroes[i].sword);
        }        
    }
    free(heroes);
}

void shieldSelection(Shield** shields, Hero* heroes, int* numShields)
{
    int choice = -1, choice2 = -1;
    int i =0;

    while(1)
    {
        printShields(*shields);
        printf("Select a shield you would like to purchase:"); 
        scanf("%d", &choice);

        while (choice < 0 || choice >= *numShields)//Error Check
        {
            printf("Invalid Input, Try Again:");
            scanf("%d", &choice);
        }
        
        if(choice == (*numShields)-1)
        {    
            return;
        }

        
        printHeroes(heroes, SHIELDS);//Print All hero info
        printf("Select a hero to equip the shield to:");
        scanf("%d", &choice2);
        
        while(choice2 < 0 || choice2 > 2)//Error Check
        {
            printf("Invalid Input, Try Again:");
            scanf("%d", &choice2);
        }
        
        heroes[choice2].shield = extractShieldFromList(shields, choice);//Extracts chosen shield and Assign chosen shield to hero
       
        (*numShields)--;//Decrease number of shields
    }
        
    
    
}
void swordSelection(Sword** swords, Hero* heroes, int* numSwords)
{
    int choice = -1, choice2 = -1;
    int i =0;

    while(1)
    {
        printSwords(*swords);
        printf("Select a sword you would like to purchase:"); 
        scanf("%d", &choice);

        while (choice < 0 || choice >= *numSwords)//Error Check
        {
            printf("Invalid Input, Try Again:");
            scanf("%d", &choice);
        }
        
        if(choice == (*numSwords)-1)
        {    
            return;
        }

        
        printHeroes(heroes, SWORDS);//Print All hero info
        printf("Select a hero to equip the sword to:");
        scanf("%d", &choice2);
        
        while(choice2 < 0 || choice2 > 2)//Error Check
        {
            printf("Invalid Input, Try Again:");
            scanf("%d", &choice2);
        }

        heroes[choice2].sword = extractSwordFromList(swords, choice);//Assign chosen sword to hero

        (*numSwords)--;//Decrease number of swords
    }
    return;
}

void printShields(Shield* shields)
{
    int i=0;

    while(shields->nextShield != NULL)
    {
        printf("%d: %s \n"
                    "\tPrice: %d \tDefense: %d \t Weight: %d \n\n",
                i, shields->name, shields->price, shields->defense, shields->weight);
        
            i++;
            shields = shields->nextShield;
    }
    
    printf("%d: Quit\n\n", i);
    return;
}

void printSwords(Sword* swords)
{
    int i=0;
    if(swords == NULL)
    {
        printf("There are no swords left to purchase\n");
        return;
    }
    while(swords->nextSword != NULL)
    {
        printf("%d: %s \n"
                    "\tPrice: %d \tDamage: %d \n\n",
                i, swords->name, swords->price, swords->damage);
        
            i++;
            swords = swords->nextSword;
    }
    printf("%d: Quit\n\n", i);
    return;
}

Shield* readShields(FILE* fp, int* numShieldsPtr)
{
    Shield* start = malloc(sizeof(Shield));
    Shield* newShield = start;
    
    if(start == NULL)//If it doesn't malloc correctly
    {
        return NULL;
    }
    
    else
    {
        while(1)
        {
            (*numShieldsPtr)++;//Increase the value of numShields by one    
            
            fread(newShield, sizeof(Shield), 1, fp);//Read in the shields from the file
            
            if(feof(fp))//Exit once the file is done
            {
               newShield->nextShield = NULL;//End the list
                return start;
            }
            
            newShield->nextShield = malloc(sizeof(Shield));
            
            if(newShield->nextShield == NULL)//If it can't malloc space for the next shield
            {
                return NULL;//This will trip up error messages in Shop
            }
            
            newShield = newShield->nextShield;//Make the next shield the new NewShield
        }//end while
    }//end else
}

Sword* readSwords(FILE* fp, int* numSwordsPtr)
{
    Sword* start = malloc(sizeof(Sword));
    Sword* newSword = start;
    
    if(start == NULL)//If it doesn't malloc correctly
    {
        return NULL;
    }
    
    else
    {
        while(1)
        {
            (*numSwordsPtr)++;//Increase the value of numShields by one    
            
            fread(newSword, sizeof(Sword), 1, fp);//Read in the swords from the file
            
            if(feof(fp))//Exit once the file is done
            {
                newSword->nextSword = NULL;//End the list
                return start;
            }
            
            newSword->nextSword = malloc(sizeof(Sword));
            
            if(newSword->nextSword == NULL)//If it can't malloc space for the next sword
            {
                return NULL;//This will trip up error messages in Shop
            }
            
            newSword = newSword->nextSword;//Make the next sword the new newsword
        }
    }
}

Shield* extractShieldFromList(Shield** shields, int chosenShield)
{
        
    Shield* previous;//Utility Pointers
    Shield* current;
    Shield* temp;
    int i = 0;
    
    if(chosenShield == 0)//Beginning of list
        {    
            temp = *shields;//Save start pointer
            *shields = (*shields)->nextShield;//Make second element new start
            return temp;
        }
    
    else//Middle of list/end of list
        {
            previous = *shields;//Save start as previous
            current = (*shields)->nextShield;//Make next shield the current one
            
            for(i = 0; i < chosenShield-1; i++)//Cycle through list to find correct item
            { 
                previous = current;//Keep track of where it's at in the list
                current = current->nextShield;
            }           
           
            if(current != NULL)
            {
                temp = current;//Save current pointer

                previous->nextShield = current->nextShield;//move pointer for next shield into the previous pointer
                return temp;
            }
            else
            {
                return NULL;
            }
        }
}

Sword* extractSwordFromList(Sword** swords, int chosenSword)
{
       
    Sword* previous;//Utility Pointers
    Sword* current;
    Sword* temp;
    int i = 0;
    
    if(chosenSword == 0)//Beginning of list
        {    
            temp = *swords;//Save start pointer
            *swords = (*swords)->nextSword;//Make second element new start
            return temp;
        }
    
    else//Middle of list/end of list
        {
            previous = *swords;//Save start as previous
            current = (*swords)->nextSword;//Make next shield the current one
            
            for(i = 0; i < chosenSword-1; i++)//Cycle through list to find correct item
            { 
                previous = current;//Keep track of where it's at in the list
                current = current->nextSword;
            }
            

            if(current != NULL)
            {
                temp = current;//Save current pointer
                previous->nextSword = current->nextSword;//move pointer for next shield into the previous pointer
                return temp;
            }
            else
            {
                return NULL;
            }
        }

}

void freeShields(Shield* shields)
{
    Shield* temp;
    
    while(shields != NULL)//Go through the list freeing each one
    {
        temp = shields;//Hold address for beginning of list
        shields = shields->nextShield;
        free(temp);
    }
    free(shields);
    return;
}

void freeSwords(Sword* swords)
{
    Sword* temp;
    
    while(swords != NULL)//Go through the list freeing each one
    {
        temp = swords;//Hold address for beginning of list
        swords = swords->nextSword;
        free(temp);
    }
    free(swords);
    return;
}