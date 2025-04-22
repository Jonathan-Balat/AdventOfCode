#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "common.h"

#define OFFSET_MUL_CHAR     (4)
#define OFFSET_COMMA_CHAR   (1)
#define OFFSET_NUM_CHAR     (3)

#define DECIMAL             (10)

typedef struct{
    char *ptr_start;
    char *ptr_num_a_start;
    char *ptr_comma_start;
    char *ptr_num_b_start;
    char *ptr_end;
    bool b_qualify;
} MUL_INSTR_t;

typedef struct{
    char *ptr_current_start;
    char *ptr_next_start;
} INSTR_PTRS_t;

uint32_t do_count = 0x0;
uint32_t dont_count = 0x0;

uint32_t get_number(char *ptr_to_num)
{
    uint32_t num = 0;

    num = strtol(ptr_to_num, NULL, DECIMAL);

    return num;
}

#define assert_break(cond) if (!(cond)) { break; }


void update_do_dont_pointers(INSTR_PTRS_t *dos, INSTR_PTRS_t *dont, MUL_INSTR_t instr)
{
    char *tmp = NULL;

    /* Move to next instruction occurrence */
    if (dos->ptr_next_start != NULL)
    {
        if (dos->ptr_next_start < instr.ptr_start)
        {
            tmp = strstr((dos->ptr_next_start+1), "do()");
            if (tmp != NULL)
            {
                dos->ptr_current_start = dos->ptr_next_start;
                dos->ptr_next_start = tmp;
            
                do_count++;
                
            }
        }
    }

    /* Move to next instruction occurrence */
    if (dos->ptr_next_start != NULL)
    {
        if (dont->ptr_next_start < instr.ptr_start)
        {
            tmp = strstr((dont->ptr_next_start+1), "don't()");
            if (tmp != NULL)
            {
                dont->ptr_current_start = dont->ptr_next_start;
                dont->ptr_next_start = tmp;
            
                dont_count++;
            }
        }
    }
}

MUL_INSTR_t qualify_mul_instruction(INSTR_PTRS_t *dos, INSTR_PTRS_t *dont, MUL_INSTR_t instr)
{
    /* Evaluate if qualified or not. */
    if (instr.b_qualify)
    {
        if ((instr.ptr_start > dont->ptr_current_start))
        {
            printf("\nDisabled");
            instr.b_qualify = false;
        }
        else
        {
            printf("\n ???");// Do nothing
        }
    }
    else if(!instr.b_qualify)
    {
        if ((instr.ptr_start > dos->ptr_current_start))
        {
            printf("\nEnabled");
            instr.b_qualify = true;
        }
        else
        {
            printf("\n !!!");// Do nothing
        }
    }
    else
    {
        printf("\n ---");// Do nothing
    }
    
    printf("\nSTATUS[%u]\n", instr.b_qualify);
    printf("\n\tDO:   %u", dos->ptr_current_start);
    printf("\n\tDONT: %u ", dont->ptr_current_start);
    printf("\n\tMUL:  %u ", instr.ptr_start);

    return instr;
}


void puzzle_part_1(void)
{    
    ssize_t read;
    size_t len = 0;
    char *line = NULL; /* Automatically allocated in getline */
    FILE *file = NULL;

    MUL_INSTR_t instr = {0};
    INSTR_PTRS_t do_instr = {0};
    INSTR_PTRS_t dont_instr = {0};
      
    uint32_t num_a = 0;
    uint32_t num_b = 0;
    uint32_t sum = 0x0;
    
    file = open_file("../input.txt");
    
    /* Read first line to loop over */ 
    read = getline(&line, &len, file);
    instr.b_qualify = true;

    do_instr.ptr_current_start = strstr(line, "do()");
    if (do_instr.ptr_current_start != NULL)
    {
        do_count++;
    }

    dont_instr.ptr_current_start = strstr(line, "don't()");
    if (dont_instr.ptr_current_start != NULL)
    {
        dont_count++;
    }

    do_instr.ptr_next_start = strstr(do_instr.ptr_current_start+1, "do()");
    if (do_instr.ptr_next_start != NULL)
    {
        do_count++;
    }

    dont_instr.ptr_next_start = strstr(dont_instr.ptr_current_start+1, "don't()");
    if (dont_instr.ptr_next_start != NULL)
    {
        dont_count++;
    }

    while (read > 0)
    {
        /* Reset structure pointers */
        instr.ptr_start = NULL;
        instr.ptr_num_a_start = NULL;
        instr.ptr_comma_start = NULL;
        instr.ptr_num_b_start = NULL;
        instr.ptr_end = line;

        printf("\n\n");

        /* Extract mul from line */
        while (instr.ptr_end != NULL)
        {           
            /* Search string for mul( characters */
            instr.ptr_start = strstr(instr.ptr_end, "mul(");
            assert_break(instr.ptr_start != NULL);

            /* Verify that this doesn't cross any do/donts */
            update_do_dont_pointers(&do_instr, &dont_instr, instr);
 
            /* Search string for comma character */
            instr.ptr_comma_start = strstr(instr.ptr_start, ",");
            assert_break(instr.ptr_comma_start != NULL);
 
            /* Search string for ) character */
            instr.ptr_end = strstr(instr.ptr_start, ")");
            assert_break(instr.ptr_end != NULL);

            /* Check character positioning validity */
            if ((instr.ptr_comma_start - instr.ptr_start) > 7)
            {
                instr.ptr_end = instr.ptr_start + 1;
                continue;
            }

            if ((instr.ptr_end - instr.ptr_comma_start) > 4)
            {
                instr.ptr_end = instr.ptr_start + 1;
                continue;
            }

            instr = qualify_mul_instruction(&do_instr, &dont_instr, instr);
                         
            /* Get pointer to start of numbers */
            instr.ptr_num_a_start = instr.ptr_start + OFFSET_MUL_CHAR;
            instr.ptr_num_b_start = instr.ptr_comma_start + OFFSET_COMMA_CHAR;
        
            /* Check numbers' validity (max of 3 digits) */
            if ((instr.ptr_comma_start - instr.ptr_num_a_start) > OFFSET_NUM_CHAR)
            {
                printf("Invalid number A size\n");
                continue;
            }
                    
            if ((instr.ptr_end - instr.ptr_num_b_start) > OFFSET_NUM_CHAR)
            {
                printf("Invalid number B size \n");
                continue;
            }

            /* Get integers and take their sum */
            num_a = get_number(instr.ptr_num_a_start);
            num_b = get_number(instr.ptr_num_b_start);

            // if (instr.b_qualify)
            // {
                sum += num_a * num_b;
            // }

            printf(" %u %u %u", num_a, num_b, sum);
        }
        
        /* Read next line */
        read = getline(&line, &len, file);
    }
    
   printf("\n\nSUM=%u %u %u\n", sum, do_count, dont_count);
   
   free(line); 
   close_files();
}

int main(void)
{
    puzzle_part_1();
    
    return 0;
}
