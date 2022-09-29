#include "header.h"

void addToHead(List* list, Student* newStud) {
	newStud->next = list->head;/*new stue next pointer to head*/
	list->head = newStud;/*head pointer to new stud*/
}

void addAfterStud(Student* newStud, Student* prevStud) {
	newStud->next = prevStud->next;/*new stud next pointer to next of prevstud*/
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
