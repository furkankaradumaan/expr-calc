int is_parenthesis(char c); // Verilen karakter bir parantezse 1 aksi halde 0 dön.
double degrees_to_radians(double degrees);
double radians_to_degrees(double radians);
int istakingradians(double (*fptr)(double));
int isgivingradians(double (*fptr)(double));
int haschar(char *, char); // bir stringin içinde istenen karakter var mı kontrol et.
char *substr(const char *str, int start, int end);
char *getword(char *expr); //İlk kelimeyi dön. Bir kelimenin içinde numerik veya özel karakterler bulunamaz.
char *chartos(char);
int isFunctionName(char *);
