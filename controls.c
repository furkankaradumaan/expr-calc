#include <stdio.h>
#include "controls.h"
#include "calculations.h"
#include <math.h>
#include <string.h>

#define NFUNCS	27

struct Function functions[NFUNCS] = 
{
	{"+", 2, 3, .doubleOperand = sum},
	{"-", 2, 3, .doubleOperand = sub},
	{"*", 2, 2, .doubleOperand = mul},
	{"/", 2, 2, .doubleOperand = div},
	{"%", 2, 2, .doubleOperand = mod},
	{"^", 2, 2, .doubleOperand = power},
	{"sqrt", 1, 1, .singleOperand = sqrt},
	{"cbrt", 1, 1, .singleOperand = cbrt},
	{"sin", 1, 1, .singleOperand = sin},
	{"cos", 1, 1, .singleOperand = cos},
	{"tan", 1, 1, .singleOperand = tan},
	{"cot", 1, 1, .singleOperand = cot}, // cot fonksiyonunu yaz.
	{"sec", 1, 1, .singleOperand = sec}, // sec fonksiyonunu yaz.
	{"cosec", 1, 1, .singleOperand = cosec},  // cosec fonksiyonunu yaz.
	{"floor", 1, 1, .singleOperand = floor},
	{"exp", 1, 1, .singleOperand = exp},
	{"log", 1, 1, .singleOperand = log10},
	{"ln", 1, 1, .singleOperand = log},
	{"asin", 1, 1, .singleOperand = asin},
	{"atan", 1, 1, .singleOperand = atan},
	{"acos", 1, 1, .singleOperand = acos},
	{"!", 1, 1, .singleOperand = fact},
	{"abs", 1, 1, .singleOperand = fabs},
	{"fib", 1, 1, .singleOperand = fib},
	{"min", 2, 1, .doubleOperand = fmin},
	{"max", 2, 1, .doubleOperand = fmax},
	{"hypt", 2, 1, .doubleOperand = hypot}
};

int getClass(char *op)
{
	for(int i = 0; i < NFUNCS; ++i)
		if(strcmp(functions[i].op, op) == 0)
			return functions[i].priority;

	return -1; // Fonksiyon bulunamadı.
}

int getParameters(char *op)
{
	for(int i = 0; i < NFUNCS; ++i)
		if(strcmp(functions[i].op, op) == 0)
			return functions[i].params;
	
	return -1;
}

doubleOpFunc getDoubleOperandFunction(char *op)
{
	for(int i = 0; i < NFUNCS; ++i)
		if(strcmp(functions[i].op, op) == 0 && functions[i].params == 2)
			return functions[i].doubleOperand; // Fonksiyonu dön.
	
	return NULL;
}

singleOpFunc getSingleOperandFunction(char *op)
{
	for(int i = 0; i < NFUNCS; ++i)
		if(strcmp(functions[i].op, op) == 0 && functions[i].params == 1)
			return functions[i].singleOperand;

	return NULL;
}

