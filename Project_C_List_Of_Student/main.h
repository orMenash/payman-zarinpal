#pragma once
#ifndef MAIN
#define MAIN
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

#define CHUNCK 100
typedef char Bool;/*To retunr bool from functions.*/

enum fileTypes {
	in, out
};
enum field {
	_first_name, _second_name, _ID, _c_lang, _computer_networks, _cs_fundamentals, _average
};
enum types {
	_char = 1, _int, _float
};

#endif // !main

