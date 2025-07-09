#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "expr.h"
#include "variables.h"

#define MAXTOKENS	1000
#define MAXEXPR		5000
#define NCOMMANDS	2

// İfade tipleri
#define DECLARATION	1 // Değişken tanımlama
#define EXECUTION	2 // Sadece fade çözme
#define COMMAND		3 //stop veya listvar gibi komutlar girilmesi.

int strcmp(char *, char *);
int iscommand(char *);
void terminate(); // Programı sonlandır.

char *commands[] =
{
	"terminate", "vars"
};

void (*command_funcs[])() = 
{
	terminate, list_vars
};

int main()
{	
	
	char *expr = (char *)malloc(sizeof(char) * MAXEXPR);
	struct Token *tokens[MAXTOKENS];
	int depth, state, i;
	double ans;
	int stop = 0;
	char *var_name;
	void (*fptr)(); // function pointer for commands.

	while(!stop)
	{
		getexpr(expr, MAXEXPR);
		
		// expr içinde '=' karakter var mı kontrol et.
		if((var_name = isdeclaration(expr)) != NULL)
		{
			state = DECLARATION;
			skipdeclaration(&expr); // '=' e kadar olan bölümleri kaldır.

		}else if((i = iscommand(expr)) != -1)
		{
			state = COMMAND;
			fptr = command_funcs[i];
		}else
			state = EXECUTION;
		
		if(state == COMMAND)
		{
				fptr(); // İlgili komutu gerçekleştiren fonksiyonu çalıştır.
		}else
		{
			if(tokenize(expr, tokens, MAXTOKENS, &depth) == NULL)
				perror("Hatalı ifade!\n");
			else if(evaluate_expression(tokens, depth, &ans) == 0)
				printf("Hatalı ifade!\n");
			else
			{	
				if(state == DECLARATION)
				{
					if(addvar(var_name, ans)) // Değişkeni değişken listesine ekle.
						printf("%s= %lf\n", var_name, ans);
					else
					{
						printf("Çok fazla değişken!");
					}
				}else
					printf("result= %lf\n", ans);
			}
		}
	}

	return stop;
}

int iscommand(char *expr)
{
	for(int i = 0; i < NCOMMANDS; ++i)
		if(strcmp(commands[i], expr) == 0)
			return i; // Fonksiyonun bulunduğu indeksi dön.	
	
	return -1;
}

void terminate()
{
	puts("Program sonlandırılıyor...");
	exit(0); // Sonlandır.
}
