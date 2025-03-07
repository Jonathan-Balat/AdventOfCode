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


void check_number_difference(uint8_t idx, uint32_t *list, int32_t *err_diff_list, report_err_type_e *report_list)
{
    int32_t num_A = list[idx];
    int32_t num_B = list[idx+1];
    int32_t num_C = list[idx+2];

    int32_t x = abs(num_C-num_B);
    int32_t y = abs(num_B-num_A);
    // int32_t z = abs(num_C-num_A);

    /* Get difference */
    if ((x < LVL_BND_MAX) && (x>LVL_BND_MIN))
    {
        if ((y < LVL_BND_MAX) && (y>LVL_BND_MIN))
        {
            // report_list = VALID;
            // Do nothing, array indeces are default valid
        }
        else
        {
            report_list[idx] |= INVALID_DIFF;
            err_diff_list[idx] = 1;
        }
    }
    else
    {
        if ((y < LVL_BND_MAX) && (y>LVL_BND_MIN))
        {
            report_list[idx+2] |= INVALID_DIFF;
            err_diff_list[idx+2] = 1;
        }
        else
        {
            report_list[idx+1] |= INVALID_DIFF;
            err_diff_list[idx+1] = 1;
        }
    }

}

void check_number_level(uint8_t idx, uint32_t *list, int32_t *err_dir_list, report_err_type_e *report_list)
{
    int32_t num_A = list[idx];
    int32_t num_B = list[idx+1];
    int32_t num_C = list[idx+2];

    int32_t x = (num_C-num_B)>0;
    int32_t y = (num_B-num_A)>0;
    int32_t z = (num_C-num_A)>0;
   
    /* Get level */
    if (x == y)
    {
        if (x == z)
        {
            // *report_list = VALID;
            // Do nothing, array indeces are default valid
        }
        else
        {
            report_list[idx+2] |= INVALID_DIR;
            err_dir_list[idx+2] = 1;
        }
    }
    else
    {
        if  (x == z)
        {
            report_list[idx+1] |= INVALID_DIR;
            err_dir_list[idx+1] = 1;
        }
        else
        {
            report_list[idx] |= INVALID_DIR;
            err_dir_list[idx] = 1;
        }
    }
}

uint8_t assess_report(uint32_t *list, uint8_t idx_max, uint32_t *unique_err_count)
{
    int32_t err_dir[idx_max];
    int32_t err_diff[idx_max];
    report_err_type_e err_list[idx_max];
    uint8_t err_count = 0;
    uint8_t unique_err_bitm = 0;

    /* Clear errors before re/assessing */
    clear_array(err_list, idx_max);
    clear_array((uint32_t *)err_dir, idx_max);
    clear_array((uint32_t *)err_diff, idx_max);
    err_count = 0;

    /* Assess numbers in report */
    for (uint8_t idx = 0; idx < (idx_max-2); idx++)
    {
        /* Get level difference */
        check_number_difference(idx, list, &err_diff[0], &err_list[0]);
        check_number_level(idx, list, &err_dir[0], &err_list[0]);

    }

    for (uint8_t idx = 0; idx < idx_max; idx++)
    {
        if (err_list[idx] > VALID)
        {
            err_count++;
        }

        unique_err_bitm |= err_list[idx];
    }

    if ((unique_err_bitm != INVALID)&&(err_count == 1))
    {
        (*unique_err_count)++;
    }

    if (err_count == 1)
    {

        printf("Numbers: \n");
        for (uint8_t idx = 0; idx < idx_max; idx++)
        {
            printf("%d ", list[idx]);
        }
        printf("\n");

        printf("Errors %u (UNQ=%u): \n", err_count, *unique_err_count);
        for (uint8_t idx = 0; idx < idx_max; idx++)
        {
            printf("%d ", err_list[idx]);
        }

        printf("\n");
        for (uint8_t idx = 0; idx < idx_max; idx++)
        {
            printf("%d ", err_diff[idx]);
        }
        printf("\n");

        for (uint8_t idx = 0; idx < idx_max; idx++)
        {
            printf("%d ", err_dir[idx]);
        }
        printf("\n\n");
    }

    return err_count;
}

void puzzle_part_2(void)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    FILE *file = NULL;
    
    char *token = NULL;
    uint8_t idx_max = 0;
    uint16_t report_safe_count = 0;
    uint8_t error_count = 0;
    uint32_t unique_err_count = 0;
    uint32_t list_num[MAX_DATA_PER_LINE];
    
    file = open_file("../input.txt");
    
    /* loop over each line input */ 
    read = getline(&line, &len, file);
    while (read > 0)
    {
        /* Clear array for reuse */
        clear_array(list_num, MAX_DATA_PER_LINE);

        /* Loop over each number in line, and keep track of its size */
        token = strtok(line, " ");
        for (uint8_t idx = 0; ((token != NULL)&&(idx < MAX_DATA_PER_LINE)); idx++)
        {
            /* Store integer into list */
            sscanf(token, "%u", &list_num[idx]);

            /* Get next number */
            token = strtok(NULL, " ");
            idx_max = idx+1;
        }

        /* Assess reports if within standard */
        error_count = assess_report(list_num, idx_max, &unique_err_count);
        if (error_count == 0)
        {
            report_safe_count++;
        }

        read = getline(&line, &len, file);
    }


    printf("Number of safe reports: %u\n", report_safe_count);

    free(line);
    close_files();

}

int main(void)
{
    //puzzle_part_1();
    puzzle_part_2();
    
    return 0;
}
