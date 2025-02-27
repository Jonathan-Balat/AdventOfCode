
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(void)
{
    char line[256];

    FILE *file = NULL;
    
    printf("AoC Day1 Puzzle 1!\n");

    file = get_input_data("../input.txt");
    
    while (fgets(line, sizeof(line), file)) 
    {
        // Process each line
        printf("%s\n", line);
    }

    fclose(file);
    // loop over each line input
    //      - Get integers into two lists.
    // Sort list by value.
    // Contrast each index to get their difference. Store to 3rd list.
    // find total distance and return result.

    return 0;
}
