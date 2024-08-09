#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int get_lstats(int count, char **values, struct stat *stats);
