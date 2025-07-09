#define MAXNAME	10


typedef double (*doubleOpFunc)(double, double);
typedef double (*singleOpFunc)(double);

struct Function
{
	char op[MAXNAME]; // +, -, sin, cos, ...
	int params; // Parametre sayısı
	int priority; // Önceliği 1 olan en öncelikli 3 olan en düşük.	
	union{
		doubleOpFunc doubleOperand;
		singleOpFunc singleOperand;
	};
};

// Verilen op'nin öncelik numarasını dön.
int getClass(char *op);

// Verilen op'nin parametre sayısını dön.
int getParameters(char *op);

// op operatörüne ait olan fonksiyonu dön.
// op nin parametre sayısı 2 olmalı.
doubleOpFunc getDoubleOperandFunction(char *op);


/*
 *	op operatörüne ait fonksiyonu dön.
 *	op'nin parametre sayısı 1 olmalı.
 * */
singleOpFunc getSingleOperandFunction(char *op);
