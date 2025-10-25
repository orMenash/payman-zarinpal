#pragma once
#ifndef printFunctions
#define pritnFunctions
#include "studentList.h"

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







#endif // !printFunctions
