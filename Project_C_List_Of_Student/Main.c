#include "header.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	List* list = (List*)calloc(1, sizeof(List));/* Manager structure of the list.*/
	if (list == NULL) return errorMessge("Memory allocation failed!\n");/* Checking if memory allocation was successful.*/
	char* fileName = _strdup("students.csv");/* Default filename.*/
	if (fileName == NULL) return errorMessge("Memory allocation failed!\n");/*Checking if memory allocation was successful.*/
	printf("\n\n\n%10cWELLCOM TO -> Student management software.\n\n", ' ');
	fromFileToList(&fileName, list);/*Reading from a file and creating a list of students*/
	printListToConsole(list);
	getQuery(list, fileName);
	saveTOfile(list, fileName);
	free(fileName);
	freeList(list);
	printf("Good Bye :)\n");
	return 0;
}