#pragma once
#ifndef source
#define source

#include "cmpFunctoins.h"
#include "validator.h"


//return pointer to value field of user (from query).
char* valueFieldUser(char** query);

// The function gets the query and create new student or updates exists student.
void set(char* query, List* list, char* fielName);

//select action -> get field, condition and value frome a query and check all students in the list.
void select(char* query, Student* head);

//creating new file with all information sorted from list. 
void saveTOfile(List* list, char* fileName);

//The function receives a query from the user and sends to the appropriate function (sellct, print, set, quit, remove).
void getQuery(List* list, char* fileName);

char* getFieldOfSet(char** query, char* fieldUser);

//get query and return char* of field.
char* getField(char** query);

//return char* of condition in query.
char* getCondition(char** query);

//return int of type course.
int getTypeCorse(char* cours);

//update "localFilesInStruct" to address of field in struct (by offsetof), and update "validDataUser"(generic function) to correct function.
int getFieldType(char* fieldUser, int* localFilesInStruct);

//return type of operator -> {1 : =}, {2 : !=}, {3 : >}, {4 : <}
int getConditionType(char* condUser);

//return pointer to function of condition and type(int, char, float).
void* getFunction(char fieldUserType, char condUserType);

// get the query and return the action (sellct, print, set, quit, remove).
char* getAction(char** query);

// The function gets the query of user and retunr the field.
char* getFieldSet(char** query);

// get new name form user and return pointer to name.
char* getNewName();

#endif // !source
