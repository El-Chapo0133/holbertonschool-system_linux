#ifndef LIBASM
#define LIBASM

#include <stddef.h>

size_t asm_strlen(const char *str);
int asm_strcmp(const char *s1, const char *s2);
int asm_strncmp(const char *s1, const char *s2, int n);


#endif