#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

#define MAX_DATA          (1000)
#define MAX_DATA_PER_LINE (8)

#define LVL_BND_MAX      (4)
#define LVL_BND_MIN      (0)

typedef enum{
    UNSAFE = 0,
    SAFE = 1
} report_status_e;

typedef enum{
    VALID           = 0,
    INVALID_DIFF,
    INVALID_DIR,
    INVALID
} report_err_type_e;

typedef enum{
    LVL_NONE            = 0,
    LVL_INCREMENTING,
    LVL_DECREMENTING,
    LVL_INVALID
} report_dir_lvl_e;


report_err_type_e check_number_difference(uint32_t num_prev, uint32_t num_next)
{
    uint32_t num_diff = 0;
    report_err_type_e report_value = VALID;

    /* Get difference */
    if (num_prev < num_next)
    {
        num_diff = num_next - num_prev;
    }
    else if (num_prev > num_next)
    {
        num_diff = num_prev - num_next;
    }
    else
    {
        num_diff = 0;
    }

    /* Check if difference is within bounds */
    if ((num_diff == LVL_BND_MIN)||(num_diff >= LVL_BND_MAX))
    {
        report_value = INVALID_DIFF;
    }

    return report_value;
}

report_err_type_e check_number_level(uint32_t num_prev, uint32_t num_next, report_dir_lvl_e *level_dir)
{
    report_err_type_e report_value = VALID;

    if (num_prev < num_next)
    {
        *level_dir |= LVL_INCREMENTING;
    }
    else if (num_prev > num_next)
    {
        *level_dir |= LVL_DECREMENTING;
    }
    else
    {
        *level_dir |= LVL_INVALID;
    }

    /* Check if direction is invalid, then override result to UNSAFE */
    if (*level_dir == LVL_INVALID)
    {
        report_value = INVALID_DIR;
    }

    return report_value;
}

report_status_e assess_reports(uint32_t *list)
{
    report_status_e result = SAFE;

    uint32_t num_prev = list[0];
    uint32_t num_next = 0;

    report_dir_lvl_e level_direction = LVL_NONE;

    report_err_type_e err_list[MAX_DATA_PER_LINE] = {VALID};
    uint8_t err_count = 0;

    /* Assess each report*/
    for (uint8_t idx = 1; idx < MAX_DATA_PER_LINE; idx++)
    {
        num_next = list[idx];

        /* Check if end of list, always ended with 0 */
        if (num_next == 0)
        {
            break;
        }

        /* Get level difference */
        err_list[idx] |= check_number_difference(num_prev, num_next);

        err_list[idx] |= check_number_level(num_prev, num_next, &level_direction);
        
        printf("%u) %u %u -> %u\n", idx, num_prev, num_next, result);
        num_prev = num_next;
    }

    /* Count errors */
    for (uint8_t idx = 0; idx < MAX_DATA_PER_LINE; idx++)
    {
        if (err_list[idx] > 0)
        {
            err_count++;
        }
    }

    if (err_count > 0)
    {
        result = UNSAFE;
    }

    return result;
}


void puzzle_part_1(void)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    FILE *file = NULL;
    
    char *token = NULL;
    uint16_t report_safe_count = 0;
    uint32_t list_num[MAX_DATA_PER_LINE];
    
    file = get_input_data("../input.txt");
    
    /* loop over each line input */ 
    read = getline(&line, &len, file);
    while (read > 0)
    {
        /* Clear array for reuse */
        clear_array(list_num, MAX_DATA_PER_LINE);

        /* Loop over each number in line */
        token = strtok(line, " ");
        for (uint8_t idx = 0; ((token != NULL)&&(idx < MAX_DATA_PER_LINE)); idx++)
        {
            /* Store integer into list */
            sscanf(token, "%u", &list_num[idx]);

            /* Get next number */
            token = strtok(NULL, " ");
        }

        /* Assess reports if within standard */
        report_safe_count += assess_reports(list_num);

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
