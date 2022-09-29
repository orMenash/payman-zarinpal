#pragma once


#pragma once
#ifndef MAIN_PROJECT
#define MAIN_PROJECT

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
#define GO_TO break
// FIELDS OPTIONS.
#define CREATE_FIELDS_ARR char* fieldsArr[14] = {"first name", "char", "second name", "char", "id", "char", "c lang", "int", "computer networks", "int", "cs fundamentals", "int", "average", "float"};
#define CREATE_CONDITION_ARR char* condArr[4] = {"=", "!=", ">", "<"};// CONDITION OPYTIONS.
#define columns 7 // columns to print (fields options).
#define ARRAY_OF_NAME_COURSES char* arrNameCourses[] = {"c lang", "computer networks", "cs fundamentals"};
#define NUM_OF_COURSES 3/*number of courses*/
typedef char Bool;/*To retunr bool from functions.*/

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




// The function gets the query of user and retunr the field.
char* getFieldSet(char** query);

// get new name form user and return pointer to name.
char* getNewName();

//return pointer to value field of user (from query).
char* valueFieldUser(char** query);

//return pointer to student from list (by index of student).
Student* getStud(int index, List* list);



//return pointer to string from user or file.
char* getDinamicStrFromUserOrFile(FILE* type1);

//return char* of field.
char* getField(char** query);

//return int of type course.
int getTypeCorse(char* cours);

//return char* of condition in query.
char* getCondition(char** query);

//update "localFilesInStruct" to address of field in struct (by offsetof), and update "validDataUser"(generic function) to correct function.
int getFieldType(char* fieldUser, int* localFilesInStruct, Bool(**validDataUser)(char*));

//return type of operator -> {1 : =}, {2 : !=}, {3 : >}, {4 : <}
int getConditionType(char* condUser);

//return pointer to function of condition and type(int, char, float).
void* getFunction(char fieldUserType, char condUserType);

// get the query and return the action (sellct, print, set, quit, remove).
char* getAction(char** query);

// the function runs over on all the list of student checks the condition and prints this student if the condition is met.
void  genericCmpFunc(Student* head, Bool(*cb)(void*, void*), int localFilesInStruct, void* dataUser); Bool checkIfValidName(char* name);

// the function runs over on all the studnet list and return his index or -1 if no is not exists.
int getIndexOfStudent(Student* studUser, List* list);

// the function update the average of student.
void updateAvg(Student* stud);

// updateing ID of student (if the id invalid in the file and the user want to updeat).
char* updateID();

// the function gets field of student and new data , and update this field to new data.
int changeField(char** studFiles, char* newStudField);

// the function gets file name and open this file and if this name is not exists the function asks new name.
FILE* openFile(char** fileName, char* type);

// the function change all capital leters to lower cases.
void toLowerStr(char* str);

//The function receives a query from the userand sends to the appropriate function (sellct, print, set, quit, remove).
void getQuery(List* list, char* fielName);

// The function sends to appropriate check condition function.
void select(char* query, Student* head);

// The function gets the query and create new student or updates exists student.
void set(char* query, List* list, char* fielName);

// The function runs over all the list and save to new file 
void saveTOfile(List* list, char* fileName);

// The function gets line from file creates data and sends to function create student. 
Student* creatStudFromFile(char* line);

// the function creates new student or updates exists student and return this student.
Student* creatStud(char* fN, char* sN, char* ID, int typeCourse, char* mark);

// The function checks if the user entered valid field and return 1 if valid.
Bool validFiedl(char* fieldUser, char* fieldSystem);

// The function gets string of number and number (int), and return 1 if the digits in string equal to number.
Bool checkNumDigInStr(char* str, int num);

// The function checks if the string is only numbers and return 1 if there are only numbers.
Bool onlyNumbers(char* str);

// The function checks if the ID is valid and return 1 if the ID is valid.
Bool checkIfValidID(char* ID);

// The function checks if the grade(int) is valid and return 1 if the grade is valid.
Bool validMark(char* mark);

// The function checks if the string is only letters and return 1 if there are only letters.
Bool onlyLetters(char* str);

// The function checks if the grade(float) is valid and return 1 if the grade is valid.
Bool validAvg(char* num);

// -------------------------------------------------------------------------
// CONDITIONS_FUNCTIONS
// --------------------
// 
// General: The functions compare the user's data with the student structure.
//		Cmp: Return 1 if equle else  return 0.
//		NotCmp: Return 1 if not equle else return 0.
//		Big: Return 1 if the value of struct student is greater than the user's data else return 0.
//		small: return 1 if the value of struct student is smaller than the user's data else return 0.
// 
// Parameters : void* -> the functions do coustint to int or char*.
//		numUser - int from user to equle.
//		strUser - string from user to equle.
//		numStud - int from student struct to equle.
//		strStud - string from student struct to equle.
// 
// Return Value : Bool(char) -> 1 or 0;
// 
//-------------------------------------------------------------------------
//--------------- == -------------------
Bool intCmp(void* numUser, void* numStud);
Bool charCmp(void* strUser, void* strStud);
Bool floatCmp(void* numUser, void* numStud);
//--------------- != -------------------		
Bool intNotCmp(void* numUser, void* numStud);
Bool charNotCmp(void* strUser, void* strStud);
Bool floatNotCmp(void* numUser, void* numStud);
//--------------- > -------------------		
Bool intBig(void* numUser, void* numStud);
Bool charBig(void* strUser, void* strStud);
Bool floatBig(void* numUser, void* numStud);
//--------------- < -------------------		
Bool intSmall(void* numUser, void* numStud);
Bool charSmall(void* strUser, void* strStud);
Bool floatSmall(void* numUser, void* numStud);


//===========================LIST_FINISHE==========================
//add student to list by second name.
void AddStudToSortedList(List* list, Student* newStud);

//remove student from the list.
void removeStud(Student* prevsStud, Student* stud);

//remove the head of list (student) and update head to next student.
Student* removeFromHead(List* list);
// 
// 
// 
// 
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
// 
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
// 
// 

//==========print_functions================================================================
//-------------------------------------------------------------------------
// errorMessge
// -----------
// 
// General: The function prints to console strError that it got.
// 
// Parameters : 
//	strError - pointer of string to print.
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void* errorMessge(char* strError);

//-------------------------------------------------------------------------
// printStudentToConsole
// ---------------------
// 
// General: The function prints all the information of student struct to console.
// 
// Parameters : None
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void printStudentToConsole(Student* stud, int num);

//-------------------------------------------------------------------------
// printListToConsole
// ------------------
// 
// General: The function pritns to console all the studnets in the list.
// 
// Parameters : None
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void printListToConsole(List* list);

//---------------------------------------------------------------------
// printRowToConsole
// -----------------
// 
// General: The function prints to console a row
// 
// Parameters : None
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void printRowToConsole();

//---------------------------------------------------------------------
// printIntroduction
// -----------------
// 
// General: The function prints to consol the introduction of the software.
// 
// Parameters : None
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void printIntroduction();

//---------------------------------------------------------------------
// printTitle
// ----------
// 
// General: The function prints the title of the table of students.
// 
// Parameters : None
// 
// Return Value : None
// 
//----------------------------------------------------------------------
void printTitle();

//
//
//
//
//==========================================================================
// 
// 
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


#endif // !MAIN_PROJECT



