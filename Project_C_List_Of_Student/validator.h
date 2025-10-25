#pragma once
#ifndef validator
#define validator

#include "main.h"

Bool isDigit(char ch); // return 1 if valid.

// The function checks if the user entered valid field and return 1 if valid.
Bool validFiedl(char* fieldUser, char* fieldSystem);// return 1 if true.

Bool checkIfValidName(char* name);

// The function gets string of number and number (int), and return 0 if the digits in string equal to number.
Bool checkNumDigInStr(char* str, int num);// return 0 if valid

// The function checks if the string is only numbers and return 1 if there are only numbers.
Bool onlyNumbers(char* str);

// The function checks if the ID is valid and return 0 if the ID is valid.
Bool checkIfValidID(char* ID);// return 0 if valid

// The function checks if the grade(int) is valid and return 0 if the grade is valid.
Bool validMark(char* mark);

// The function checks if the string is only letters and return 1 if there are only letters.
Bool onlyLetters(char* str);

// The function checks if the grade(float) is valid and return 0 if the grade is valid.
Bool validAvg(char* num);// return 0 if valid


#endif // !falidator

