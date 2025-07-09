#include <math.h>

double sum(double i, double j) {return i + j;}
double sub(double i, double j) {return i - j;}
double mul(double i, double j) {return i * j;}
double div(double i, double j)
{
	if(j == 0)
		return 0.0;

	return i / j;
}

double mod(double i, double j)
{
	return fmod(i, j);
}

double power(double i, double j)
{
	return pow(i, j);
}

double fact(double val)
{

	int ans = 1;
	
	while(val > 1)
		ans *= val--;

	return ans;
}

double cot(double x)
{
	return 1 / tan(x);
}
double sec(double x)
{
	return 1 / cos(x);
}

double cosec(double x)
{
	return 1 / sin(x);
}

double fib(double n)
{
	if(n == 1 || n == 2)
		return 1;

	int x = 1, y = 1, fib;
	
	n -= 2;
	for(int i = 0; i < n; i++)
	{
		fib = x + y;
		x = y;
		y = fib;
	}
	
	return fib;
}




