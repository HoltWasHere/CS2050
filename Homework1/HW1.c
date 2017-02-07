/* 
 * File:   Homework 1
 * Author: Holt Skinner
 *         HASTG2
 *
 * Created on September 3, 2015, 2:10 PM
 */

#include <stdio.h>
#include <stdlib.h>

//Structure Definitions
typedef struct category
{
    char name[20];
    int numInCategory;
} Category;

typedef struct shield
{
    char name[50];
    int price;
    int defense;
    int weight;
} Shield;

typedef struct sword
{
    char name[50];
    int price;
    int damage;
    int weight;
} Sword;

typedef struct footwear
{
    char name[50];
    int price;
    int defense;
    int weight;
} Footwear;

typedef struct headgear
{
    char name[50];
    int price;
    int defense;
    int weight;
} Headgear;

typedef struct hero
{
    char name[30];
    int health;
    int defense;
    int speed;
    int attack;
    int luck;
} Hero;

//Function Prototypes
void mainMenu(); //Displays Menu and starts the game
void highScores();//Prints out high scores and goes back to main menu
void newGame();//Asks for name and calls functions to do the game, then goes back to main menu
void processHeroes();
void weaponSelection();
void shieldSelection(Shield* shields, int numShields);
void swordSelection(Sword* swords, int numSwords);
void footwearSelection(Footwear* footwear, int numFootwear);
void headgearSelection(Headgear* headgear, int numHeadgear);

int main(int argc, char** argv) {
    
    if (argc != 5)//Checking to make sure the input files read in right
    {
        printf("Invalid Arguments");
        return 1;
    }
    mainMenu();
    
    return (EXIT_SUCCESS);
}

void mainMenu(void)//Displays Menu and starts the game
{
    int menuChoice;
    while(menuChoice != 3)//Checking to see if they quit
    {    

        printf("\nWelcome! Please select an option:\n\n1. New Game\n2. High Scores\n3. Exit Game\n\n");
        scanf("%d", &menuChoice);
    
        switch (menuChoice) //Each possibility for each option
        {
                case 1: newGame();//If they select 1, Begin a new game
                        break;//Leave switch after doing new game           
                case 2: highScores();//If they select 2, show high scores 
                        break;//Leave switch
                case 3: break;       
                default: printf("Invalid Input. Try Again.\n\n");
                        break;
            
        }//End switch 
    }//End While    
   
    return;
}

void highScores()//Prints out high scores and goes back to main menu
{
    FILE* fp = fopen("highScores.txt", "r");
        
    if (fp == NULL)
    {
        printf("\nCannot open file highScores.txt\n\n");
        return;
    } 
    char hsPeople[256];//Character array to store high score people
    int hsNums[10];//integer array to store high score numbers
    int i;//Counter
    printf("Username:\tScore:\n\a");
    for (i=0; i<10; i++)
    {
        fscanf(fp, "%s %d", hsPeople, &hsNums[i]);//Read in name and high score from a file
        printf("%s\t\t%d\n", hsPeople, hsNums[i]);//Print out name and high score
    }//End for
    fclose(fp);
    return;
}
void newGame()//Asks for name and calls functions to do the game, then goes back to main menu
{
    FILE* fp = fopen("save.txt", "w");//Open/create Save file
    
    if(fp==NULL)//Error check for file problems
    {
        printf("Could not create save.txt");
    }
    char name[20];//Array to hold name
    printf("What is your name?\n");
    scanf("%s", name);
    fprintf(fp, "%s", name);
    fclose(fp);
    printf("Hello %s. Welcome to the gauntlet.\n\n", name);
    
    processHeroes();//Call processHeroes
    weaponSelection();//Call weapon selection
    
    return;
}
void processHeroes()
{
    FILE* fp = fopen("HeroesFile.txt", "rb");//Open Heroes file
    
    if(fp == NULL)//Error check for file problems
    {
        printf("Could not open HeroesFile.txt");
    }
    
    Hero blankhero[6];//Array of heroes
    int i=0;//Counter
    int heroSelect1, heroSelect2, heroSelect3;
    printf("Hero Data:\n\n");
    while(1)//Read in hero data, store it and print it out
    {
        fread(&blankhero[i], sizeof(Hero), 1, fp);
        if(feof(fp))
        {
            break;
        }
        printf("%s\n\tHealth: %d\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck:%d\n\n", blankhero[i].name, blankhero[i].health, blankhero[i].defense, blankhero[i].speed, blankhero[i].attack, blankhero[i].luck);
        i++;
    }//end while
    fclose(fp);//CLose the heroes file
    printf("Choose the first hero you wish to add to your team (1-5):");
    scanf("%d", &heroSelect1);
    while (heroSelect1 < 1 || heroSelect1 > 5)//Error check for heroselect
    {
        printf("\nIncorrect choice. Choose again:");
        scanf("%d", &heroSelect1);
    }//End while End hero 1 stuff
   
    //Begin hero 2
    printf("\nChoose the second hero you wish to add to your team (1-5):");
    scanf("%d", &heroSelect2);
    while (heroSelect2 < 1 || heroSelect2 > 5 || heroSelect2 == heroSelect1)//Error check for heroselect
    {
        printf("\nIncorrect choice. Choose again:");
        scanf("%d", &heroSelect2);
    }//End while End hero 2 stuff
    
    //Begin hero 3
    printf("\nChoose the third hero you wish to add to your team (1-5):");
    scanf("%d", &heroSelect3);
    while (heroSelect3 < 1 || heroSelect3 > 5 || heroSelect3 == heroSelect1 || heroSelect3 == heroSelect2)//Error check for heroselect
    {
        printf("\nIncorrect choice. Choose again:");
        scanf("%d", &heroSelect3);
    }//End while End hero 3 stuff
    
    FILE* fp2 = fopen("heroesSave.txt", "wb");//Create heroesSave file in binary to save the chosen heroes
    fwrite(&blankhero[heroSelect1+1], sizeof(Hero), 1, fp2);//Write hero 1 to the file
    fwrite(&blankhero[heroSelect2+1], sizeof(Hero), 1, fp2);//Hero 2
    fwrite(&blankhero[heroSelect3+1], sizeof(Hero), 1, fp2);//Hero 2
    fclose(fp2);//Close the file
    printf("\nHero choices saved successfully.\n");
    return;
}

