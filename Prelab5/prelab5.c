/* 
 * File:   main.c
 * Author: Holt Skinner
 *          hastg2
 */

/*
 * Look for the ******************* to see where stuff needs to be added.
 * 
 You are to do 2 things: 
 * 1. Add the timing functions to main. Everything is included, so you just need to add appropriate
 *    variables and function calls to do this. You are to create the variables that will hold the 
 *    timestamps, and then store the difference between the timestamps into the variable time, which
 *    has been made for you. That is all you need to do for this (it will print out automatically if you do
 *    it right). 
 * 
 * 2. You are to add code for the sorting functions:
 *      merge by artist
 *      insertion by ID
 *      selection by number sold
 *    
 *    For the merge sort, the merge part is done for you. Simply fill in the recursive part of the merge
 *    sort (this should be quite simple)
 *    For the insertion and selection sort, put in the code necessary to sort the malloced array by the 
 *    appropriate characteristic. See below if you are still confused on where you are putting code. 
 * 
 * 
 * That's it! Make sure to put the appropriate header at the top so we know who you are. Be sure to COMMENT
 * so we know your thought process and so you can explain to yourself what you're doing. 
 * 
 * 
 * A note on the timing: You might get stupidly small numbers, and thus the total time
 * will be so small that it will be unmeasurable. THIS IS OKAY! That means you have a good
 * enough computer such that for 10 elements, the algorithms don't differ enough in time enough
 * for you to care which you use. There are no units on the printed timestamps, because you can change
 * the units very easily, so look at your calculation to see units. The total time should be in 
 * microseconds, but again, subject to change.  
 * 
 * If you really want to see meaningful results, use the clock() function with vars of type
 * clock_t. This will put everything in terms of clock ticks instead of sec/usec (if you want to know 
   how long a clock tick is, look at your processing speed. My computer has 3.11 GHz processing speed, which means 
 * 3.11 billion clock ticks = 1 second, roughly).
 * 
 * You can modify other stuff, but other than the above things, everything else can be left alone. 
 * Basically, MODIFY PREEXISTING CODE AT YOUR OWN RISK!
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef struct MA
{
    char name[30];
    char artist[30];
    int numberSold;
    int ID;
} music_album;

music_album* readFromFile(char* filename);
void printAlbums(music_album* list, long long time, long long t1, long long t2);
void mergeSortByArtist(music_album* list, int start, int end);
void merge(music_album* list, int start, int middle, int end);
void selectionSortOnNumberSold(music_album* list);
void insertionSortOnID(music_album* list);

int main(int argc, char** argv) {

    //User's choice on sort
    int choice;
    //Here are the time variables. They will hold the following:
    //  time: the final time that the algorithm took.
    //  t1: the first timestamp recorded, before the algorithm runs
    //  t2: the second timestamp recorded, after the algorithm runs
    long long time = -1;
    long long t1, t2;
    
    music_album* list = readFromFile("input.txt");
    if(!list)
    {
        printf("No array! Did something happen to the file?\n");
        return;
    }
    printAlbums(list, time, t1, t2);
    
    //Prints a menu. Each menu selection will do a different sort, and then print out the newly sorted array. 
    //Repeats until user put in 4, then the program will end. 
    while(1)
    {
        printf("Choose a selection:\n1: Selection sort on numberSold\n2: Insertion sort on ID\n3: Merge sort on artist\n");
        printf("4: Exit\n");
        printf("\n>");
        scanf("%d", &choice);
        //Appropriate error checking
        while(choice > 4 || choice < 1)
        {
            printf("Invalid selection.\n");
            printf("\n>");
            scanf("%d", &choice);
        }
        
        //****************First thing to do************************
        //start the timing. Get the first timestamp here.
        struct timeval tv;
        gettimeofday(&tv, NULL);
	t1 = tv.tv_sec+(tv.tv_usec/1000000.0);

        
        switch (choice)
        {
            //****************Second thing to do************************
            case 1: 
                selectionSortOnNumberSold(list);
                gettimeofday(&tv, NULL);
                t2 = (tv.tv_sec*1000000)+tv.tv_usec;  
                printAlbums(list, t2-t1, t1, t2);
                break;
            case 2:
                insertionSortOnID(list);
                gettimeofday(&tv, NULL);
                t2 = (tv.tv_sec*1000000)+tv.tv_usec;  
                printAlbums(list, t2-t1, t1, t2);
                break;
            case 3:
                mergeSortByArtist(list, 0, 9);
                gettimeofday(&tv, NULL);
                t2 = (tv.tv_sec*1000000)+tv.tv_usec; 
                printAlbums(list, t2-t1, t1, t2);
                break;
            case 4:
                //not needed here
                free(list);
                return 0;
        }
        
        
    }
    
}

music_album* readFromFile(char* filename)
{
    FILE* fp = fopen(filename, "rb");
    
    if(!fp)
    {
        return NULL;
    }
    
    music_album* list = malloc(sizeof(music_album)*10);
    fread(list, sizeof(music_album), 10, fp);
    fclose(fp);
    return list;
}

void printAlbums(music_album* list, long long time, long long t1, long long t2)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("------\nArtist: %s\nAlbum: %s\nNumber Sold: %d copies\nID: %d\n------\n", 
                list[i].artist, list[i].name, list[i].numberSold, list[i].ID);
    }
    if(time == -1)
    {
        printf("\nTime has not been recorded yet.\n\n");
    }
    else if(time == 0)
    {
        printf("\nTotal time: Less than 1 microsecond\n");
        printf("\nt1: %e\n", t1);
        printf("\nt2: %e\n\n", t2);
    }
    else 
    {
        printf("\nTotal time: %e\n", time);
        printf("\nt1: %e\n", t1);
        printf("\nt2: %e\n\n", t2);
    }
    
}


/*
 * Inputs:
 *      list: the pointer to the malloced array
 *      low: the lowest index of the scoped array
 *      high: the highest index of the scoped array
 * 
 * Returns: nothing
 */
