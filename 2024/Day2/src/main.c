#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

#define MAX_DATA          (1000)
#define MAX_DATA_PER_LINE (8)

#define LVL_NONE          (0)
#define LVL_DECREMENTING  (1)
#define LVL_INCREMENTING  (2)
#define LVL_INVALID       (3)

#define LVL_BND_MAX      (4)
#define LVL_BND_MIN      (0)

typedef enum{
    SAFE = 0,
    UNSAFE = 1
}report_status_e;


report_status_e assess_reports(uint32_t *list)
{
    report_status_e result = SAFE;

    uint8_t level_dir_bitm = LVL_NONE;

    uint32_t num_prev = list[0];
    uint32_t num_next = 0;
    uint32_t num_diff = 0;

    /* Assess each report*/
    for (uint8_t idx = 1; idx < MAX_DATA_PER_LINE; idx++)
    {
        num_next = list[idx];

        /* Check if already unsafe. Skip further assessments. */
        if (result == UNSAFE)
        {
            break;
        }

        /* Check if end of list, always ended with 0 */
        if (num_next == 0)
        {
            break;
        }

        /* Get level difference and direction */
        if (num_prev < num_next)
        {
            level_dir_bitm |= LVL_INCREMENTING;
            num_diff = num_next - num_prev;
        }
        else if (num_prev > num_next)
        {
            level_dir_bitm |= LVL_DECREMENTING;
            num_diff = num_prev - num_next;
        }
        else
        {
            level_dir_bitm |= LVL_INVALID;
            num_diff = 0;
        }

        /* Check if difference is within bounds */
        if ((num_diff == LVL_BND_MIN)||(num_diff >= LVL_BND_MAX))
        {
            result |= UNSAFE;
        }

        /* Check if direction is invalid, then override result to UNSAFE */
        if (level_dir_bitm == LVL_INVALID)
        {
            result |= UNSAFE;
        }
        
        // printf("%u) %u %u %u %u -> %u\n", idx, num_prev, num_next, num_diff, level_dir_bitm, result);
        num_prev = num_next;
    }

    // if (result == SAFE)
    // {
    //     printf("SAFE\n\n");
    // }
    // else
    // {
    //     printf("UNSAFE\n\n");
    // }

    return result;
}

void puzzle_part_1(void)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    FILE *file = NULL;
    
    char *token = NULL;
    report_status_e report_value = SAFE;
    uint16_t report_idx = 0;
    uint16_t report_safe_count = 0;
    uint32_t list_num[MAX_DATA_PER_LINE];
    
    file = get_input_data("../input.txt");
    
    /* loop over each line input */ 
    read = getline(&line, &len, file);
    report_idx = 0;
    while (read > 0)
    {
        /* Loop over each number in line */
        token = strtok(line, " ");
        for (uint8_t idx = 0; ((token != NULL)&&(idx < MAX_DATA_PER_LINE)); idx++)
        {
            /* Store integer into list */
            sscanf(token, "%u", &list_num[idx]);

            /* Get next number */
            token = strtok(NULL, " ");
        }

        report_value = assess_reports(list_num);
        if (report_value==SAFE)
        {
            report_safe_count++;
        }

        /* Clear list */
        for (uint8_t idx = 0; idx < MAX_DATA_PER_LINE; idx++)
        {
            list_num[idx] = 0;
        }

        report_idx++;

        read = getline(&line, &len, file);
    }


    printf("Number of safe reports: %u\n", report_safe_count);

    free(line);
    fclose(file);
}

void puzzle_part_2(void)
{

}

int main(void)
{
    puzzle_part_1();
    // puzzle_part_2();
    
    return 0;
}
