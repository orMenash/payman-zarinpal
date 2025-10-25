#include "cmpFunctoins.h"

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
//--------select_conditions-----------------
Bool intCmp(void* numUser, void* numStud) {
	if ((atoi((char*)numUser) - *(int*)numStud) == 0) return 1;
	return 0;
}
Bool charCmp(void* strUser, void* strStud) {
	if (strcmp((char*)strUser, *(char**)strStud) == 0) return 1;
	return 0;
}
Bool floatCmp(void* numUser, void* numStud) {
	if ((atof((char*)numUser) - *(float*)numStud) == 0) return 1;
	return 0;
}
//--------------- != -------------------
Bool intNotCmp(void* numUser, void* numStud) {
	if ((atoi((char*)numUser) - *(int*)numStud) != 0) return 1;
	return 0;
}
Bool charNotCmp(void* strUser, void* strStud) {
	if (strcmp((char*)strUser, *(char**)strStud) != 0) return 1;
	return 0;
}
Bool floatNotCmp(void* numUser, void* numStud) {
	if ((atof((char*)numUser) - *(float*)numStud) != 0) return 1;
	return 0;
}
//--------------- > -------------------
Bool intBig(void* numUser, void* numStud) {
	if ((*(int*)numStud) - atoi((char*)numUser) > 0) return 1;
	return 0;
}
Bool charBig(void* strUser, void* strStud) {
	if (strcmp(*(char**)strStud, (char*)strUser) > 0) return 1;
	return 0;
}
Bool floatBig(void* numUser, void* numStud) {
	if ((*(float*)numStud) - atof((char*)numUser) > 0) return 1;
	return 0;
}
//--------------- < -------------------
Bool intSmall(void* numUser, void* numStud) {
	if ((*(int*)numStud) - atoi((char*)numUser) < 0) return 1;
	return 0;
}
Bool charSmall(void* strUser, void* strStud) {
	if (strcmp(*(char**)strStud, (char*)strUser) < 0) return 1;
	return 0;
}
Bool floatSmall(void* numUser, void* numStud) {
	if ((*(float*)numStud) - atof((char*)numUser) < 0) return 1;
	return 0;
}

