#include <stdio.h>
#include "supfuncs.h"
#include <stdlib.h>
#include <ctype.h>
#include "variables.h"
#include <string.h>

int vars = 0;
char *var_names[MAXVARS];
double var_values[MAXVARS];

// Verilen ifade bir değişken tanımı mı kontrol et.
// Eğer geçerli bir değişken tanımıysa 1, aksi halde 0 dön.
char *isdeclaration(char *expr)
{
	
	char *var_name;
	char *start;

	// boşlukları atla.
	while(isspace(*expr))
		expr++;
	
	if(*expr == '=')
		return NULL; // ='den önce sadece boşluk var. Declaration olamaz.
	
	start = expr; // değişken isminin başlangıcı
	
	// Alfabe karakterlerini atla.
	while(isalpha(*expr))
		expr++;
	
	var_name = (char *)malloc(sizeof(char) * (expr - start + 1)); // Gerekli yeri ayır.
	strncpy(var_name, start, (expr - start));
	var_name[expr - start] = '\0';

	// Değişken isminden sonraki boşlukları da atla.
	while(isspace(*expr))
		expr++;
	
	// Artık ='e ulaşmış olmamız gerekiyor. 
	// Eğer eşittire ulaşılamadıysa ='in sonunda tek bir kelime(tek değişken ismi) yok demektir.
	if(*expr == '=')
		return var_name;

	return 0;
}

// İfadelerde Declaration kısmını atla.
void skipdeclaration(char **expr)
{
	while(**expr != '=')
		(*expr)++;
	(*expr)++;
}


// Değişken zaten bulunuyorsa güncelle, bulunmuyorsa ekle.
// Değişken eklenemiyorsa 0, aksi halde 1 dön.
int addvar(char *var_name, double var_val)
{	

	int index;
	if((index = varexists(var_name)) != -1)
	{
		var_values[index] = var_val; // Değişkenin değerini güncelle.
		return 1;
	}

	if(vars >= MAXVARS)
		return 0;

	var_names[vars] = (char *)malloc(sizeof(char) * strlen(var_name));
	strcpy(var_names[vars], var_name); // İsmi kopyala.
	
	var_values[vars] = var_val;

	vars++;
	return 1;
}

int varexists(char *var_name)
{
	for(int i = 0; i < vars; i++)
		if(strcmp(var_name, var_names[i]) == 0)
			return i;

	return -1;
}

double getvarval(int index)
{
	return var_values[index];
}

void list_vars()
{
	for(int i = 0; i < vars; ++i)
	{
		printf("%s = %lf\n", var_names[i], var_values[i]);
	}
}



