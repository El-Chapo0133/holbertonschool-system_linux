#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void display(int argc, int index_directory, char* directory, int count, char *values[count], Flags *my_flags, struct stat stats[count]);
