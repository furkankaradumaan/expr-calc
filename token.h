#ifndef	TOKEN_H
#define TOKEN_H

#define	SINGLEFUNCS	5
#define DOUBLEFUNCS	1

enum TokenType
{
	NUMBER, OPERATOR,FUNCTION, END	
};

struct Token
{
	enum TokenType type;
	int depth;
	union
	{
		float number;
		char *op;
	};
};


/*
 *	tokens listesinden 'left' indisi ile (dahil) right indisi(dahil değil) arasındaki tüm tokenleri sil.
 *	'right' indisinden sağda kalan tokenleri de uygun yerlere kaydır.
 * */
int rmtokens(struct Token *tokens[], int left, int right);

/*
 *	function_names listesinden fonksiyon ismini bul ve indeksini dön.
 *	eğer bulunmuyorsa -1 dön. Tek parametreli fonksiyonlarda arar.
 * */
int findSingleFunc(char *func_name);

/*
 *	Çift parametre alan fonksiyonlarda ara.
 * */
int findDoubleFunc(char *func_name);

int count_tokens(struct Token *tokens[]);


/*
 *	expr ile alınan matematiksel ifadeyi parçalara ayır. Token'ler oluştur ve tokens içine diz.
 *	En fazla 'maxtokens' token olabilir. en son tokens'i dön.
 *	En sonunda bulunan maksimum deinliği depth içine yaz.
 * */
struct Token **tokenize(char *expr, struct Token *tokens[], int maxtokens, int *depth);

/*
 *	expr içinde en başta bir sayı varsa onu al
 *	Sayıyı aldıktan sonra bir token oluştur ve token'i dön. Hata durumunda token tipini end olarak dön.
 *	Fonksiyona derinliğin adresi geçilir çünkü sayı alındığı sırada parantez içine girme veya çıkma durumlarında
 *	depth'in değeri güncellenmelidir.
 * */
struct Token *getNumber(char **expr, int *cur_depth);

/*
 *	Operatörü al, token oluştur ve token'e yerleştir.
 *	Token'i dön. Hata durumunda token tipini end olarak dön.
 * */
struct Token *getOperator(char **expr, int *cur_depth);

struct Token *getVariable(char **expr, int *cur_depth);
/*
 *	FUNC ismini alır ve token'e yerleştirir.
 *	Daha sonra token'i döner.
 * */
struct Token *getFunction(char **expr, int *cur_depth);

/*
 *	NUMBER tipinde bir token oluştur ve sayısını ve derinliğini verilen şekilde düzenle.
 *	Oluşturulan token'in adresini dön.
 * */
struct Token *createNumberToken(float number, int depth);

/*
 *	Bir token'in tipi aslında NUMBER'dir. sayı almaya çalışırken fonksiyon ismiyle karşılaşıldığında bu token devreye girer. Fonksiyon ismini alır ve Token'in 
 *	*func değişkenine yazılır. NUMBER fonksiyonu içinde bu token parametreleri de alınarak fonksiyonun ifade ettiği sayı hesaplanır.
 * */
struct Token *createFunctionToken(char *func_name, int depth);

/*
 *	OPERATOR tipinde bir token oluştur ve op ve derinlik değişkenlerini  düzenle.
 *	Adresini dön.
 * */
struct Token *createOperatorToken(char *op, int depth);

/*
 *	END tipinde bir token oluştur ve dön. Sadece tokenin tipi end olarak ayarlanır.
 * */
struct Token *createEndToken();

/*
 *	Token için ayrılmış alanı serbest bırak ve pointer'ini tekrar NULL olarak ayarla.
 * */
void freeToken(struct Token **token);


#endif
