/* 
 * File:   Lab5.c
 * Author: hastg2
 *          Holt Skinner
 * Created on September 30, 2015, 3:04 PM
 */

typedef struct student
{
    char FName[20];
    char LName[20];
    float GPA;
    int ID;
} Student;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Compile error, caused stringcmp to not be recodnised, String library not included, added string library

//Student* ReadStudents(char* filename, int* numStudentsRef);
Student* readStudents(char* filename, int* numStudentsRef);
//Compile error, Misspelled function prototype, changed uppercase r to lowercase r
void printStudents(Student* students, int numStudents);
Student* searchStudentID(Student* students, int low, int high, int targetID);
Student* sortStudentsByID(Student* students, int numStudents);
Student* findHighestGPA(Student* students, int numStudents); 
void writeToReadableFile(Student* students, int numStudents, char* filename);
void driver(char* filename, char* filename2);
Student* sortStudentsByLastName(Student* students, int numStudents);
//Compile error, missing function prototype, Added Function prototype

int main(int argc, char** argv) {
    
    //driver(argv[0], argv[1]); 
    driver(argv[1], argv[2]);
    //Logical error,Sending wrong elements of argv, (./a.out and binaryFile instead of binaryFile and output)
    
    return (EXIT_SUCCESS);
}

void driver(char* filename, char* filename2)
{
    int numStudents;
    Student* students = readStudents(filename, &numStudents);
    
    printf("Students: \n");//Spelling error???
    printStudents(students, numStudents);
    
    
    //printf("The highest GPA is %.2f.\n", findHighestGPA(students, numStudents).GPA);
    printf("The highest GPA is %.2f.\n", findHighestGPA(students, numStudents)->GPA);
    //Compile Error, Used incorrect structure notation, findHighestGpa returns a student pointer, not a student
    
    printf("------------\nStudents sorted by last name:\n");
    students=sortStudentsByLastName(students, numStudents);
    printStudents(students, numStudents);
    
    students = sortStudentsByID(students, numStudents);
    int ID;
    int control;
    while(1)
    {
        printf("------------\nGive me a student ID to search for: ");
        //scanf("%d", ID);
        scanf("%d", &ID); 
        //Segmentation fault (didn't cause a compile error), no & on ID variable, added &
        
        //Student* result = searchStudentID(students, numStudents-1, ID);
        Student* result = searchStudentID(students, 0, numStudents, ID);
        //compile error, Not enough arguments, sent high, but not low, added "0" as low value
        
        //if(result = NULL)
        if(result == NULL)
            //logic error, causing if to never take effect, added an extra equals sign
        {
            printf("Student not found.\n");
        }
        else
        {
            printf("Found student: \n");
            printStudents(result, 1);
        }
        printf("\n\nEnter 0 to quit or 1 to search for another ID: ");
        scanf("%d", &control);
        //while(control != 1 || control != 0)
            //logic error, caused infinite while loop, while never fails, changed || to &&
        while(control != 1 && control != 0)//
        {
            printf("Sorry, I don't understand that command. Try again.\n");
            printf("\n\nEnter 0 to quit or 1 to search for another ID: ");
            scanf("%d", &control);
        }
        if(control == 0)
        {
            break;
        }
    }
    
    writeToReadableFile(students, numStudents, filename2);
    
}

Student* readStudents(char* filename, int* numStudentsRef)
{
    FILE* fp = fopen(filename, "r");
    
    fseek(fp, 0, SEEK_END);
    
    //numStudentsRef = (int)ftell(fp) / sizeof(Student);
    *numStudentsRef = (int)ftell(fp) / sizeof(Student);
    //Compiler error, Didn't dereference the pointer, types were incompatible variable types, added an asterisk
    rewind(fp);
    
    //Student* students;
    Student* students = malloc(sizeof(Student)* (*numStudentsRef));
    //segmentation fault, Missing malloc, creating empty pointer
    
    //fread(&students, sizeof(Student), *numStudentsRef, fp);
    fread(students, sizeof(Student), *numStudentsRef, fp);
    //segmentation fault, Didn't need the "&" students is already a pointer
    
    //free(students)
    //Compile error, Can't free pointer that's returning 
    fclose(fp);
    
    return students;  
}

