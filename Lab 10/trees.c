
#include <stdio.h>
#include <stdlib.h>
#include "fxns.h"

Student* searchForStudent(Student* root, int ID)
{
    if(!root)
    {
        return NULL;
    }
    
    if(root->ID == ID)
    {
        return root;
    }
    else if(root->ID > ID)
    {
        return searchForStudent(root->leftStudent, ID);
    }
    else
    {
        return searchForStudent(root->rightStudent, ID);
    }
}

Student* addLeaf(Student* root, Student* newNode)
{
    if(!root)
    {
        return newNode;
    }
    
    if(root->ID > newNode->ID)
    {
        root->leftStudent = addLeaf(root->leftStudent, newNode);
    }
    else
    {
        root->rightStudent = addLeaf(root->rightStudent, newNode);
    }
    
    return root;
}

Student* readTotalStudentsAndMakeTree(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    #ifdef TEST
    assert(fp != NULL)
    #endif

    Student* node = NULL;
    Student* root = NULL;
    int fxnCheck = 0;
    while(!feof(fp))
    {
        node = malloc(sizeof(Student));
        
        #ifdef TEST
        assert(node != NULL)
        #endif

        //reads a student from the file. Every student has an 8 digit student ID, a GPA, and a first and last name.
        fxnCheck = fscanf(fp, "%d %f %s %s",
                &(node->ID), &(node->GPA), node->fname, node->lname);
        
        #ifdef TEST
        assert((node->ID>=10000000) && (node->ID <=99999999))
        assert(node->GPA>=0.0 && node->GPA<=4.0)
        assert(node->fname != NULL)
        assert(node->lname != NULL)
        #endif

        node->leftStudent = NULL;
        node->rightStudent = NULL;
        root = addLeaf(root, node);
        
        #ifdef TEST
        assert(root != NULL)
            //is the root's left what it should be?
            //is the root->left's left and right what it should be?
            //is the root's right what it should be?
            //is the root what it should be?
        #endif
    }
    return root;
}