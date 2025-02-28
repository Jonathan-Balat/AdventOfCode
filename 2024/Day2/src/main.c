#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

#define MAX_DATA (1000)

void process_input_data(uint32_t *list_A, uint32_t *list_B)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    FILE *file = NULL;
    uint32_t idx = 0;
    
    file = get_input_data("../input.txt");
    
    /* loop over each line input */ 
    read = getline(&line, &len, file);
    while (read > 0)
    {
        /* Store integers into two lists */
        sscanf(line, "%u %u", &list_A[idx], &list_B[idx]);
        idx++;

        read = getline(&line, &len, file);
    }

    free(line);
    fclose(file);
}

void puzzle_part_1(void)
{

}

void puzzle_part_2(void)
{

}

int main(void)
{
    puzzle_part_1();
    puzzle_part_2();
    
    return 0;
}
