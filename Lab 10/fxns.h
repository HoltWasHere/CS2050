/* 
 * File:   fxns.h
 * Author: hastg2
 *
 * Created on November 11, 2015, 4:05 PM
 */

#ifndef FXNS_H
#define	FXNS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define assert(condition){                  \
    if(!(condition))                        \
    {                                       \
        printf("Assertion failed:\n");      \
        printf("Line: %d\nFile: %s\n",      \
                __LINE__, __FILE__);        \
        exit(0);                            \
    }                                       \
}
    

    
typedef struct studentNode
{
    int ID;
    float GPA;
    char fname[20];
    char lname[20];
    struct studentNode* leftStudent;
    struct studentNode* rightStudent;
} Student;


Student* addLeaf(Student*, Student*);
Student* readTotalStudentsAndMakeTree(char*);
Student* searchForStudent(Student*, int);

Student* readStudentsForClassAndMakeQ(char*);
Student* addStudentToQ(Student*, Student*);
Student* removeStudentFromQ(Student**);


#ifdef	__cplusplus
}
#endif

#endif	/* FXNS_H */

