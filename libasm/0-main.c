#include <stdio.h>

int asm_strcmp(const char *s1, const char *s2);

int main(void) {
    int compare = asm_strcmp("Hello World", "Hello orld");
    printf("%d\n", compare);
}