/* 
 * File:   prelab9.c
 * Author: Holt Skinner
 *         hastg2
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct router
{
    int ID;
    struct router* leftRouter;
    struct router* rightRouter;
} Router;

/*
 * You are to read in some router IDs, and create a BST out of it. 
 * After you create the tree, the program will print out a nice little
 * tree so you can check and see if nodes were added correctly. Then free 
 * the tree.
 * 
 * THERE ARE IMPORTANT NOTES DOWN BY THE PRINT TREE FUNCTION.
 */

Router* readInRouterData(char* filename);
Router* addTreeLeaf(Router* root, Router* newLeaf);
void freeTree(Router* root);
void printTree(Router* root);
int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255]);

//Don't have to touch main. It gets the root of the tree you made,
//then prints out the tree and calls your free implementation.
int main(int argc, char** argv) {
    Router* root = readInRouterData(argv[1]);
    printTree(root);
    freeTree(root);
    return (EXIT_SUCCESS);
}

//Input: the name of the file that has the router IDs
//Return: the root of the BST
//Read in each router ID, put that ID into a new node, then add the node to the
//tree using the addTreeLeaf function.
Router* readInRouterData(char* filename)
{
    //Need a loop so you can get every node value from the file.
    FILE* fp = fopen(filename, "r");
    
    Router* root = (Router*)malloc(sizeof(Router));//Create root node
    fscanf(fp, "%d", &root->ID);
    root->leftRouter = NULL;
    root->rightRouter = NULL;
    
    while(!feof(fp))
    {
        Router* new = (Router*)malloc(sizeof(Router));//Create every new node
        fscanf(fp, "%d", &new->ID);//Add info
        new->leftRouter = NULL;
        new->rightRouter = NULL;
        root = addTreeLeaf(root, new);
    }
    //Make a node for every ID, add it to the tree. Repeat. 
    //Remember to keep track of the root!
    //Remember to do something with the pointers in the new nodes!
    
    //Return the root. Remember to close your file. 
    fclose(fp);
    return root;
}

//Input: the root of a BST, and the new node to be added.
//Return: the root of the tree/subtree.
//Use techniques learned in class to recursively go through the tree
//and add the new node to the tree.
Router* addTreeLeaf(Router* root, Router* newLeaf)
{
    //Am I at an open spot in the tree?
    if(root == NULL)
    {
        root = newLeaf;
        root->leftRouter = NULL;
        root->rightRouter = NULL;
        return root;
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

//Input: the root of a BST
//Return: none
//Free the tree, using techniques learned in class.
void freeTree(Router* root)
{
    //Free EVERYTHING.
    
    if(root != NULL)
    {
        freeTree(root->leftRouter);
        freeTree(root->rightRouter);
        free(root);
    }
    return;
}

//IGNORE THIS FUNCTION
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