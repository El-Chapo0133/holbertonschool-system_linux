#include <stdio.h>

int asm_strncmp(const char *s1, const char *s2, int n);

int main(void) {
    int compare = asm_strncmp("Hello World", "Hello orld", 5);
    printf("%d", compare);
}