/* 
 * File:   main.c
 * Author: hastg2
 *          Holt Skinner
 *          Lab 11
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void parseFile(char* filename);
void parseWord(char* word);
bool isAPhoneNumber(char* word);
bool isADate(char* word);
bool isATime(char* word);

int main(int argc, char** argv)
{
	parseFile(argv[1]);	
	return 0;
}

//not actually needed for the test input file, but a nice general parser
//with a few delimiters for general use. Can be used on other text files,
//such as memos, etc
void parseFile(char* filename)
{
	FILE* fp = fopen(filename, "r");
	char* word = malloc(sizeof(char)*255);
	char c;
	int i = 0;
	bool periodInWord = false;
	bool wasWordDone = false;
	//puts actual words together, instead of using strtok.
	//This way you can use strtok if you so choose in the 
	//check functions below.
	while((c = fgetc(fp)) != EOF)
	{
		//thought this would cause a corner case, will keep here anyway.
		if(c == '\n')
		{
			wasWordDone = true;
		}
		//these separate words from each other.
		else if(c == ' ' || c == ',' || c == '.')
		{
			wasWordDone = true;
		}
		//this is either a letter or character that is part of a word.
		else
		{
			//still on the same word.
			if(wasWordDone == false)
			{
				word[i] = c;
				i++;
			}
			//new word has been started. Process old word, then
			//start over.
			else
			{
				word[i] = '\0';
				i = 0;
				parseWord(word);
				free(word);
				word = malloc(sizeof(char)*255);
				word[i] = c;
				wasWordDone = false;
				i++;
			}
		}	
	}
	//leaves out the last word because the loop stops at EOF,
	//so process last word.
	parseWord(word);	
	fclose(fp);
	free(word);
}

void parseWord(char* word)
{
    if (word[strlen(word) - 1] == '\r')
    {
        word[strlen(word) - 1] = '\0';
    }
        if(isAPhoneNumber(word))
	{
		printf("Phone Number found: %s\n", word);
	}
	if(isADate(word))
	{
		printf("Date found: %s\n", word);
	}
	if(isATime(word))
	{
		printf("Time found: %s\n", word);
	}
}

//These are for you to do!
//I also changed it up last minute. You can use strtok() if you want, but
//you won't get the bonus!
bool isAPhoneNumber(char* word)
{
    int i = 0;
    
    for(i = 0; word[i] != '\0'; i++)
    {

        if(i == 3 || i == 7)//If there's supposed to be a dash
        {
            if(word[i] != '-')
            {
                return false;
            }
        }
        
        else if(!isdigit(word[i]))//if its not a digit
        {
            return false;
        }
    }
    if(i != 12)//If the length is wrong
    {
            return false;
    }
    return true;//You survived!
}

bool isADate(char* word)
{


    int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //We'll say that the earliest readable date is 01/01/1970 (computer epoch).
    //Computers shouldn't be reading stuff from earlier than computers anyway.
    int earliestValidYear = 1970;
    int earliestValidDay = 1;
    int earliestValidMonth = 1;
    int day, month, year;
    
    int i = 0, j=0;
    
    for(j=0; j<2; j++)
    {
        if(!isdigit(word[i]))//Invalid character for first char 
        {
            return false;
        }
    
        i++;
    
        if(word[i] != '/' && !isdigit(word[i]))
        {
            return false;
        }
    
        if(isdigit(word[i]))
        {    
            i++;
            if(word[i] != '/')
            {
            return false;
            }
        }
        i++;
    }//End for
    for(j = 0; j<4; j++)//Check for four digits
    {
        if(!isdigit(word[i]))
        {
            return false;
        }
        i++;
    }
    if (word[i] != '\0')
    {
        return false;
    }
    
    sscanf(word, "%d/%d/%d", &month, &day, &year);

    if(month < earliestValidMonth || month >12)//Valid month
    {
        return false;
    }
    else if(day < earliestValidDay || day > daysPerMonth [month-1])//valid day
    {
        return false;
    }
    else if(year < earliestValidYear)
    {
        return false;
    }
    else
    {
        return true;//You survived!
    }


}

bool isATime(char* word)
{

    int i = 0;
    
    if(!isdigit(word[i]))//first char must be digit
    {
        return false;
    }
    i++;
    if(word[i] != ':' && !isdigit(word[i]))//If it's not a colon or digit
        {
            return false;
        }
    
    if(isdigit(word[i]))//splinter group
        {    
            i++;
            if(word[i] != ':')
            {
                return false;
            }
        }
   i++;
   if(!isdigit(word[i]) || !isdigit(word[++i])) //check next two digits
   {
       return false;
   }
        
   i++;
  
   if(word[i] != 'a' && word[i] != 'p')//check for correct character
   {
       return false;
   }
   
   i++;

   
   if(word[i] != 'm')
   {
       return false;
   }
   
   i++;

   if (word[i] != '\0')//If the string isnt over
   {
       return false;
   }

   int hour, minute; 
   char char1, char2;
   sscanf(word, "%d:%d%c%c", &hour, &minute, &char1, &char2);
   
   if(hour < 1 || hour >12)//invalid hours
   {
       return false;
   }
   if(minute < 0 || minute > 59)//invalid minutes
   {
       return false;
   }
   
   return true;//You survived!
}