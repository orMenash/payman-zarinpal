#include "generalFunctions.h"

FILE* openFile(char** fileName, int type) {
	FILE* pFile = NULL;
	while (pFile == NULL) {/*Check if fileName and pFile are not NULL*/
		if (type == in)//in = 0
			pFile = fopen(*fileName, "r+t");
		else
			pFile = fopen(*fileName, "wt");
		if ((*fileName) == NULL || pFile == NULL) {
			printf("Failed to open the file, please enter a different file name or 1 to continu without file.\n");
			free(*fileName);
			//Geting a new file name from the user.
			if ((*fileName = getDinamicStrFromUserOrFile(stdin)) == NULL) return 0;/*If memory allocation failed 5 times return 0*/
			if (!strcmp(*fileName, "1")) {/*If the user entered 1 return 0*/
				return 0;
			}
		}
	}
	return pFile;
}

char toLowerCh(char ch) {
	if (ch >= 'A' && ch <= 'Z')/*If uppercase*/
		ch += 32; /*Update to lowercase*/
	return ch;
}

void toLowerStr(char* str) {
	int i = 0;
	while (str[i]) {/*Run all the string.*/
		str[i] = toLowerCh(str[i]);
		i++;
	}
}

char* getDinamicStrFromUserOrFile(FILE* type) {
	// save pointer to realloc pointer to copy
	char* newDinamicStr = NULL, * saveNewDin = NULL, * desNewDinStr = NULL;
	unsigned int flag = 1, loop = 1, len = 0, prevLen = 0, lenChunkUser = 0;
	static int attempts = 4;
	char chunkUser[CHUNCK];
	while (flag) {
		fgets(chunkUser, CHUNCK, type);/* get chunk string from user.*/
		lenChunkUser = (int)strlen(chunkUser);/* save len.*/
		if (chunkUser[lenChunkUser - 1] == '\n') {/*check if is end the string of user by \n */
			chunkUser[lenChunkUser - 1] = '\0';/*update \n to \0*/
			lenChunkUser--;
			flag = 0;/*update to 0 to finishe get chuncks*/
		}
		prevLen = len;
		len += lenChunkUser;/*update new len*/
		if (loop == 1) {/*to know if need malloc or realloc*/
			newDinamicStr = (char*)malloc((len + 1) * sizeof(char));
			if (newDinamicStr == NULL && attempts > 0) {
				printf("Memory allocation failed! (%d)\n -> ", attempts + 1);
				attempts--;
				return getDinamicStrFromUserOrFile(type);
			}
			else if (newDinamicStr == NULL) {
				printf("Memory allocation failed! (%d)\n", attempts + 1);/*if memory allocation failed write error and return NULL*/
				attempts = 5;
				return 0;
			}
		}
		else {/*if need realloc*/
			saveNewDin = (char*)realloc(newDinamicStr, (len + 1) * sizeof(char));

			if (newDinamicStr == NULL && attempts > 0) {
				printf("Memory allocation failed! (%d)\n -> ", attempts + 1);
				attempts--;
				return getDinamicStrFromUserOrFile(type);
			}
			else  if (newDinamicStr == NULL) {
				printf("Memory allocation failed! (%d)\n", attempts + 1);/*if memory allocation failed write error and return NULL*/
				attempts = 5;
				return 0;
			}
			newDinamicStr = saveNewDin;
		}
		if (newDinamicStr + prevLen != NULL)
			strcpy(newDinamicStr + prevLen, chunkUser);
		loop++;
	}
	attempts = 5;/*update to 5 times*/
	toLowerStr(newDinamicStr);
	return newDinamicStr;
}

int copyDynamicStr(char** des, char* corce) {
	char* tempField = NULL; /* to save the old data field (if alloction filed). */
	tempField = _strdup(*des); /* copy the old data field. */
	if (tempField == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	free(*des);
	*des = _strdup(corce);
	if (*des == NULL) {/* Checking if memory allocation was successful.*/
		*des = tempField;
		printf("Memory allocation failed!\n");
		return 0;
	}
	free(tempField);
	return 1;
}