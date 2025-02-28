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

int main(void)
{
    uint32_t L_list[MAX_DATA];
    uint32_t R_list[MAX_DATA];
    uint32_t diff_list[MAX_DATA];
    uint32_t total_distance = 0;

    printf("AoC Day1 Puzzle 1!\n");

    process_input_data(L_list, R_list);

    /* Puzzle Part 1 */
    sort_ascending(L_list, MAX_DATA);
    sort_ascending(R_list, MAX_DATA);

    /* Contrast each index to get their difference. Store to 3rd list. */
    for (uint32_t i = 0; i < MAX_DATA; i++)
    {
        if (R_list[i] >= L_list[i])
        {
            diff_list[i] = R_list[i] - L_list[i];
        }
        else
        {
            diff_list[i] = L_list[i] - R_list[i];
        }
    }

    /* find total distance and return result. */
    for (uint32_t i=0; i < MAX_DATA; i++)
    {
        total_distance += diff_list[i];
    }

    printf("Total Distance: %d\n", total_distance);
    return 0;
}
