#include "printFunctions.h"

void printTitle() {
	char row = 196, col = 179;
	char* cours1 = "c lang", * cours2 = "Computer Networks", * cours3 = "CS Fundamentals", * average = "Average";
	char* ID = "ID", * secondName = "second name", * firstName = "first name", * warnings = "Warnings";
	printf("%10cgrades options : -1 = No grade, -2 = Invalid grade\n", ' ');
	printRowToConsole();
	printf("%10c%-3s%c%-12s%c%-12s%-5c%-6s%c", col, "num", col, firstName, col, secondName, col, ID, col);
	printf("%-7s%c%-18s%c%-16s%c%-8s%-7c%-17s\n", cours1, col, cours2, col, cours3, col, average, col, warnings);
	printRowToConsole();
}

void printIntroduction() {
	printf("\n%10cintroduction\n", ' ');
	printf("%10cThe use of the software\n", ' ');
	printf("%10c1. print : print all students. exampel -> \"print\"\n", ' ');
	printf("%10c2. select : Prints students who meet the condition. example -> \"select first name > gil\"\n", ' ');
	printf("%10c3. set : add or update student. examle -> \"set first name = or, second name = menashe, id = 123456789, c lang = 96\"\n%13cIt is not possible to change an ID and a first name.\n", ' ', ' ');
	printf("%13cA name cannot contain two names, if the name contains two names you can use _ for example ben_or.\n", ' ');
	printf("%10c4. remove : Remove student by ID. example -> \"remove 123456789\"\n", ' ');
	printf("%10c5. quit : Quit from the software and save information. exampel -> \"quit\"\n", ' ');

}

void printListToConsole(List* list) {
	Student* ptr = list->head;/*pointer to head of list*/
	int num = 0;/*number of student*/
	if (ptr == NULL)/*If the list is empty*/
		printf("The list is empty!\n");
	else {
		printTitle();
		while (ptr) {
			num++;
			printStudentToConsole(ptr, num);
			ptr = ptr->next;/*next student*/
		}
	}
}

void printRowToConsole() {
	char row = 196, col = 179;/*to print row and column*/
	for (int i = 0; i < 116; i++) {
		switch (i)
		{
		case 0:/*begining of the row*/
			printf("%10c", col);
			break;
		default:
			printf("%c", row);
			break;
		}
	}
	printf("\n");
}

void printStudentToConsole(Student* stud, int num) {
	char* arrNameCourses[] = ARRAY_OF_NAME_COURSES;/*Creat array of courses name*/
	char row = 196, col = 179;/*to print row and column*/

	printf("%10c%-3d%c%-12s%c%-12s%c%-10s%-3c", col, num, col, stud->firstName, col, stud->secondName, col, stud->ID, col);
	printf("%-5d%-9c%-10d%-8c%-9d%c%-8.2f%c", stud->marks[0], col, stud->marks[1], col, stud->marks[2], col, stud->avg, col);
	if (stud->validFirstName)/*If invalid first name*/
		printf("*first name ");
	if (stud->validSecondName)/*If invalid second name*/
		printf("*second name ");
	if (stud->valid_ID)/*If ivalid ID*/
		printf("*ID ");
	for (int i = 0; i < NUM_OF_COURSES; i++) {/*Run on all vaildMarks of course*/
		if (stud->validMark[i] == -2)/*If invalid mark*/
			printf("*%s ", arrNameCourses[i]);
	}
	printf("\n");
	printRowToConsole();
}






