#include <stdio.h>
#include <stdlib.h>
#include "common.h"


int main(void)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    FILE *file = NULL;
    
    printf("AoC Day1 Puzzle 1!\n");

    file = get_input_data("../input.txt");
    
    int idx = 1;
    while ((read = getline(&line, &len, file)) > 0)
    {
        // Process each line
        printf("%d) %s", idx, line);
        idx++;
    }

    free(line);
    fclose(file);
    // loop over each line input
    //      - Get integers into two lists.
    // Sort list by value.
    // Contrast each index to get their difference. Store to 3rd list.
    // find total distance and return result.

    return 0;
}
