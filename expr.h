void getexpr(char *expr, int maxExpr);
int evaluate_mul_div(struct Token *tokens[], int *tokensSize, int depth);
int evaluate_sum_sub(struct Token *tokens[], int *tokensSize, int depth);
int evaluate_functions(struct Token *tokens[], int *tokensSize, int depth);
int evaluate_expression(struct Token *tokens[], int depth, double *ans);
int type_control(int x, struct Token *);
