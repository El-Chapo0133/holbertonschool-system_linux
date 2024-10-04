#include <stdio.h>
#include "libasm.h"

int test(const char *s1, const char *s2, int n);

int main(void) {
	/*
    	int compare = asm_strcmp("Hello World", "Hello World");
	printf("%d\n", compare);
	compare = asm_strcmp("Hello World", "Hello orld");
	printf("%d\n", compare);
	compare = asm_strcmp("Hello orld", "Hello World");
	printf("%d\n", compare);
	*/
	test("Hello", "world", 1);
}
