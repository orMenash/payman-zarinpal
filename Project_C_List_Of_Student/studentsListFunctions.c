#include "studentList.h"
#include "generalFunctions.h"
#include "source.h" 



void addToHead(List* list, Student* newStud) {
	newStud->next = list->head;/*new stue next pointer to head*/
	list->head = newStud;/*head pointer to new stud*/
}

void addAfterStud(Student* newStud, Student* prevStud) {
	newStud->next = prevStud->next;/*newStud -> next pointer to next of prevstud*/
	prevStud->next = newStud;/*prevstud next pointer to new stud*/
}

void AddStudToSortedList(List* list, Student* newStud) {
	if (newStud != NULL) {/*If new studer is NULL go out*/
		Student* stud = list->head, * prevStud = NULL;/*head the list of student*/
		if (stud == NULL || (strcmp(stud->secondName, newStud->secondName) >= 0))/*If list is empty or need to be befor the head.*/
			addToHead(list, newStud);
		else {
			prevStud = stud;
			stud = stud->next;
			while (stud) {
				if (strcmp(stud->secondName, newStud->secondName) >= 0) {
					addAfterStud(newStud, prevStud);/*add befor stud*/
					break;
				}
				prevStud = stud;
				stud = stud->next;
			}
			if (stud == NULL) {/*If need to be in the tail*/
				addAfterStud(newStud, prevStud);/*add after prevStud, here stud is NULL*/
			}
		}
	}
}

void removeFromList(List* list, char* query) {
	Student* stud = list->head, * prevStud = NULL;/*head the list of students*/

	char* IDstud;/**/
	int index = 0;/*index of student to remove*/
	IDstud = getField(&query);/*get ID from query*/

	if (!strcmp(stud->ID, IDstud)) {/*If this is the head.*/
		removeFromHead(list);
	}
	prevStud = stud;
	stud = stud->next;
	while (stud) {
		if (!strcmp(stud->ID, IDstud)) {
			removeStud(prevStud, stud);
			freeStud(stud);
			break;
		}
		prevStud = stud;
		stud = stud->next;
	}

	if (stud == NULL)/*If this ID does not exist in list.*/
		printf("This ID \"%s\" does not exist in the system\n", IDstud);

}

Student* removeFromHead(List* list) {
	Student* stud = list->head;
	list->head = stud->next;
	return stud;
}

void removeStud(Student* prevsStud, Student* stud) {
	prevsStud->next = stud->next;
}

