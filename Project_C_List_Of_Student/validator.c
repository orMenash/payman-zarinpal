#include "validator.h"

Bool isDigit(char ch) { // return 1 if valid.
	if (ch >= '0' && ch <= '9') return 1;
	return 0;
}

Bool validFiedl(char* fieldUser, char* fieldSystem) { // return 1 if true.

	if (strcmp(fieldUser, fieldSystem)) {// if field valid. 
		printf("\"%s\" is invalid field!\n", fieldUser);
		return 0;
	}
	return 1;
}

Bool checkIfValidName(char* name) {// return 0 if valid
	if (onlyLetters(name)) return 0;//if only letters.
	return 1;// if invalid.
}     // return 0 if valid

Bool checkNumDigInStr(char* str, int num) {
	int lenStr = (int)strlen(str);
	if (lenStr == num)
		return 1;
	return 0;
}

Bool onlyNumbers(char* str) {
	if (str == NULL) return 0;
	while (*str) {
		if (isDigit(*str) == 0)
			return 0;
		str++;
	}
	return 1;
}

Bool checkIfValidID(char* ID) {// return 0 if valid
	int flag = 0;
	if (checkNumDigInStr(ID, 9) == 0)// if more then 9 digits.
		flag += 1;
	if (onlyNumbers(ID) == 0) {// if the ID isn't digits only.
		if (flag == 1)
			flag += 2;
		else
			flag += 1;
	}
	return flag;
}// return 0 if vlaid

Bool validMark(char* mark) {// return 0 if valid
	if (mark == 0)
		return -1; // no numberd
	int flag = 0;
	int num;
	if (!isDigit(*mark) && !(*mark == '-'))
		return -2;
	if (onlyNumbers(mark + 1) == 0)
		return -2;/*if invalid mark*/
	num = atoi(mark);
	if (num < 0 || num > 100) {
		if (num == -1) return -1;/*if no number*/
		else return -2;/*if invalid mark*/
	}
	return 0;
}// return 0 if valid

Bool onlyLetters(char* str) {
	while (*str) {
		if ((*str < 'a' || *str > 'z') && *str != ' ')
			return 0;
		str++;
	}
	return 1;
}

Bool validAvg(char* num) {// return 0 if valid
	if (num == 0) return 1;
	char* DecimalNum = NULL;
	char* intNum = strtok(num, ".");
	if (validMark(intNum) == 0) {
		
		if ((DecimalNum = strtok(NULL, "\0")) == NULL || onlyNumbers(DecimalNum))
			return 0;
	}
		
	return 1;
}// return 0 if vlaid


