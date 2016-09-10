#include <stdio.h>
#include <stdlib.h>

#include "fxns.h"


Student* readStudentsForClassAndMakeQ(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    #ifdef TEST
    assert(fp != NULL)
    #endif

    float requiredGPA;
    int ID;
    int fxnCheck = 0;
    Student* node = NULL;
    Student* head = NULL;
    Student* tail;
    
    //This is the GPA every student must have to enroll into the class.
    fscanf(fp, "%f", &requiredGPA);
    
    #ifdef TEST
    assert(requiredGPA >= 0.0 && requiredGPA < 4.1)
    #endif

    while(!feof(fp))
    {
        node = malloc(sizeof(Student));
        
        #ifdef TEST
        assert(node != NULL)
        #endif

        //reads a student from the file. Every student has an 8 digit student ID, a GPA, and a first and last name.
        //later on, this student will be cross referenced with the set of students to make sure he/she is a valid student.
        fxnCheck = fscanf(fp, "%d %f %s %s",
                &(node->ID), &(node->GPA), node->fname, node->lname);
        
        #ifdef TEST
        assert(node!=NULL)
        assert((node->ID>=10000000) && (node->ID <=99999999))
        assert(node->GPA>=0.0 && node->GPA<=4.0)
        assert(node->fname != NULL)
        assert(node->lname != NULL)
        assert(node->GPA >= requiredGPA)
            
        #endif
        
        //Only the rightStudent ptr will be used...all leftStudent ptrs will be NULL. This will
        //ensure a one-way list. 
        
        node->rightStudent = NULL;
        node->leftStudent = NULL;
        head = addStudentToQ(head, node);
        tail = node;
        #ifdef TEST
        assert(node->leftStudent == NULL)
        assert(node!=NULL)
        assert(head !=NULL)
        assert(tail !=NULL)
        assert(tail == node)
        #endif

        node = NULL;
    }
    return head;
}

Student* addStudentToQ(Student* head, Student* newNode)
{
    if(!head)
    {
        return newNode;
    }
    
    Student* tmp = head;
    while(tmp->rightStudent != NULL)
    {
        tmp = tmp->rightStudent;
    }
    tmp->rightStudent = newNode;
    return head;
}

Student* removeStudentFromQ(Student** head)
{
    if((*head)->rightStudent == NULL)
    {
        Student* tmp = *head;
        *head = NULL;
        return tmp;
    }
    
    Student* tmp = (*head);
    *head = (*head)->rightStudent;
    tmp->rightStudent = NULL;
    return tmp;
    
}