void printStudents(Student* students, int numStudents)
{
    int i = 0; 
    //for(; i < numStudents; i++)
    //logic error, No first argument in the for loop,added i=0 
    for (i = 0; i<numStudents; i++)
    {
        //printf("-----%s %s\n\tGPA: %f\n\tStudent ID: %d\n------\n", 
        printf("-----%s %s\n\tGPA: %.2f\n\tStudent ID: %d\n------\n", 
                //Cosmetic/logic Error, printing out full float value instead of first two decimal points
                students[i].FName, students[i].LName, students[i].GPA, students[i].ID);
        //students.FName, students.LName, students.GPA, students.ID);
                //compile error, no clarification of array element, added [i] to clarify which student's information is being printed out]
    }
    
    //return 0; 
    return;
    //compile error, function is void, can't return 0, removed the zero
}

Student* searchStudentID(Student* students, int low, int high, int targetID)
{
    //if(low<=high)
    //logic error, Causing it to always return NULL, changed inequality to the opposite
    if(low > high)
    {
        return NULL;
    }
    
    int mid = (low+high)/2;
    
    //if(targetID == students[mid])
    if(targetID == students[mid].ID)
        //compile error, trying to compare an int to an entire student, added ".ID"
    {
        return &students[mid];
    }
    //else if(targetID > students[mid].ID)
    //Logic Error, inequality was switched around causing binary search to not work correctly, switched the inequality and the search works properly
    else if(targetID < students[mid].ID)
    {
        //return searchStudentID(students, low, mid, targetID);
        return searchStudentID(students, low, mid-1, targetID);
        //logic error, put mid instead of mid-1, wouldn't search between right values
    }
    else
    {
        return searchStudentID(students, mid+1, high, targetID);
    }
}

Student* findHighestGPA(Student* students, int numStudents)
{
    Student* max = &students[0];
    int i = 1;
    for(i; i < numStudents; i++)
    {
        if(students[i].GPA > max->GPA)
        {
            max = &students[i];
        }
    }
    
    return max;
}

Student* sortStudentsByLastName(Student* students, int numStudents)
{
    int i, j, min;
    
    for(j = 0; j < numStudents-1; j++)
    {
        for(i = j+1; i < numStudents; i++)
        {
            //if(strcmp(students[i].LName, students[min].LName) > 0) 
            if(strcmp(students[i].LName, students[min].LName) < 0)
                //Logic error, was causing sort to not work correctly, inequality facing the wrong direction, switched the inequality and the program sorted correctly
            {
                min = i;
            }
        }
        
        if(min != j)
        {
            //int tmp = students[j];
            Student tmp = students[j];
            //compile error, incorrect type for tmp, changed it to a type Student
            students[j] = students[min];
            students[min] = tmp;
        }
    }
    
    return students;
}

Student* sortStudentsByID(Student* students, int numStudents)
{
    int i, j, min;
    for(j = 0; j < numStudents-1; j++)
    {
        min = j;
        for(i = j+1; i < numStudents; i++)
        {
            if(students[i].ID < students[min].ID)
            {
                min = i;
            }
        }
        
        if(min != j)
        {
            //int tmp = students[j];
            Student tmp = students[j];
            //incorrect type for temp
            students[j] = students[min];
            students[min] = tmp;
        }
    }
    
    return students;
}

void writeToReadableFile(Student* students, int numStudents, char* filename)
{
    FILE* fp = fopen(filename, "w");
    int i = 0;
    for(;i < numStudents; i++)
    {
        fprintf(fp, "%s %s\n", students[i].FName, students[i].LName);
        //fprintf(fp, "%d %d\n", &students[i].GPA, &students[i].ID);
        fprintf(fp, "%.2f %d\n", students[i].GPA, students[i].ID);
        //Logic errors (I'm surprised it wasn't a compile error) had invalid &'s and was trying to print GPA as an int instead of a float, wasn't printing out correctly, removed ampersands and changed %d to %.2f,  
    }
    fclose(fp);
    free(students);
    return;//No error, just bad coding practice return was missing, added return
}