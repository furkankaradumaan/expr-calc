#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "controls.h"
#include "supfuncs.h"
#include <math.h>
#include "variables.h"

int rmtokens(struct Token *tokens[], int left, int right)
{
	
	for(int i = left; i < right; ++i)
		free(tokens[i]); // Token'i serbest bırak.
	
	int i = right;
	int j = left;
	do
	{
		tokens[j] = tokens[i];
		tokens[i++] = NULL;
	}while(tokens[j++]->type != END);
	
	return right - left; // Silinen token sayısını döndür.
}

int count_tokens(struct Token *tokens[])
{
	int len;
	for(len = 0; tokens[len]->type != END; ++len);

	return len;
}


struct Token **tokenize(char *expr, struct Token *tokens[], int maxtokens, int *d)
{
	int counter;
	struct Token *lastToken = NULL;
	int depth = 1;
	int maxdepth = 1;

	counter = 0;
	do
	{
		tokens[counter] = getNumber(&expr, &depth); // İlk önce NUMBER tipinde almayı dene. Eğer sıradaki token bir NUMBER deeğilse fonksiyon NULL dönecektir.
		
		if(tokens[counter] == NULL)
			tokens[counter] = getVariable(&expr, &depth);

		if(tokens[counter] == NULL)
			tokens[counter] = getFunction(&expr, &depth); //İkinci olarak fonksiyon olarak almayı dene. Eğer fonksiyon değilse yine NULL dönecek.

		if(tokens[counter] == NULL)
			tokens[counter] = getOperator(&expr, &depth); // Üçüncü olaral operatör almayı dene.

		lastToken = tokens[counter++];
		
		maxdepth = maxdepth > depth ? maxdepth : depth;

	}while(counter <= maxtokens && lastToken != NULL && lastToken->type != END);
	
	if(lastToken == NULL)
		tokens = NULL;

	*d = maxdepth;
	return tokens;
}

struct Token *createNumberToken(float number, int depth)
{
	struct Token *token = (struct Token *)malloc(sizeof(struct Token));
	
	token->type = NUMBER;
	token->number = number;
	token->depth = depth;

	return token;
}

struct Token *createOperatorToken(char *op, int depth)
{
	struct Token *token = (struct Token *)malloc(sizeof(struct Token) * (strlen(op) + 1));	
        token->op = (char *)malloc(sizeof(char) * (strlen(op) + 1)); // Fonksiyon ismi için bellek ayır.


	token->type = OPERATOR;
	strcpy(token->op, op);
	token->depth = depth;
	
	return token;
}

struct Token *createFunctionToken(char *func_name, int depth)
{
	
	struct Token *token = (struct Token *)malloc(sizeof(struct Token)); // Token için bellek ayır.
	token->op = (char *)malloc(sizeof(char) * (strlen(func_name) + 1)); // Fonksiyon ismi için bellek ayır.
	
	token->type = FUNCTION;
	strcpy(token->op, func_name);
	token->depth = depth;
	
	return token;
}

struct Token *createEndToken()
{
	struct Token *token = (struct Token *)malloc(sizeof(struct Token));
	
	token->type = END;

	return token;
}

void freeToken(struct Token **token)
{
	free(*token);
	token = NULL;
}


struct Token *getOperator(char **expr, int *depth)
{
	struct Token *token;

	while(isspace(**expr) || is_parenthesis(**expr))
	{
		if(**expr == '(' || **expr == '[')
			(*depth)++;
		else if(**expr == ')' || **expr == ']')
			(*depth)++;
	}

	if(**expr == '\0')
	{	
		// expr sadece boşluksa(operatör yoksa) END token dön.
		token = createEndToken();
	}else
	{

		token = createOperatorToken(chartos(**expr), *depth);
		(*expr)++; // operatoru atla.
	}
	
	if(token->type == OPERATOR && getClass(token->op) == -1)
	{
		free(token);
		token = NULL;
	}

	return token;
}


struct Token *getNumber(char **expr, int *depth)
{
	struct Token *token = NULL;

	while(isspace(**expr) || is_parenthesis(**expr) || **expr == ',')
	{
		if(**expr == '(' || **expr == '[')
			(*depth)++;
		else if(**expr == ')' || **expr == ']')
			(*depth)--;

		(*expr)++;
	}	// Boşlukları atla ve parantezleri işle.

	if(**expr == '\0')
		token = createEndToken(); // İfadenin sonuna ulaşıldı. end token oluştur.
	else if(isdigit(**expr) || ((**expr == '+' || **expr == '-') && isdigit(*(*expr + 1))))
	{
		token = createNumberToken(atof(*expr), *depth);

		if(**expr == '+' || **expr == '-')
			(*expr)++;
		while(isdigit(**expr))
			(*expr)++;
		if(**expr == '.')
			(*expr)++;
		while(isdigit(**expr))
			(*expr)++;
	}

	return token;
}

struct Token *getVariable(char **expr, int *depth)
{	
	struct Token *token = NULL;
	char *var_name;
	int i;

	// Boşlukları atla ve parantezleri işle.
	while(isspace(**expr) || is_parenthesis(**expr))
	{
		if(**expr == '(' || **expr == '[')
			(*depth)++;
		else if(**expr == ')' || **expr == ']')
			(*depth)--;

		(*expr)++;
	}
	
	if(**expr == '\0')
		token = createEndToken();

	else
	{	
		var_name = getword(*expr); // Değişken ismini al.
		if((i = varexists(var_name)) != -1)
		{
			(*expr) += strlen(var_name); // Değişken ismini artık atlayabiliriz.
			token = createNumberToken(getvarval(i), *depth);
		}
	}

	return token;
}

struct Token *getFunction(char **expr, int *depth)
{	
	char *func_name = NULL;
	
	// Boşlukları atla.
	while(isspace(**expr) || is_parenthesis(**expr))
	{
		if(**expr == '(' || **expr == '[')
			(*depth)++;
		else if(**expr == ')' || **expr == ']')
			(*depth)--;

		(*expr)++;
	}	

	if(**expr == '\0')
		return createEndToken();
	else if(**expr == '!')
		func_name = chartos(**expr);
	else
		func_name = getword(*expr);
	
	if(func_name == NULL || getClass(func_name) == -1)
		return NULL;
	else
		(*expr) += strlen(func_name);

	return createFunctionToken(func_name, *depth);
}
