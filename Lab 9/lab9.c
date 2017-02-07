/* 
 * File:   lab9.c
 * Author: hastg2
 *         Holt Skinner
 * Created on November 4, 2015, 3:02 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct router
{
    int ID;
    int travelTimeToLeft;
    int travelTimeToRight;
    struct router* leftRouter;
    struct router* rightRouter;
} Router;

typedef struct packet
{
    int packetID;
    int destinationRouter;
} Packet;

Router* readInRouterData(char* filename);
Router* addTreeLeaf(Router* root, Router* newLeaf);
void handlePacketData(char* filename, Router* root);
Router* findRouter(int* timeElapsed, Router* root, Packet* packet);
void freeTree(Router* root);


Router* bonusRead(char* filename);
void mirrorTree(Router* root);
void printTree(Router* root);
int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255]);

int main(int argc, char** argv) {
    
    Router* root = readInRouterData(argv[1]);
    handlePacketData(argv[2], root);
     
    Router* bonusRoot = bonusRead(argv[1]);
    printTree(bonusRoot);
    mirrorTree(bonusRoot);
    printTree(bonusRoot);
    
    freeTree(root);
    freeTree(bonusRoot);
    return (EXIT_SUCCESS);
}

Router* readInRouterData(char* filename)
{
    FILE* fp = fopen(filename, "r");

    Router* root = NULL;
    Router* new = NULL;
    while(!feof(fp))
    {
        new = (Router*)malloc(sizeof(Router));//Create every new node
        fscanf(fp, "%d %d %d", &new->ID, &new->travelTimeToLeft, &new->travelTimeToRight);//Add info
        new->leftRouter = NULL;
        new->rightRouter = NULL;
        root = addTreeLeaf(root, new);
    }
    fclose(fp);
    return root;
}

Router* addTreeLeaf(Router* root, Router* newLeaf)
{
    //Am I at an open spot in the tree?
    if(root == NULL)
    {
        return newLeaf;
    }
    //Do I go left? 
    if(newLeaf->ID < root->ID)
    {
        root->leftRouter = addTreeLeaf(root->leftRouter, newLeaf);//Make the current root's left pointer point to the new leaf
    }
        
    //Do I go right?
    else
    {
        root->rightRouter = addTreeLeaf(root->rightRouter, newLeaf);
    }
    
    return root;//What do I return?
}

void handlePacketData(char* filename, Router* root)
{
    FILE* fp = fopen(filename, "r");
    Packet* packetPtr = malloc(sizeof(Packet));
    int time = 0;
    printf("\nBegin transmissions:\n");
    while(fscanf(fp, "%d %d", &(packetPtr->packetID), 
            &(packetPtr->destinationRouter)) == 2)
    {
        printf("Packet %d: searching for router %d...", packetPtr->packetID, 
                packetPtr->destinationRouter);
        Router* dest = findRouter(&time, root, packetPtr);
        if(!dest)
        {
            printf("Router not found for packet %d.\n", packetPtr->packetID);
        }
        else
        {
            printf("Router found. Travel time for packet: %d ms\n", time);
        }
        time = 0;
    }
    free(packetPtr);
    fclose(fp);
}

Router* findRouter(int* timeElapsed, Router* root, Packet* packet)
{
    if(root == NULL)//if we get to the end of the tree and it's not there
    {
        return NULL;
    }
    else if(packet->destinationRouter == root->ID)//We found it!!!
    {
        return root;
    }
    else if(packet->destinationRouter < root->ID)//Less than
    {
        *timeElapsed += (root->travelTimeToLeft);
        return findRouter(timeElapsed, root->leftRouter, packet);
    }
    else//greater than
    {
        *timeElapsed += (root->travelTimeToRight);
        return findRouter(timeElapsed, root->rightRouter, packet);
    }

}

void freeTree(Router* root)
{
    if(root != NULL)
    {
        freeTree(root->leftRouter);
        freeTree(root->rightRouter);
        free(root);
    }
    return;
}


int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255])
{
    int i;
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->ID);

    int left  = _printTree(tree->leftRouter,  1, offset,                depth + 1, s);
    int right = _printTree(tree->rightRouter, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }

    return left + width + right;
}

//IGNORE THIS FUNCTION TOO
void printTree(Router *tree)
{
    int i;
    char s[20][255];
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _printTree(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

Router* bonusRead(char* filename)//Read in only 15 routers
{
    FILE* fp = fopen(filename, "r");
    
    Router* root = (Router*)malloc(sizeof(Router));//Create root node
    fscanf(fp, "%d", &root->ID);//Fill root node
    root->leftRouter = NULL;//End the tree
    root->rightRouter = NULL;
    
    int i= 0;//Counter
    while(i<15)
    {
        Router* new = (Router*)malloc(sizeof(Router));//Create every new node
        fscanf(fp, "%d %d %d", &new->ID, &new->travelTimeToLeft, &new->travelTimeToRight);//Add info
        new->leftRouter = NULL;
        new->rightRouter = NULL;
        root = addTreeLeaf(root, new);
        i++;
    }
    fclose(fp);
    return root;
}
void mirrorTree(Router* root)//Flip it all around
{
    Router* hold;
    if (root !=NULL) // #Preorder Traversal with swaps
    {
	hold = root->leftRouter;
        root->leftRouter = root->rightRouter;
        root->rightRouter = hold;
        mirrorTree(root->leftRouter);
        mirrorTree(root->rightRouter);
    }
    
    return;
}
