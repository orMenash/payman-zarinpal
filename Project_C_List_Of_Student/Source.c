#include "header.h"


//Opening file ,reading from file and creating list of student.
int fromFileToList(char** fileName, List* list) {
	Student* newStd = NULL;/*To creat new student*/
	FILE* pFile = NULL;/*To open file*/
	char* lineFromFile = NULL;/*To read line from file*/
	int indexOfStud = -1;/*To check if this student already exist*/
	char ch;/*To read one char from file to check if arived to eof.*/
	int flag = 0; /*To know if need to free lineTromFile*/

	pFile = openFile(fileName, "in");
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

//Opening the file and if can't to open, asking from user new fileName.
FILE* openFile(char** fileName, char* type) {
	FILE* pFile = NULL;
	while (pFile == NULL) {/*Check if fileName and pFile are not NULL*/
		if (!strcmp(type, "in"))
			pFile = fopen(*fileName, "r+t");
		else
			pFile = fopen(*fileName, "wt");
		if ((*fileName) == NULL || pFile == NULL) {
			errorMessge("Failed to open the file, please enter a different file name or 1 to continu without file.\n");
			//Geting a new file name from the user.
			free(*fileName);
			if ((*fileName = getDinamicStrFromUserOrFile(stdin)) == NULL) return 0;/*If memory allocation failed 5 times return 0*/
			if (!strcmp(*fileName, "1")) {/*If the user entered 1 return 0*/
				return 0;
			}
		}
	}
	return pFile;
}

// Receives a query from the user and sends to the appropriate function.
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

//select action -> get field, condition and value frome a query and check all students in the list.
void select(char* query, Student* head) {
	Student* stud = head;
	Bool(*cb)(void*, void*);/*pointer to function */
	Bool(*validDataUser)(char*);
	char* fieldUser = NULL, * condUser = NULL, * dataUser = NULL;
	int locInStruct, fieldUserType, condUserType;
	do {
		fieldUser = getField(&query);/*geting field of uaser from the query.*/
		fieldUserType = getFieldType(fieldUser, &locInStruct, &validDataUser);/*return type of field and update locInStruct and validDataUser fields types -> {1: char}, {2 : int} {3 : float}*/
		if (fieldUserType == 0) GO_TO; // If the field is invalid.
		condUser = getCondition(&query);
		condUserType = getConditionType(condUser);/*conditions types -> {1 : = }, {2 : != }, {3 : >}, {4 : <}*/
		if (condUserType == 0) GO_TO;// If a condition is invalid.
		dataUser = getField(&query);
		cb = (Bool(*)(void*, void*)) getFunction(fieldUserType, condUserType);/*get a spcific function*/
		genericCmpFunc(stud, cb, locInStruct, dataUser);/*send to specific function to check all student in the list whis user condition*/
	} while (0);
	free(fieldUser);
	free(condUser);
	free(dataUser);
}

char* freeF(char* str) {
	free(str);
	return NULL;
}



void set(char* query, List* list, char* fielName) {
	ARRAY_OF_NAME_COURSES/*creatin array of course names*/
		Student* stud = NULL, * oldStud = NULL;/*stud to creat new student , old stud to update student*/
	//stud = (student*)calloc(1, sizeof(student));
	char* first_name = NULL, * second_name = NULL, * ID = NULL, * courseName = NULL, * mark = NULL;
	int  typeCours = -1, oldIndex, newIndex;/*i - index of course*/
	char* prevStud = NULL;
	int flagFreeStud = 0;


	do {
		if (first_name = getFieldSet(&query)) {/*if valid field*/
			if (validFiedl(first_name, "first name")) {/*if valid field value*/
				first_name = freeF(first_name);
				if ((first_name = valueFieldUser(&query)) == NULL) {
					printf(" (in filed first name)\n");
					GO_TO;
				}
			}
			else GO_TO;
		}
		else {/*if invalid field*/
			printf("need to be \"first name\"");
			GO_TO;
		}

		if (second_name = getFieldSet(&query)) {
			if (validFiedl(second_name, "second name")) {/*if valid field*/
				second_name = freeF(second_name);
				if ((second_name = valueFieldUser(&query)) == NULL) {
					printf(" (in filed second name)\n");
					GO_TO;
				}
			}
			else GO_TO;
		}
		else {/*if invalid field*/
			printf("need to be \"second name\"");
			GO_TO;
		}

		if (ID = getFieldSet(&query)) {
			if (validFiedl(ID, "id")) {/*if valid field*/
				ID = freeF(ID);
				if ((ID = valueFieldUser(&query)) == NULL) {
					printf(" (in filed ID)\n");
					GO_TO;
				}
			}
			else GO_TO;/*invalid field*/
		}
		else {/*if invalid field*/
			printf("need to be \"ID\"");
			GO_TO;
		}

		if (courseName = getFieldSet(&query)) {
			for (int i = 0; i < NUM_OF_COURSES; i++) {
				if (!strcmp(courseName, arrNameCourses[i])) {/*if valid course name check in the array of course names.*/
					courseName = freeF(courseName);
					courseName = _strdup(arrNameCourses[i]);
					typeCours = i;
					break;
				}
			}

		}
		else GO_TO; /*if courseName from query(line 148) == NULL */

		if (courseName == NULL || *courseName ==  - 1) {/*if invalid courseName */
			printf("\"%s\" is invalid course name!\n", courseName);
			GO_TO;
		}
		else
			if ((mark = valueFieldUser(&query)) == NULL) {
				printf(" (in filed \"%s\")\n", courseName);
				GO_TO;
			}

		stud = creatStud(first_name, second_name, ID, typeCours, mark);
		if (stud == NULL) GO_TO;

		oldIndex = getIndexOfStudent(stud, list);
		
		if (stud->validSecondName == 1) {/*if invalid second name*/
			printf("\"%s\" is invalid second name!\n", stud->secondName);
			freeStud(stud);
			flagFreeStud = 0;
			GO_TO;
		}
		if (typeCours >= 0)/*Make sure not to reach invalid values in the array*/
			if (stud->validMark[typeCours] != 0) {/*if invalid mark*/
				printf("\"%s\" is invalid mark!\n", mark);
				freeStud(stud);
				flagFreeStud = 0;
				GO_TO;
			}

		if (oldIndex == -1) {/*if this student dose not exist in the list.*/
			if (stud->validFirstName == 1) {/*if invalid first name*/
				printf("\"%s\" is invalid first name!\n", stud->firstName);
				freeStud(stud);
				flagFreeStud = 0;
				GO_TO;
			}
			if (stud->valid_ID == 1) {/*if invalid ID*/
				printf("\"%s\" is invalid ID!\n", stud->ID);
				freeStud(stud);
				flagFreeStud = 0;
				GO_TO;
			}
			AddStudToSortedList(list, stud);/*Add to list*/
			printf("Set completed successfully!\n");
			flagFreeStud = 0;
			GO_TO;
		}
		else {/*if this student exist in the list*/

			oldStud = getStud(oldIndex, list);/*get student from list by index.*/
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
				GO_TO;
			}
			else if (stud->validFirstName == 2) {// change first name.
				printf("You can not change a first name!\n");
				freeStud(stud);
				flagFreeStud = 0;
				GO_TO;
			}
			if (stud->valid_ID == 1) {/*if invalid ID the user can to change.*/
				printf("you can chang your invalid ID to new valid ID OR press 1 to continu with this ID:\n-->");
				do {
					stud->ID = updateID();
					if (stud->ID == NULL) GO_TO; /*alloction filed or user entered one*/
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
	} while (0);


	free(first_name);
	free(second_name);
	free(ID);
	free(mark);
	free(courseName);
	if (flagFreeStud)
		free(stud);
}

//creating new file with all information sorted from list  
void saveTOfile(List* list, char* fileName) {
	ARRAY_OF_NAME_COURSES
		FILE* pFile;
	Student* stud = list->head;
	pFile = openFile(&fileName, "out");
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

// Update uppercase to lowercase
char toLowerCh(char ch) {
	if (ch >= 'A' && ch <= 'Z')/*If uppercase*/
		ch += 32; /*Update to lowercase*/
	return ch;
}

//Update string all uppercase to lowercase letters.
void toLowerStr(char* str) {
	int i = 0;
	while (str[i]) {/*Run all the string.*/
		str[i] = toLowerCh(str[i]);
		i++;
	}
}

//get puery and return only the field to check.
char* getField(char** query) {
	char* saveQuery = NULL, * field = NULL;
	unsigned int count = 0;
	while (**query == ' ') (*query)++;/*Skipping spaces*/
	while ((**query) != '=' && (**query) != '!' && (**query) != '<' && (**query) != '>' && (**query) != '\0') {/*counter of characters until condition*/
		count++;
		(*query)++;
	}
	saveQuery = (*query);/*save to stay query pointer in this place */
	while (*(saveQuery - 1) == ' ') {/*Skipping spaces*/
		count--;
		saveQuery--;
	}
	field = (char*)malloc((count + 1) * (sizeof(char)));
	if (field == NULL) return (char*)errorMessge("Memory allocation failed!\n");
	field[count] = '\0';
	memcpy(field, saveQuery - count, count);
	return field;
}




Student* creatStud(char* fN, char* sN, char* ID, int typeCourse, char* mark) {
	Student* stud = NULL;
	stud = (Student*)calloc(1, sizeof(Student));
	if (stud == NULL) return errorMessge("Aloction filed!");

	stud->firstName = _strdup(fN);
	if (stud->firstName == NULL) return errorMessge("Aloction filed!");
	stud->validFirstName = checkIfValidName(stud->firstName);// update if vliad or invalid  (0:valid, 1: invalid)

	stud->secondName = _strdup(sN);
	if (stud->secondName == NULL) return errorMessge("Aloction filed!");
	stud->validSecondName = checkIfValidName(stud->secondName);// update if vliad or invalid  (0:valid, 1: invalid)

	stud->ID = _strdup(ID);
	if (stud->ID == NULL) return errorMessge("Aloction filed!");
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
		changeField(&updateStud->secondName, newStd->secondName);/*update second name*/
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

int changeField(char** studField, char* newStudField) {
	char* tempField = NULL; /* to save the old data field (if alloction filed). */
	tempField = _strdup(*studField); /* copy the old data field. */
	if (tempField == NULL) {
		return *(int*)errorMessge("Memory allocation failed!\n");
	}
	free(*studField);
	*studField = _strdup(newStudField);
	if (*studField == NULL) {
		*studField = tempField;
		return *(int*)errorMessge("Memory allocation failed!\n");
	}
	free(tempField);
	return 1;
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
	if (condition == NULL)  return errorMessge("Memory allocation failed!\n");
	memcpy(condition, (*query) - count, count);
	return condition;
}
int getTypeCorse(char* cours) {
	ARRAY_OF_NAME_COURSES
		for (int i = 0; i < NUM_OF_COURSES; i++) {
			if (!strcmp(cours, arrNameCourses[i]))
				return i;
		}
	return -1;
}
int getFieldType(char* fieldUser, int* localFilesInStruct, Bool(**validDataUser)(char*)) {
	if (fieldUser == NULL) return 0;
	CREATE_FIELDS_ARR
		//{1: char}, {2 : int} {3 : float}
		for (int i = 0; i < 14; i += 2) {
			if (!strcmp(fieldsArr[i], fieldUser)) {
				switch (i)
				{
				case 0:// first name.
					*localFilesInStruct = OFFSETOF(struct student, firstName);
					*validDataUser = checkIfValidName;
					break;
				case 2:// second name.
					*localFilesInStruct = OFFSETOF(struct student, secondName);
					*validDataUser = checkIfValidName;
					break;
				case 4:// ID.
					*localFilesInStruct = OFFSETOF(struct student, ID);
					*validDataUser = checkIfValidID;
					break;
				case 6:// c lang.
					*localFilesInStruct = OFFSETOF(struct student, marks);
					*validDataUser = validMark;
					break;
				case 8:// computer networks.
					*localFilesInStruct = OFFSETOF(struct student, marks) + 4;
					*validDataUser = validMark;
					break;
				case 10:// cs fundamentals.
					*localFilesInStruct = OFFSETOF(struct student, marks) + 8;
					*validDataUser = validMark;
					break;
				case 12:// average.
					*localFilesInStruct = OFFSETOF(struct student, avg);
					*validDataUser = validAvg;
					break;
				}
				if (!strcmp(fieldsArr[i + 1], "char")) return 1;
				else if (!strcmp(fieldsArr[i + 1], "int")) return 2;
				else if (!strcmp(fieldsArr[i + 1], "float")) return 3;
			}
		}
	printf("\"%s\" is a field invalid!\n", fieldUser);


	return 0;
}

int getConditionType(char* condUser) {
	if (condUser == NULL) return 0;
	CREATE_CONDITION_ARR
		// {1 : =}, {2 : !=}, {3 : >}, {4 : <}
		for (int i = 0; i < 4; i++) {
			if (!strcmp(condArr[i], condUser))
				return i + 1;
		}
	printf("\"%s\" is an improper condition!\n", condUser);
	return 0;
}


char* getDinamicStrFromUserOrFile(FILE* type1) {
	//                      save pointer to realloc    pointer to copy
	char* newDinamicStr = NULL, * saveNewDin = NULL, * desNewDinStr = NULL;
	unsigned int flag = 1, loop = 1, len = 0, prevLen = 0, lenChunkUser = 0;
	static int attempts = 4;
	char chunkUser[10];
	while (flag) {
		fgets(chunkUser, 10, type1);/* get chunk string from user.*/
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
				return getDinamicStrFromUserOrFile(type1);
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
				return getDinamicStrFromUserOrFile(type1);
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
void* getFunction(char fieldUserType, char condUserType) {
	switch (fieldUserType)
	{
	case 1:// char
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
	case 2:// int
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
	case 3:// float
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
	if (action == NULL) errorMessge("Memory allocation failed!\n");
	else memcpy(action, (*str) - count, count);
	return action;
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
	if (field == NULL) return (char*)errorMessge("aloction filde!\n");
	(field)[count] = '\0';
	memcpy(field, (*query) - count, count);
	*query = saveQuery;
	if (**query == ',') (*query)++;// Skip the character ','.
	return field;
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
	if (field == NULL) return (char*)errorMessge("aloction filde!\n");
	field[count] = '\0';
	memcpy(field, saveQuery - count, count);
	return field; // if query valid there is char '='
}
Student* getStud(int index, List* list) {
	Student* stud = list->head;
	for (int i = 0; i <= index - 1; i++) {
		stud = stud->next;
	}
	return stud;
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
void  genericCmpFunc(Student* head, Bool(*cb)(void*, void*), int localFilesInStruct, void* dataUser) {
	Student* stud = head;
	int num = 0;
	while (stud) {/* runing on all the student list. */
		void* pDataStud = (void*)(((char*)stud) + localFilesInStruct);/* updateing the address of this field in this student struct. */
		if (cb(dataUser, pDataStud)) {/* check the condtion in this student(in this field).*/
			if (num == 0) {
				printTitle();
				num++;
			}
			printStudentToConsole(stud, num);
			num++;
		}
		stud = stud->next;
	}
	if (num == 0)
		printf("There are no students who meet the criteria!\n");
}