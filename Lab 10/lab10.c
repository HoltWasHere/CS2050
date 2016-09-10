/* 
 * File:   lab10.c
 * Author: hastg2
 *
 * Created on November 11, 2015, 3:38 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "fxns.h"








int main(int argc, char** argv) {
    //Should fire if you did your Makefile correctly.
    #ifdef TEST
        printf("**************You have successfully triggered the preprocessor definition******************\n");
    #endif
    //Uncomment this and rerun if you can't get it to work. Comment it back out once it works.
    //assert(1 > 2);
    Student* root = readTotalStudentsAndMakeTree(argv[1]);
    Student* head = readStudentsForClassAndMakeQ(argv[2]);
    #ifdef TEST
    assert(root != NULL)
    assert(head != NULL)        
    #endif

    Student* nextStudent;
    Student* checkStudent;
    while(head)
    {
        nextStudent = removeStudentFromQ(&head);
        #ifdef TEST
        assert(nextStudent != NULL)
        #endif
        
        checkStudent = searchForStudent(root, nextStudent->ID);
        
        #ifdef TEST
        assert(checkStudent != NULL)
        #endif

        printf("%s %s has been enrolled into the class.\n",
                nextStudent->fname, nextStudent->lname);
        free(nextStudent);
    }
    
    return (EXIT_SUCCESS);
}


