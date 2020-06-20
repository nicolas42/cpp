#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Parse words by noting down the starting positions of words 
// and changing spaces to null characters

double get_time(void);

typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

string string_make(size_t n);
void string_free(string f);
void string_maybe_grow(string* f);
string string_copy(string a);

string read_file(char *filename);

typedef struct strings {
	size_t length;
	size_t allocated;
	char** data;
} strings;

strings strings_init(void);
strings strings_make(size_t length);
void strings_free(strings f);
void strings_maybe_grow(strings* f);
void strings_add(strings* f, char* a);

// strings string_split_destructive(char* a char* split_chars);
strings string_split_destructive(char* a, char* split_chars);
void demo_split_destructive(void);
double min(double a, double b);
int split_main(int argc, char** argv);

#endif
