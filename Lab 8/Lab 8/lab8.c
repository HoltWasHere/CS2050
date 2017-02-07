/* File:   lab8.c
 * Author: hastg2
 *          Holt Skinner
 * Created on October 28, 2015, 3:04 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct word_
{
    char word[10];
    struct word_* nextWord;
    struct word_* prevWord;
}Word;


Word* addWordToSentence(Word* firstWord, Word* newWord);
Word* deleteWordFromSentence(Word** firstWord);
Word* addWordToUndoList(Word* lastUndone, Word* newestUndoneWord);
Word* deleteWordFromUndoList(Word** lastUndone);
void printSentence(Word* firstWord);
void freeMemory(Word* firstWord, Word* undoList);

int main(int argc, char** argv) {

    int choice;
    Word* justReadIn = NULL;
    Word* undoStack = NULL;
    Word* undoneWord = NULL;
    Word* redoneWord = NULL;
    Word* sentenceQ = NULL;//I made it a stack instead
    
    while(1)
    {
        printf("1: Add Word\n"
                "2: Undo\n"
                "3: Redo\n"
                "4: Quit\n");
        printf("Option:\n>");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1: 
                justReadIn = malloc(sizeof(Word));
                printf("Insert your word: ");
                scanf("%s", justReadIn->word);
                sentenceQ = addWordToSentence(sentenceQ, justReadIn);
                break;
            case 2:
                undoneWord = deleteWordFromSentence(&sentenceQ);
                undoStack = addWordToUndoList(undoStack, undoneWord);
                break;
            case 3:
                redoneWord = deleteWordFromUndoList(&undoStack);
                sentenceQ = addWordToSentence(sentenceQ, redoneWord);
                break;
            case 4:
                freeMemory(sentenceQ, undoStack);
                return 0;
                break;
            default:
                printf("Did not understand command. Try again.\n");
                break;
        }
        printf("\n");
        printSentence(sentenceQ);
        printf("\n");
    }
    
    return (EXIT_SUCCESS);
}

Word* addWordToSentence(Word* firstWord, Word* newWord)//Return Head of list
{
    if(newWord == NULL)//New List
    {
        printf("Nothing to add.\n");
        return firstWord;
                
    }

    newWord->prevWord = firstWord;
    newWord->nextWord =  NULL;
    
    if(firstWord != NULL)//if its not a new list
    {
        firstWord->nextWord = newWord;
    }
    return newWord;
       
}

Word* deleteWordFromSentence(Word** firstWord)
{
    if(*firstWord == NULL)//If the sentence is empty
    {
        printf("\nNo sentence here.\n");
        return NULL;
    }
    
    Word* temp = *firstWord;//Save end of sentence
    
    (*firstWord) = (*firstWord)->prevWord;//Move pointers around
    
    if(*firstWord != NULL)
    {
        (*firstWord)->nextWord = NULL;
    }
    return temp;
}

Word* addWordToUndoList(Word* lastUndone, Word* newestUndoneWord)
{
    if(newestUndoneWord == NULL)//if the sentence is empty
    {
        printf("Nothing to Undo.\n");
        return NULL;
    }
    if(lastUndone == NULL)//Create new undone stack
    {
        lastUndone = newestUndoneWord;//Set newest undone word as stack top
        lastUndone->prevWord = NULL;//Make the node not point to anything
        lastUndone->nextWord = NULL;
        return lastUndone;//return new top
    }
    else
    {
        newestUndoneWord->prevWord = lastUndone;//Set previous top of stack as previous word
        newestUndoneWord->nextWord = NULL;//Signify end of list
        lastUndone->nextWord = newestUndoneWord;//Connect old top to new top
        return newestUndoneWord;//make it the new top
    }
    
}

Word* deleteWordFromUndoList(Word** lastUndone)
{
    if((*lastUndone) == NULL)
    {
        printf("Nothing to Redo.\n");
        return NULL;
    }
    Word* temp = *lastUndone;//Save top of stack
    (*lastUndone) = (*lastUndone)->prevWord;//Move pointers around
    return temp;
}

void printSentence(Word* firstWord)
{
    if(firstWord == NULL)
    {
        printf("\nNothing to Print.\n");
        return;
    }
    
    Word* temp = firstWord;// Temp to cycle through
    
    while(temp->prevWord != NULL)//go to bottom of stack (rewind)
    {
        temp = temp->prevWord;
    }
    printf("\n");
    
    while(temp != NULL)//Cycle through the list in printed order
    {
        printf("%s ", temp->word);
        temp = temp->nextWord;
    }
    
    printf("\n");
    return;
}

void freeMemory(Word* firstWord, Word* undoStack)
{
    Word* temp;
    
    while (firstWord != NULL)
    {
        temp = firstWord;
        firstWord = firstWord->prevWord;
        free(temp);
    }
    free(firstWord);
    
    while (undoStack != NULL)
    {
        temp = undoStack;
        undoStack = undoStack->prevWord;
        free(temp);
    }
    free(undoStack);
}
