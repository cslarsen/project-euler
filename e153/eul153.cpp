#include <stdio.h>

typedef long long int aint;
typedef double fl;

typedef struct complex_t {
	fl r, i;
} complex_t;

complex_t* conjugate(const complex_t* p)
{
	static complex_t c;
	c.r = p->r;
	c.i = -p->i;
	return &c;
}

complex_t* square(const complex_t* p)
{
	static complex_t c;
	c.r = p->r * p->r;
	c.i = -(p->i * p->i);
	return &c;
}

int isgaussian(const complex_t* p)
{
	return (p->r - (aint)p->r) == 0.0f && (p->i - (aint)p->i) == 0.0f;
}

// return num/denum
complex_t* div(complex_t num, complex_t denum)
{
		
}

int main()
{
	complex_t c = {1.0f, -2.1f};
	printf("%d\n", isgaussian(&c));

	c.r = 1.0f;
	c.i = -2.0f;
	printf("%d\n", isgaussian(&c));
	
}
