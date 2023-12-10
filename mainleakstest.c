#include <libc.h>

//tester leaks
void f()
{
	system("leaks a.out");
}

int main()
{
	atexit(f);
	char *s = malloc(10);
	free(s);
}