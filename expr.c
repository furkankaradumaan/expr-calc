#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "calculations.h"
#include "controls.h"
#include "expr.h"
#include <string.h>
#include "supfuncs.h"

void getexpr(char *expr, int max)
{
	
	int ch, len;
	while(isspace(ch = getchar())); // Boşlukları atla.
	
	if(ch != EOF)
		(*expr) = ch;

	for(len = 1; len < max - 1 && (ch = getchar()) != EOF && ch != '\n'; len++)
	{
		*(expr + len) = ch;
	}
	*(expr + len) = '\0';
}


// sin(tan(45))
int evaluate_expression(struct Token *tokens[], int depth, double *ans)
{
	int size = count_tokens(tokens);
	int control;

	while(depth > 0)
	{
		control = evaluate_functions(tokens, &size, depth);
	
		if(control == 0)
			return control;

		control = evaluate_mul_div(tokens, &size, depth);
		
		if(control == 0)
			return control;
		control = evaluate_sum_sub(tokens, &size, depth);
		
		if(control == 0)
			return control;
		depth--;
	}

	*ans = tokens[0]->number;

	return 1; // Başarılı.
}

int evaluate_mul_div(struct Token *tokens[], int *tokensSize, int depth) 
{
	double (*fptr)(double, double);
	double(*sfptr)(double);
	int params;

	for(int i = 1; i < *tokensSize; ++i)
	{
			
			if(!(tokens[i]->depth == depth) || !(tokens[i]->type == OPERATOR) || !(getClass(tokens[i]->op) == 2))
				continue;

			params = getParameters(tokens[i]->op); // Parametre sayısını al.
			if(params == 2)
			{
				fptr = getDoubleOperandFunction(tokens[i]->op); // Fonksiyonu al.
				*tokensSize -= params;
                                if(!type_control(NUMBER, tokens[i - 1]) || !type_control(NUMBER, tokens[i + 1]))
                                        return 0; // Bir önceki veya bir sonraki operand NUMBER tipinde değil!

                                tokens[i - 1]->number = fptr(tokens[i - 1]->number, tokens[i + 1]->number);
                                rmtokens(tokens, i, i + 2);
                                i--;

			}
			else if(params == 1)
			{
				sfptr = getSingleOperandFunction(tokens[i]->op);
			
				(*tokensSize) -= params;
				if(!type_control(NUMBER, tokens[i - 1]))
					return 0;
				tokens[i - 1]->number = sfptr(tokens[i - 1]->number);
				rmtokens(tokens, i, i + 1);
				i--;
			}
	}
			
	return 1; // İşlem başarılı.
}

int evaluate_sum_sub(struct Token *tokens[], int *tokensSize, int depth)
{
	double (*fptr)(double, double);
	int params;

        for(int i = 0; i < *tokensSize; ++i)
        {
	
		if(!(tokens[i]->type == OPERATOR) || !(tokens[i]->depth == depth) || !(getClass(tokens[i]->op) == 3))
			continue;

		params = getParameters(tokens[i]->op);
           	if(params == 2)
		{
			fptr = getDoubleOperandFunction(tokens[i]->op);
			if(!type_control(NUMBER, tokens[i - 1]) || !type_control(NUMBER, tokens[i + 1]))
				return 0;

			*tokensSize -= 2;
			tokens[i - 1]->number = fptr(tokens[i - 1]->number, tokens[i + 1]->number);
                        rmtokens(tokens, i, i + 2);
                        i--;
		}
	}
        

        for(int i = 0; i < *tokensSize; ++i)
                if(tokens[i]->depth == depth)
                        tokens[i]->depth--; // depth'i 1 azalt.

        return 1; // İşlem başarılı.
}

int evaluate_functions(struct Token *tokens[], int *tokensSize, int depth)
{
	double (*sfptr)(double);
	double (*fptr)(double, double);
	int params;

	for(int i = 0; i < *tokensSize; ++i)
	{
		if(!(tokens[i]->depth == depth) || !(tokens[i]->type == FUNCTION) || !(getClass(tokens[i]->op) == 1))
			continue;

		params = getParameters(tokens[i]->op); // Fonksiyonun parametre sayısını al.
		

		if(strcmp(tokens[i]->op, "!") == 0)
		{
			if(i == 0 || !type_control(NUMBER, tokens[i - 1]) || tokens[i - 1]->number != (int)(tokens[i - 1]->number))
				return 0;
			
			sfptr = fact;
			tokens[i - 1]->number = sfptr(tokens[i - 1]->number);
			
			(*tokensSize) -= params;
			rmtokens(tokens, i, i + 1);
			i--;
		}
		else if(params == 1)
		{
			if(!type_control(NUMBER, tokens[i + 1]))
				return 0;

			sfptr = getSingleOperandFunction(tokens[i]->op);

			if(sfptr == fib && tokens[i + 1]->number != (int)(tokens[i + 1]->number))
				return 0;

			tokens[i]->type = NUMBER;
			if(istakingradians(sfptr))
				tokens[i]->number = sfptr(degrees_to_radians(tokens[i + 1]->number));
			else
				tokens[i]->number = sfptr(tokens[i + 1]->number);


			if(isgivingradians(sfptr))
				tokens[i]->number = radians_to_degrees(tokens[i]->number);

			rmtokens(tokens, i + 1, i + 2);
			(*tokensSize)--;
		}
		else if(params == 2)
		{
			// parametrelerin tip kontrollerini yap.
			if(!type_control(NUMBER, tokens[i + 1]) || !type_control(NUMBER, tokens[i + 2]))
				return 0;
			
			fptr = getDoubleOperandFunction(tokens[i]->op);
			tokens[i]->type = NUMBER;
			tokens[i]->number = fptr(tokens[i + 1]->number, tokens[i + 2]->number);

			rmtokens(tokens, i + 1, i + 3);
			(*tokensSize) -= 2;
		}
	}

	return 1;
}

int type_control(int i, struct Token *token)
{
	return token->type == i;
}