void mergeSortByArtist(music_album* list, int low, int high)
{
//****************Third thing to do************************  
    
    /*
     * Fill in this function. Remember your base case.
     * 
     * Remember, the sort goes down the left side, then the right side, 
     * then merges the two sides. The breaking down parts are recursive calls,
     * and then you just do merge. 
     * 
     * Make sure you figure out how the left and right sides are represented
     * using low and high! 
     
     */
        if (low < high)
    {
        int m = low+(high-low)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSortByArtist(list, low, m);
        mergeSortByArtist(list, m+1, high);
        merge(list, low, m, high);
    }
    
}


/*
 * Inputs:
 *      list: the pointer to the malloced array
 *      low: the lowest index of the scoped array
 *      mid: the middle index of the scoped array
 *      high: the highest index of the scoped array
 * 
 * Returns: nothing
 * 
 * DON'T TOUCH
 */
void merge(music_album* list, int low, int mid, int high)
{
    music_album *temp;
	int left, right, current;
	
	temp = malloc((high + 1)*sizeof(music_album));
	
	left = low;
	right = mid + 1;
	current = low;
	
	while((left <= mid) && (right <= high))
	{
		if (strcmp(list[left].artist, list[right].artist) > 0)
		{
			temp[current] = list[right];
			current++;
			right++;
		}
		else
		{
			temp[current] = list[left];
			current++;
			left++;
		}
	}
	
	while(left <= mid)
	{
		temp[current] = list[left];
		current++;
		left++;
	}
	
	while(right <= high)
	{
		temp[current] = list[right];
		current++;
		right++;
	}
	
	for(left = low; left < current; left++)
	{
		list[left] = temp[left];
	}
	
	free(temp);
}

/*
 * Inputs:
 *      list: the pointer to the malloced array
 * 
 * Returns: nothing
 */
void selectionSortOnNumberSold(music_album* list)
{
//****************Fourth thing to do************************      
    

/*
 * Take the malloced array, and do selection sort using the given
 * criteria. There's nothing else you have to do.
 */
    int lh, rh, i;//Counters
    music_album temp;
    
    for(lh=0; lh < 10; lh++)
    {
        rh = lh;
        for(i = lh; i < 10; i++)
        {
            if(list[i].numberSold < list[rh].numberSold)
            {
                rh = i;
            }
        }
        temp = list[lh];
        list[lh] = list[rh];
        list[rh] = temp;
    }   
    return;
}

/*
 * Inputs:
 *      list: the pointer to the malloced array
 * 
 * Returns: nothing
 */
void insertionSortOnID(music_album* list)
{
//****************Last thing to do************************        
 
 /*
 * Take the malloced array, and do insertion sort using the given
 * criteria. There's nothing else you have to do.
 */
    int i, j;//Counters
    music_album temp;
    
    for(i=1; i<10; i++)
    {
        temp = list[i];//Save current element
        j = i-1;
        
        while((temp.ID < list[j].ID) && (j>=0))
        {
            list[j+1] = list[j];
            j=j-1;
        }
        list[j+1]=temp;
    }  
    return;
}