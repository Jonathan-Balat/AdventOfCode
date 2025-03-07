#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#define OFFSET_MUL_CHAR     (4)
#define OFFSET_COMMA_CHAR   (1)

#define DECIMAL             (10)

void process_input_data(uint32_t *list_A, uint32_t *list_B)
{
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;
    uint32_t idx = 0;
    FILE *file = NULL;
    
    file = open_file("../input.txt");
    
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
    close_files();
}


uint32_t get_number(char *ptr_to_num)
{
    uint32_t num = 0;

    num = strtol(ptr_to_num, NULL, DECIMAL);

    return num;
}

#define assert_break(cond) if (!(cond)) { break; }

void puzzle_part_1(void)
{
    FILE *file = NULL;
    file = open_file("../input.txt");
    
    char *line = NULL; /* Automatically allocated in getline */
    size_t len = 0;
    ssize_t read;

    // char *ptr_stride = NULL; // For Optimization

    char *ptr_start = NULL;
    char *ptr_num_a_start = NULL;
    char *ptr_comma_start = NULL;
    char *ptr_num_b_start = NULL;
    char *ptr_end = NULL;
      
    uint32_t num_a = 0;
    uint32_t num_b = 0;
    uint32_t sum = 0x0;
    
    printf("Starting loop\n\n");

    /* loop over each line input */ 
    read = getline(&line, &len, file);
    ptr_end = line;
    while (read > 0)
    {
        while (ptr_end != NULL)
        {
            /* Find Valid Instruction */

            // Search string for mul(*,*) characters
            ptr_start = strstr(ptr_end, "mul(");
            assert_break(ptr_start != NULL);
            ptr_comma_start = strstr(ptr_start, ",");
            assert_break(ptr_comma_start != NULL);
            ptr_end = strstr(ptr_comma_start, ")");
            assert_break(ptr_end != NULL);

            if ((ptr_comma_start - ptr_start) > 7)
            {
                ptr_end = ptr_start + OFFSET_MUL_CHAR;
                continue;
            }

            if ((ptr_end - ptr_comma_start) > 4)
            {
                ptr_end = ptr_start + OFFSET_MUL_CHAR;
                continue;
            }

            // Get pointer to start of numbers
            ptr_num_a_start = ptr_start + OFFSET_MUL_CHAR;
            ptr_num_b_start = ptr_comma_start + OFFSET_COMMA_CHAR;
        
            // Convert first digit (max of 3 digits)
            if ((ptr_comma_start - ptr_num_a_start) > 3)
            {
                printf("Invalid number A size\n");
                break;
            }
            else
            {
                num_a = get_number(ptr_num_a_start);
                // printf("Valid number A =  %u\n", num_a);
            }
                    
            // Convert 2nd string (max of 3 digits)
            if ((ptr_end - ptr_num_b_start) > 3)
            {
                printf("Invalid number B size \n");
                break;
            }
            else
            {
                num_b = get_number(ptr_num_b_start);
                // printf("Valid number B =  %u\n", num_b);
            }
            // printf("Valid numbers A, B =  %u, %u\n", num_a, num_b);
            sum += num_a * num_b;
        }
        
        read = getline(&line, &len, file);
        // printf("Read = %lld\n", read);

        ptr_start = NULL;
        ptr_num_a_start = NULL;
        ptr_comma_start = NULL;
        ptr_num_b_start = NULL;
        ptr_end = line;
    }

    
   printf("SUM=%u\n", sum);
   
   free(line);
   close_files();
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