void weaponSelection()
{
    FILE* fp = fopen("CategoryList.txt", "rb");//Open category file
    
    
      if(fp == NULL)//Error check for file problems
    {
        printf("Could not open CategoryList.txt\n");
    }
    
    Category type[4];//Array of categories
    int selection;
    int i=0;
    fseek(fp, 0, SEEK_SET);
/*
    while(i<4)//Read in category data
    {
*/
        fread(type, sizeof(Category), 4, fp);
/*
        if(feof(fp))
            {
                break;
            }
        i++;
    }//End While
*/
    fclose(fp);
    
        //Generating arrays to hold weapon data
        FILE* fp2 = fopen("ItemsFile.txt", "rb");//Create file pointer for items
        
        Shield shields[type[0].numInCategory];
        Sword swords[type[1].numInCategory];
        Footwear footwear[type[2].numInCategory];
        Headgear headgear[type[3].numInCategory];
        
        fread(shields, sizeof(Shield), type[0].numInCategory, fp2);//Read off shields and store
        fread(swords, sizeof(Sword),type[1].numInCategory, fp2);
        fread(footwear, sizeof(Footwear),type[2].numInCategory, fp2);
        fread(headgear, sizeof(Headgear),type[3].numInCategory, fp2);
        fclose(fp2);
        
    while (selection != 4)//Largest while, loop through menu
    {

        int j=0;//Counter          
        printf("\nSelect a category to see its items.\n");
            
        while(j<4)
        {
            printf("%d: %s\n", j, type[j].name);
            j++;
        }//End j<4 while
        
        
        printf("4: Quit\n\nOption:");
        scanf("%d", &selection);
        if(selection <4 && selection>=0)
        {
            printf("\nItem Data:\n\n");
        }
        switch(selection)//Different options for different selections
        {
            case 0: shieldSelection(shields, type[0].numInCategory);
                    break;
            case 1: swordSelection(swords, type[1].numInCategory);
                    break;
            case 2: footwearSelection(footwear, type[2].numInCategory);
                    break;
            case 3: headgearSelection(headgear, type[3].numInCategory);
                    break;
            case 4: break;
            
            default:printf("Invalid Choice. Try Again:"); //Error check
                    scanf("%d", &selection);
                    break;
        }//End switch        
    }//End selection!=4 while

}


void shieldSelection(Shield* shields, int numShields)
{
    int i;//Counter
    for(i=0; i<numShields; i++)//Cycle through array of weapons and print them out
    {
        printf("%s\n\tPrice: $%d\n\tMultiplier: %d\n\tWeight: %d\n\n", shields[i].name, shields[i].price, shields[i].defense, shields[i].weight);
    }
    return;
}
void swordSelection(Sword* swords, int numSwords)
{
    int i;//Counter
    for(i=0; i<numSwords; i++)
    {
        printf("%s\n\tPrice: $%d\n\tMultiplier: %d\n\tWeight: %d\n\n", swords[i].name, swords[i].price, swords[i].damage, swords[i].weight);
    }
    return;
}
void footwearSelection(Footwear* footwear, int numFootwear)
{
    int i;//Counter
    for(i=0; i<numFootwear; i++)
    {
        printf("%s\n\tPrice: $%d\n\tMultiplier: %d\n\tWeight: %d\n\n", footwear[i].name, footwear[i].price, footwear[i].defense, footwear[i].weight);
    }
    return;    
}
void headgearSelection(Headgear* headgear, int numHeadgear)
{
    int i;//Counter
    for(i=0; i<numHeadgear; i++)
    {
        printf("%s\n\tPrice: $%d\n\tMultiplier: %d\n\tWeight: %d\n\n", headgear[i].name, headgear[i].price, headgear[i].defense, headgear[i].weight);
    }
    return;    
}
