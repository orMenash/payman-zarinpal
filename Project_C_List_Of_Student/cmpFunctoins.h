#pragma once
#ifndef cmpFunctions
#define cmpFunctions
#include "studentList.h"

// the function runs over on all the list of student checks the condition and prints this student if the condition is met.
void  genericCmpFunc(Student* head, Bool(*cb)(void*, void*), int localFilesInStruct, void* dataUser); Bool checkIfValidName(char* name);

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

#endif // !cmpFunctions

