#include <stdio.h>
#include "supfuncs.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

double cot(double);
double sec(double);
double cosec(double);


int is_parenthesis(char c)
{
	return c == '(' || c == ')' ||
	       c == '[' || c == ']' ||
	       c == '{' || c == '}';
}

/*
 *	Dereceyi radyan cinsine çevir. 
 * */
double degrees_to_radians(double degrees)
{
	return (degrees) * (M_PI / 180);
}

double radians_to_degrees(double radians)
{
	return (radians) * (180 / M_PI);
}

int istakingradians(double (*fptr)(double))
{
	return fptr == sin || fptr == cos || fptr == tan ||
	       fptr == cot || fptr == sec || fptr == cosec;
}

int isgivingradians(double (*fptr)(double))
{
	return fptr == asin || fptr == acos || fptr == atan;
}

int haschar(char *s, char c)
{
	while(*s++ != '\0')
		if(*s == c)
			return 1;

	return 0;
}


char *substr(const char *str, int start, int end) {

    if (start < 0 || end < start || end > strlen(str)) {
        return NULL; // Geçersiz indeksler
    }

    int len = end - start;
    char *sub = malloc(len + 1); // +1 null karakter için
    if (!sub) return NULL; // Bellek yetersizliği kontrolü

    strncpy(sub, str + start, len);
    sub[len] = '\0'; // Null terminator

    return sub;
}

char *getword(char *expr)
{
	char *start;

	// Başta boşluk varsa atla.
	while(isspace(*expr))
		expr++;
	
	start = expr;
	// Alfabetik karakter olduğu sürece geç
	while(isalpha(*expr))
		expr++;

	return substr(start, 0, expr - start);
}

char *chartos(char c)
{
	char *s = (char *)malloc(sizeof(char) * 2);

	s[0] = c;
	s[1] = '\0';

	return s;
}