Student* creatStud(char* fN, char* sN, char* ID, int typeCourse, char* mark) {
	Student* stud = NULL;
	stud = (Student*)calloc(1, sizeof(Student));
	if (stud == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}

	stud->firstName = _strdup(fN);
	if (stud->firstName == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	stud->validFirstName = checkIfValidName(stud->firstName);// update if vliad or invalid  (0:valid, 1: invalid)

	stud->secondName = _strdup(sN);
	if (stud->secondName == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	stud->validSecondName = checkIfValidName(stud->secondName);// update if vliad or invalid  (0:valid, 1: invalid)

	stud->ID = _strdup(ID);
	if (stud->ID == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	stud->valid_ID = checkIfValidID(stud->ID);// update if vliad or invalid  (0:valid, 1: invalid)

	for (int i = 0; i < NUM_OF_COURSES; i++) {// update all marks to no grade.
		stud->validMark[i] = -1;
		stud->marks[i] = -1;
	}

	stud->validMark[typeCourse] = validMark(mark);/*update valid mark*/
	if (stud->validMark[typeCourse] == 0) {/*if valid mark*/
		stud->marks[typeCourse] = atoi(mark);/*update mark*/
		stud->avg = (float)stud->marks[typeCourse];
	}
	else {/*if invalid mark*/
		stud->marks[typeCourse] = stud->validMark[typeCourse];
		stud->avg = 0;
	}


	return stud;

}

void freeStud(Student* stud) {
	free(stud->firstName);
	free(stud->secondName);
	free(stud->ID);
	free(stud);
}

void freeList(List* list) {
	Student* stud = list->head, * prevStud;
	while (stud) {/*run all the list*/
		prevStud = stud;
		stud = stud->next;
		freeStud(prevStud);
	}
	free(list);
}

void updateStud(List* list, Student* newStd, int index) {
	Student* updateStud = list->head, * prevStud = NULL;/*pointer to student and prev*/

	for (int i = 0; i < index; i++) {/*go to student by index*/
		prevStud = updateStud;
		updateStud = updateStud->next;
	}

	for (int i = 0; i < NUM_OF_COURSES; i++) {
		if (newStd->marks[i] > -1) {/*update all valid marks*/
			updateStud->marks[i] = newStd->marks[i];
			updateStud->validMark[i] = newStd->validMark[i];
		}
	}
	updateAvg(updateStud);

	if (strcmp(updateStud->secondName, newStd->secondName)) {/*check if same ID*/
		copyDynamicStr(&updateStud->secondName, newStd->secondName);/*update second name*/
		updateStud->validSecondName = 0;
		if (index == 0) {/*If this is head the list*/
			removeFromHead(list);
		}
		else {/*If this isn't head the list*/
			removeStud(prevStud, updateStud);
		}
		AddStudToSortedList(list, updateStud);/*Add an updated student to the list*/
	}
	freeStud(newStd);
}

void updateAvg(Student* stud) {
	int numOfTests = NUM_OF_COURSES, sumMarks = 0;
	for (int i = 0; i < 3; i++) {
		if (stud->marks[i] > -1)
			sumMarks += stud->marks[i];
		else
			numOfTests--;

	}
	if (numOfTests > 0)
		stud->avg = (float)(sumMarks) / numOfTests;
}

char* updateID() {
	char* newID = NULL;
	newID = getDinamicStrFromUserOrFile(stdin);
	if (!strcmp(newID, "1")) return NULL;
	while (checkIfValidID(newID)) {
		printf("%s\" is invalid ID please enter new ID\n-->", newID);
		free(newID);
		newID = getDinamicStrFromUserOrFile(stdin);
		if (!strcmp(newID, "1")) return NULL;
	}
	return newID;
}

int getIndexOfStudent(Student* studUser, List* list) {
	if (list->head == NULL) return -1;
	int i = -1;
	Student* prevStud = NULL;

	prevStud = list->head;
	Student* stud = list->head;
	while (prevStud->next) {
		i++;
		if (!strcmp(prevStud->next->ID, studUser->ID)) {
			if (strcmp(prevStud->next->firstName, studUser->firstName))
				if (studUser->validFirstName == 0)
					studUser->validFirstName = 2;//if change first name.
			return i + 1;
		}
		prevStud = prevStud->next;
	}
	return -1;
}

Student* getStudByIndex(int index, List* list) {
	Student* stud = list->head;
	for (int i = 0; i <= index - 1; i++) {
		stud = stud->next;
	}
	return stud;
}

Student* creatStudFromFile(char* line) {
	char* firstName, * secondName, * ID, * course, * mark;
	int typeCourse = -1;/*To get the course name of student*/
	firstName = strtok(line, ",");
	secondName = strtok(NULL, ",");
	ID = strtok(NULL, ",");
	course = strtok(NULL, ",");
	if ((typeCourse = getTypeCorse(course)) == -1) {/*If the course name does not exist*/
		printf("\"%s\" this is course does not exist\n", course);
		return 0;
	}
	mark = strtok(NULL, ",");
	return creatStud(firstName, secondName, ID, typeCourse, mark);
}

int fromFileToList(char** fileName, List* list) {
	Student* newStd = NULL;/*To creat new student*/
	FILE* pFile = NULL;/*To open file*/
	char* lineFromFile = NULL;/*To read line from file*/
	int indexOfStud = -1;/*To check if this student already exist*/
	char ch;/*To read one char from file to check if arived to eof.*/
	int flag = 0; /*To know if need to free lineTromFile*/

	pFile = openFile(fileName, in);
	if (pFile == NULL) return 0; /*If the user entered 1 or alloction fieled.*/

	//Reading from the file and creating list of studnets.
	while (fscanf(pFile, "%c", &ch) > 0) {/*Reading one character and check if didn't arive to eof*/
		fseek(pFile, -1, SEEK_CUR);/*Return one character to back*/
		lineFromFile = getDinamicStrFromUserOrFile(pFile);// Reading one line from the file.
		if (lineFromFile == NULL) break; /*If memory allocation failed*/
		flag = 1;
		toLowerStr(lineFromFile);/*Updateing all uppercase letters to lowercase*/
		newStd = creatStudFromFile(lineFromFile);// creating struct of student.
		if (newStd == NULL) continue; /*If alloction fieled or incorrect field continue to next line*/
		if (list->head)/*If the list isn't empty.*/
			indexOfStud = getIndexOfStudent(newStd, list);
		if (indexOfStud > -1) {/*If this student isn't in the list*/
			updateStud(list, newStd, indexOfStud);
		}
		else {
			updateAvg(newStd);
			//sortStud(list, newStd);
			AddStudToSortedList(list, newStd);/*Adding a student to the list in a sorted form*/
		}
		free(lineFromFile);
		flag = 0;
	}
	if (flag)/*If was break*/
		free(lineFromFile);
	fclose(pFile);
	return 1;
}