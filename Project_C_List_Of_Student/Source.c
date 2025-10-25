#include "source.h"
#include "generalFunctions.h"


char* valueFieldUser(char** query) {
	unsigned int count = 0;/* counter of character. */
	char* field;           /*field to return.*/
	char* saveQuery = NULL;
	(*query)++;           /*Skip the character '='.*/
	while (**query == ' ') (*query)++; /*Skipping spaces*/
	while (**query != ',' && **query != '\0') { /*counter the character of field until the  ',' or \0. */
		count++;
		(*query)++;
	}
	saveQuery = (*query);
	while (*(*query - 1) == ' ' && count > 0) { /*lowering spaces*/
		count--;
		(*query)--;
	}
	if (count == 0) { /* if the user not entered data. */
		printf("The value of user is empty! ");
		return NULL;
	}
	field = (char*)malloc((count + 1) * sizeof(char));
	if (field == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	(field)[count] = '\0';
	memcpy(field, (*query) - count, count);
	*query = saveQuery;
	if (**query == ',') (*query)++;// Skip the character ','.
	return field;
}

void set(char* query, List* list, char* fielName) {
	char* arrNameCourses[] = ARRAY_OF_NAME_COURSES;/*creatin array of course names*/
	Student* stud = NULL, * oldStud = NULL;/*stud to creat new student , old stud to update student*/
	char* first_name = NULL, * second_name = NULL, * ID = NULL, * courseName = NULL, * mark = NULL;
	int  typeCours = -1, oldIndex, newIndex;/*i - index of course*/
	char* prevStud = NULL;
	int flagFreeStud = 0;

	if ((first_name = getFieldOfSet(&query, "first name")) == NULL) goto here;

	if ((second_name = getFieldOfSet(&query, "second name")) == NULL) goto here;

	if ((ID = getFieldOfSet(&query, "id")) == NULL) goto here;

	if (courseName = getFieldSet(&query)) {
		for (int i = 0; i < NUM_OF_COURSES; i++) {
			if (!strcmp(courseName, arrNameCourses[i])) {/*if valid course name. (checking in the array of course names).*/
				free(courseName);
				courseName = NULL;
				courseName = _strdup(arrNameCourses[i]);
				typeCours = i;
				break;
			}
		}
	}
	else goto here; /*if courseName from query == NULL */

	if (courseName == NULL || typeCours == -1) {/*if invalid courseName */
		printf("\"%s\" is invalid course name!\n", courseName);
		goto here;
	}
	else
		if ((mark = valueFieldUser(&query)) == NULL) {
			printf(" (in filed \"%s\")\n", courseName);
			goto here;
		}

	stud = creatStud(first_name, second_name, ID, typeCours, mark);
	if (stud == NULL) goto here;

	oldIndex = getIndexOfStudent(stud, list);

	if (stud->validSecondName == 1) {/*if invalid second name*/
		printf("\"%s\" is invalid second name!\n", stud->secondName);
		freeStud(stud);
		flagFreeStud = 0;
		goto here;
	}
	if (typeCours >= 0)/*Make sure not to reach invalid values in the array*/
		if (stud->validMark[typeCours] != 0) {/*if invalid mark*/
			printf("\"%s\" is invalid mark!\n", mark);
			freeStud(stud);
			flagFreeStud = 0;
			goto here;
		}

	if (oldIndex == -1) {/*if this student dose not exist in the list.*/
		if (stud->validFirstName == 1) {/*if invalid first name*/
			printf("\"%s\" is invalid first name!\n", stud->firstName);
			freeStud(stud);
			flagFreeStud = 0;
			goto here;
		}
		if (stud->valid_ID == 1) {/*if invalid ID*/
			printf("\"%s\" is invalid ID!\n", stud->ID);
			freeStud(stud);
			flagFreeStud = 0;
			goto here;
		}
		AddStudToSortedList(list, stud);/*Add to list*/
		printf("Set completed successfully!\n");
		flagFreeStud = 0;
		goto here;
	}
	else {/*if this student exist in the list*/

		oldStud = getStudByIndex(oldIndex, list);/*get student from list by index.*/
		if (oldStud->validFirstName == 1) {/*if invalid first name the user can to change.*/
			printf("you can chang your invalid first name to new valid first name OR press 1 to continu with this first name:\n-->");
			stud->firstName = getNewName();
			if (stud->firstName != NULL) {/*alloction filed or user entered one*/
				free(oldStud->firstName);
				oldStud->firstName = _strdup(stud->firstName);
				oldStud->validFirstName = 0;
			}
		}
		else if (stud->validFirstName == 1) {/*if invalid first name*/
			printf("\"%s\" is invalid first name!\n", stud->firstName);
			freeStud(stud);
			flagFreeStud = 0;
			goto here;
		}
		else if (stud->validFirstName == 2) {// change first name.
			printf("You can not change a first name!\n");
			freeStud(stud);
			flagFreeStud = 0;
			goto here;
		}
		if (stud->valid_ID == 1) {/*if invalid ID the user can to change.*/
			printf("you can chang your invalid ID to new valid ID OR press 1 to continu with this ID:\n-->");
			do {
				stud->ID = updateID();
				if (stud->ID == NULL) goto here; /*alloction filed or user entered one*/
				newIndex = getIndexOfStudent(stud, list);
				if (newIndex > -1) printf("The ID \"%s\" already exists in the system, please enter a new one.", stud->ID);
			} while (newIndex > -1);
			if (stud->ID != NULL) {
				free(oldStud->ID);
				oldStud->ID = _strdup(stud->ID);
				oldStud->valid_ID = 0;
			}
		}

		updateStud(list, stud, oldIndex);/*and free stud*/
		flagFreeStud = 0;

	}
	printf("Set completed successfully!\n");

here:// from goto if the query failed.

	free(first_name);
	free(second_name);
	free(ID);
	free(mark);
	free(courseName);
	if (flagFreeStud)
		free(stud);
}

void select(char* query, Student* head) {
	Student* stud = head;
	Bool(*cb)(void*, void*);/*pointer to function */
	Bool(*validDataUser[2])(char*) = { validMark, validAvg };
	char* fieldUser = NULL, * condUser = NULL, * dataUser = NULL;
	int locInStruct, fieldUserType, condUserType;

	fieldUser = getField(&query);/*geting field of uaser from the query.*/
	fieldUserType = getFieldType(fieldUser, &locInStruct);/*return type of field and update locInStruct and validDataUser fields types -> {1: char}, {2 : int} {3 : float}*/
	if (fieldUserType == 0) goto here; // If the field is invalid.
	condUser = getCondition(&query);
	condUserType = getConditionType(condUser);/*conditions types -> {1 : = }, {2 : != }, {3 : >}, {4 : <}*/
	if (condUserType == 0) goto here; // If a condition is invalid.
	dataUser = getField(&query);
	if (dataUser == NULL) goto here;// If The user has not entered enough data. 
	if (fieldUserType == 2 || fieldUserType == 3) {
		if (validDataUser[fieldUserType - 2](dataUser) != 0) {
			switch (fieldUserType)
			{
			case 2:
				printf("\"%s\" is invalid mark!\n", dataUser);
				goto here;
			case 3:
				printf("\"%s\" is invalid average!\n", dataUser);
				goto here;
			}

		}
	}
	cb = (Bool(*)(void*, void*)) getFunction(fieldUserType, condUserType);/*get a spcific function*/
	genericCmpFunc(stud, cb, locInStruct, dataUser);/*send to specific function to check all student in the list whis user condition*/
here:

	free(fieldUser);
	free(condUser);
	free(dataUser);
}

void saveTOfile(List* list, char* fileName) {
	char* arrNameCourses[] = ARRAY_OF_NAME_COURSES;
	FILE* pFile;
	Student* stud = list->head;
	pFile = openFile(&fileName, out);
	if (pFile != NULL) { /*If the user entered 1 or alloction fieled.*/
		while (stud) {
			for (int i = 0; i < NUM_OF_COURSES; i++) {
				if (stud->marks[i] > -1 || stud->marks[i] == -2)
					fprintf(pFile, "%s,%s,%s,%s,%d\n", stud->firstName, stud->secondName, stud->ID, arrNameCourses[i], stud->marks[i]);
			}
			stud = stud->next;
		}
		fclose(pFile);
	}
	printf("The changes have been saved!\n");
}

void getQuery(List* list, char* fileName) {
	char* query, * saveQuery, * action;
	printIntroduction();
	while (1) {
		printf("\n\n---> ");
		if ((query = getDinamicStrFromUserOrFile(stdin)) == NULL) break;/*Receives a query from the user and check if return null*/
		printf("\n\n");
		saveQuery = query;/*Save pointer of query to free*/
		toLowerStr(query);
		action = getAction(&query);
		if (action == NULL) continue;
		if (!strcmp(action, "select")) // If the user did enter "select".
			select(query, list->head);
		else if (!strcmp(action, "set")) // If the user did enter "set".
			//set(query, list, fileName);
			set(query, list, fileName);
		else if (!strcmp(action, "print")) //If the user did enter "prnit".
			printListToConsole(list);
		else if (!strcmp(action, "remove")) {//If the user did enter "quit".
			removeFromList(list, query);
		}
		else if (!strcmp(action, "quit")) {//If the user did enter "quit".
			free(saveQuery);
			free(action);
			break;
		}
		else printf("\"%s\" is an incorrect action.!\n", action);
		free(action);
		free(saveQuery);
	}
}

char* getFieldOfSet(char** query, char* fieldUser) {
	char* field;
	if (field = getFieldSet(query)) {/*If the query is invalid*/
		if (validFiedl(field, fieldUser)) {/*if valid field*/
			free(field);
			field = NULL;
			if ((field = valueFieldUser(query)) == NULL) {/*if valid value field */
				printf(" (in filed %s)\n", fieldUser);
				return NULL;
			}
		}
		else return NULL;
	}
	else {/*if invalid field*/
		printf("need to be \"first name\"");
		return NULL;
	}
	return field;
}

char* getField(char** query) {
	char* saveQuery = NULL, * field = NULL;
	unsigned int count = 0;
	while (**query == ' ') (*query)++;/*Skipping spaces*/
	while ((**query) != '=' && (**query) != '!' && (**query) != '<' && (**query) != '>' && (**query) != '\0') {/*counter of characters until condition*/
		count++;
		(*query)++;
	}
	if (count == 0) {// the user not inserted data.
		printf("The user has not entered enough data!\n");
		return NULL;
	}
	saveQuery = (*query);/*save to stay query pointer in this place */
	while (*(saveQuery - 1) == ' ' && count > 0) {/*Skipping spaces*/
		count--;
		saveQuery--;
	}
	field = (char*)malloc((count + 1) * (sizeof(char)));
	if (field == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return NULL;
	}
	field[count] = '\0';
	memcpy(field, saveQuery - count, count);
	return field;
}

char* getCondition(char** query) {
	int count = 0;
	char* condition = NULL;
	while (**query == ' ') (*query)++;
	while ((**query) == '=' || (**query) == '!' || (**query) == '<' || (**query) == '>') {
		count++;
		(*query)++;
	}
	condition = (char*)calloc((count + 1), (sizeof(char)));
	if (condition == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	memcpy(condition, (*query) - count, count);
	return condition;
}

int getTypeCorse(char* cours) {
	char* arrNameCourses[] = ARRAY_OF_NAME_COURSES;
		for (int i = 0; i < NUM_OF_COURSES; i++) {
			if (!strcmp(cours, arrNameCourses[i]))
				return i;
		}
	return -1;
}

int getFieldType(char* fieldUser, int* localFilesInStruct) {
//	void** validDataUser = NULL;//-----------------------------
	if (fieldUser == NULL) return 0;
	char* fieldsArr[14] = CREATE_FIELDS_ARR;
		//{1: char}, {2 : int} {3 : float}
		for (int i = 0; i < 14; i += 2) {
			if (!strcmp(fieldsArr[i], fieldUser)) {// checking which field the user inserted.
				switch (i / 2)
				{
				case _first_name:// first name.
					*localFilesInStruct = OFFSETOF(struct student, firstName);
					return 1;
				case _second_name:// second name.
					*localFilesInStruct = OFFSETOF(struct student, secondName);
					return 1;
				case _ID:// ID.
					*localFilesInStruct = OFFSETOF(struct student, ID);
					return 1;
				case _c_lang:// c lang.
					*localFilesInStruct = OFFSETOF(struct student, marks);
					return 2;
				case _computer_networks:// computer networks.
					*localFilesInStruct = OFFSETOF(struct student, marks) + 4;
					return 2;
				case _cs_fundamentals:// cs fundamentals.
					*localFilesInStruct = OFFSETOF(struct student, marks) + 8;
					return 2;
				case _average:// average.
					*localFilesInStruct = OFFSETOF(struct student, avg);
					return 3;
				}
			}
		}
	printf("\"%s\" is an invalid field!\n", fieldUser);


	return 0;
}

int getConditionType(char* condUser) {
	if (condUser == NULL) return 0;
	char* condArr[4] = CREATE_CONDITION_ARR;
		// {1 : =}, {2 : !=}, {3 : >}, {4 : <}
		for (int i = 0; i < 4; i++) {
			if (!strcmp(condArr[i], condUser))
				return i + 1;
		}
	printf("\"%s\" is an improper condition!\n", condUser);
	return 0;
}

void* getFunction(char fieldUserType, char condUserType) {
	switch (fieldUserType)
	{
	case _char:// char
		switch (condUserType)
		{
		case 1: // =
			return charCmp;
		case 2: // !=
			return charNotCmp;
		case 3: // >
			return charBig;
		case 4: // <
			return charSmall;
		}
	case _int:// int
		switch (condUserType)
		{
		case 1: // =
			return intCmp;
		case 2: // !=
			return intNotCmp;
		case 3: // >
			return intBig;
		case 4: // <
			return intSmall;
		}
	case _float:// float
		switch (condUserType)
		{
		case 1: // =
			return floatCmp;
		case 2: // !=
			return floatNotCmp;
		case 3: // >
			return floatBig;
		case 4: // <
			return floatSmall;
		}
	}
	return 0;
}

char* getAction(char** str) {
	int count = 0;
	char* action = NULL;
	while (**str == ' ') {
		(*str)++;
	}
	while (**str != '=' && **str != '>' && **str != '<' && **str != '!' && **str != ' ' && **str != '\0') {
		count++;
		(*str)++;
	}
	action = calloc((count + 1), sizeof(char));
	if (action == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	else memcpy(action, (*str) - count, count);
	return action;
}

char* getFieldSet(char** query) {
	char* field;
	unsigned int count = 0;
	char* saveQuery = NULL;
	while (**query == ' ') (*query)++;

	while (**query != '=' /* && **query != '>' && **query != '<' && **query != '!' */ && **query != '\0') {
		count++;
		(*query)++;
	}
	if (**query != '=') {
		printf("The query is invalid! need to be the character '='\n");
		return NULL;
	}
	saveQuery = *query;

	while (*(saveQuery - 1) == ' ') {
		count--;
		saveQuery--;
	}

	field = (char*)malloc((count + 1) * sizeof(char));
	if (field == NULL) {/* Checking if memory allocation was successful.*/
		printf("Memory allocation failed!\n");
		return 0;
	}
	field[count] = '\0';
	memcpy(field, saveQuery - count, count);
	return field; // if query valid there is char '='
}

char* getNewName() {
	char* name = NULL;
	name = getDinamicStrFromUserOrFile(stdin);
	if (!strcmp(name, "1")) return NULL;
	while (checkIfValidName(name)) {
		printf("\"%s\" is invalid name\n-->", name);
		free(name);
		name = getDinamicStrFromUserOrFile(stdin);
		if (!strcmp(name, "1")) return NULL;
	}
	return name;
}