#define MAXVARS 100 // En fazla 100 tane değişken olabilir.


char *isdeclaration(char *expr);
void skipdeclaration(char **expr);
int addvar(char *var_name, double var_val);
int varexists(char *var_name); // Değğişken ismi bulunuyorsa indeksini, bulunmuyorsa -1 dön.
double getvarval(int index); //Verilen indeksteki değişkenin değerini döner.
void list_vars();

