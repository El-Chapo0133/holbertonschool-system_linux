#include "laps.h"

int main(void)
{

    int ids1[4] = {89, 42, 1, 101};
    int ids2[1] = {11};

    race_state(ids1, 4);
    printf("--\n");
    race_state(ids1, 4);
    printf("--\n");
    race_state(ids1, 4);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 4);
}
