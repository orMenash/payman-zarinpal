#pragma once
#ifndef genefalFunction
#define generalFunction

#include "main.h"

// the function gets file name and open this file and if this name is not exists the function asks new name.
FILE* openFile(char** fileName, int type);

// Update uppercase to lowercase
char toLowerCh(char ch);

// the function change all capital leters to lower cases.
void toLowerStr(char* str);

//return pointer to string from user or file.
char* getDinamicStrFromUserOrFile(FILE* type1);

// The function copies a string to new char* and if it was not successful, it keeps the old string.
int copyDynamicStr(char** des, char* corce); //The function returns 1 if it succeeded in copying.


#endif // !genefalFunction

