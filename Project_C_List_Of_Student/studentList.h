#pragma once
#ifndef studentList
#define studentList
#include "main.h"

// FIELDS OPTIONS.
#define CREATE_FIELDS_ARR {"first name", "char", "second name", "char", "id", "char", "c lang", "int", "computer networks", "int", "cs fundamentals", "int", "average", "float"}
#define CREATE_CONDITION_ARR {"=", "!=", ">", "<"}// CONDITION OPYTIONS.
#define columns 7 // columns to print (fields options).
#define ARRAY_OF_NAME_COURSES {"c lang", "computer networks", "cs fundamentals"}
#define NUM_OF_COURSES 3/*number of courses*/
 
typedef struct student {
	struct student* next;/*Pointer to next student in the list*/

	char* firstName;
	char* secondName;
	char* ID;
	int marks[NUM_OF_COURSES];  // {0 : c lang}, {1 : computer networks}, {2 : cs fndamentals};  // value:   -1 -> did'nt do.    -10 -> invalid mark.
	float avg;/*average of all vlaid course marks*/

	char validMark[NUM_OF_COURSES];// {0: valid}, { 1: invlid mark }, {2: No grade}
	unsigned char validFirstName : 2;// {0: valid}, {1: invlid name}, {2, change first name};
	unsigned char validSecondName : 1;// {0: valid}, {1: invlid name}
	unsigned char valid_ID : 1;// {0: valid}, {1: invlid ID}

}Student;

typedef struct list {
	Student* head;/*Head of list of studnets*/
}List;


// //-------------------------------------------------------------------------
// addToHead
// ---------
// 
// General: The function get studetn struct and add to head the list.
// 
// Parameters :
//		list - Pointer to struct list (head of list).
//		stud - Pointer to struct studet to add.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void addToHead(List* list, Student* stud);

void addAfterStud(Student* newStud, Student* prevStud);

//add student to list by second name.
void AddStudToSortedList(List* list, Student* newStud);

//-------------------------------------------------------------------------
// removeFromList
// --------------
// 
// General: The function get query from user, take the ID from query
//			and remove this studnet or print that this ID dose not exist.
// 
// Parameters :
//		list - Pointer to struct list (head of list).
//		query - query from user to get ID student.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void removeFromList(List* list, char* query);

//remove student from the head of list.
Student* removeFromHead(List* list);

//remove student from the list.
void removeStud(Student* prevsStud, Student* stud);

// the function creates new student or updates exists student and return this student.
Student* creatStud(char* fN, char* sN, char* ID, int typeCourse, char* mark);

//---------------------------------------------------------------------
// freeStud
// --------
// 
// General: The function free a student struct. 
// 
// Parameters :
//  stud - pointer to student struct.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void freeStud(Student* stud);

//---------------------------------------------------------------------
// freeList
// --------
// 
// General: The function free the entire list of students (student struct) and The List struct.
// 
// Parameters :
// list - pointer to manager struct of list of students.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void freeList(List* list);

//-------------------------------------------------------------------------
// updateStud
// ----------
// 
// General: the function updates the student in the list - updates marks and second name, 
//			if the second name is different, it sends to sort.
// 
// Parameters :
//		list - pointer to head of list.
//		newStd - student struct that got from user.
//		index - to get the student from the list.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void updateStud(List* list, Student* newStd, int index);

// the function update the average of student.
void updateAvg(Student* stud);

// updateing ID of student (if the id invalid in the file and the user want to updeat).
char* updateID();

// the function runs over on all the studnet list and return his index or -1 if no is not exists.
int getIndexOfStudent(Student* studUser, List* list);

//return pointer to student from list (by index of student).
Student* getStudByIndex(int index, List* list);

// The function gets line from file creates data and sends to function create student. 
Student* creatStudFromFile(char* line);

//---------------------------------------------------------------------
// fromFileToList
// --------
// 
// General: The function opens file reads the data and creates list of student.
// 
// Parameters :
//  fileName - pointer to string of name of file.
//  list - pointer to manager struct list.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
int fromFileToList(char** fileName, List* list);

#endif // !studentList

