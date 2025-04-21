#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"


/* PUZZLE 1 FUNCTIONS */

/* PUZZLE 2 FUNCTIONS */


int main(void)
{
    FILE *file = fopen("../input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    /* Puzzle 1 Scan */

    fclose(file);

    printf("Day 5\n");

    return 0;
}
