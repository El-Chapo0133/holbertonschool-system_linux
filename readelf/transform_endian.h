#ifndef TRANSFORM_ENDIAN
#define TRANSFORM_ENDIAN

#include <inttypes.h>

uint64_t get_byte_as_little_endian(unsigned char fifth_magic, uint64_t data, int size);

#endif