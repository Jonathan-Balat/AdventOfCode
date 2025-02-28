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

int puzzle_part_1(void)
{
    uint32_t L_list[MAX_DATA];
    uint32_t R_list[MAX_DATA];
    uint32_t difference = 0x0;
    uint32_t total_distance = 0;

    process_input_data(L_list, R_list);

    sort_ascending(L_list, MAX_DATA);
    sort_ascending(R_list, MAX_DATA);

    /* Puzzle Part 1 */
    printf("AoC Day1 Puzzle 1!\n");

    /* Contrast each index to get their difference, then add to total distance */
    for (uint32_t i = 0; i < MAX_DATA; i++)
    {
        if (R_list[i] >= L_list[i])
        {
            difference = R_list[i] - L_list[i];
        }
        else
        {
            difference = L_list[i] - R_list[i];
        }
        total_distance += difference;
    }

    printf("Total Distance: %d\n", total_distance);

    return total_distance;
}

void puzzle_part_2(void)
{
    uint32_t L_list[MAX_DATA];
    uint32_t R_list[MAX_DATA];
    uint32_t prev_num = 0;
    uint32_t similarity_score = 0;

    process_input_data(L_list, R_list);

    sort_ascending(L_list, MAX_DATA);
    sort_ascending(R_list, MAX_DATA);

    /* Puzzle Part 2 */
    printf("AoC Day1 Puzzle 2!\n");

    for (uint32_t idx = 0; idx < MAX_DATA; idx++)
    {
        if ((idx > 0) && (L_list[idx] == prev_num))
        {
            /* Skip if the number the same with previous number */
            continue;
        }
        else
        {
            /* Update last number used*/
            prev_num = L_list[idx];
        }

        for (uint32_t sub_idx=0; sub_idx<MAX_DATA; sub_idx++)
        {
            if (L_list[idx] == R_list[sub_idx])
            {
                similarity_score += L_list[idx];
            }
            else if (L_list[idx] < R_list[sub_idx])
            {
                break;
            }
            else
            {
                // Do nothing;
            }
        }
    }
      
    printf("Similarity score: %d\n", similarity_score);
}

int main(void)
{
    puzzle_part_1();
    puzzle_part_2();
    
    return 0;
}
