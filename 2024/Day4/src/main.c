#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

#define MAX_CHAR (142) /* +1 for next line */
#define LTR_X 'X'
#define LTR_M 'M'
#define LTR_A 'A'
#define LTR_S 'S'


uint16_t scan_horizontal(FILE *file)
{
    char *get_line = (char *)malloc((MAX_CHAR) * sizeof(char));
    uint16_t count = 0x0;
    uint8_t b_valid = 0x1;
    uint8_t i = 0;

    /********** Horizontal Forward **********/
    /* Iterate over each lines - Horizontal Forward */
    while (fgets(get_line, MAX_CHAR, file) != NULL)
    {
        // Remove newline character if present
        get_line[strcspn(get_line, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line[i] == LTR_X);
            b_valid &= (get_line[i+1] == LTR_M);
            b_valid &= (get_line[i+2] == LTR_A);
            b_valid &= (get_line[i+3] == LTR_S);

            if (b_valid)
            {
                count++;
            }
        }  
    }

    // printf("\nTotal count H-Forward: %d", count);

    /* Reset file pointer before returning */
    rewind(file);
    
    /********** Horizontal Reverse **********/
    /* Iterate over each lines - Horizontal Reverse */
    while (fgets(get_line, MAX_CHAR, file) != NULL)
    {
        uint8_t b_valid = 0x1;

        // Remove newline character if present
        get_line[strcspn(get_line, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (uint8_t i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line[i] == LTR_S);
            b_valid &= (get_line[i+1] == LTR_A);
            b_valid &= (get_line[i+2] == LTR_M);
            b_valid &= (get_line[i+3] == LTR_X);

            if (b_valid)
            {
                count++;
            }
        }  
    }

    printf("\nTotal count H: %d", count);
    /* Reset file pointer before returning */
    rewind(file);
    
    /* Free up allocated memory */
    free(get_line);

    return count;
}



uint32_t scan_vertical(FILE *file)
{
    char *get_line1 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line2 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line3 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line4 = (char *)malloc((MAX_CHAR) * sizeof(char));
    uint32_t count = 0x0;
    uint8_t b_valid = 0x1;
    uint8_t i = 0;

    /********** Vertical Forward **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines - Vertical Forward */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-2; i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i] == LTR_X);
            b_valid &= (get_line2[i] == LTR_M);
            b_valid &= (get_line3[i] == LTR_A);
            b_valid &= (get_line4[i] == LTR_S);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    // printf("\nTotal count V-Forward: %d", count);

    /* Reset file pointer before returning */
    rewind(file);

    /********** Vertical Reverse **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-2; i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i] == LTR_S);
            b_valid &= (get_line2[i] == LTR_A);
            b_valid &= (get_line3[i] == LTR_M);
            b_valid &= (get_line4[i] == LTR_X);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    printf("\nTotal count V: %d", count);
    
    /* Reset file pointer before returning */
    rewind(file);

    /* Free up allocated memory */
    free(get_line1);
    free(get_line2);
    free(get_line3);
    free(get_line4);
    
    return count;
}



uint32_t scan_diagonal_right(FILE *file)
{
    char *get_line1 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line2 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line3 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line4 = (char *)malloc((MAX_CHAR) * sizeof(char));
    uint32_t count = 0x0;
    uint8_t b_valid = 0x1;
    uint8_t i = 0;

    
    /********** Diagonal Right Forward **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i] == LTR_X);
            b_valid &= (get_line2[i+1] == LTR_M);
            b_valid &= (get_line3[i+2] == LTR_A);
            b_valid &= (get_line4[i+3] == LTR_S);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    // printf("\nTotal count DR-Forward: %d", count);

    /* Reset file pointer before returning */
    rewind(file);

    /********** Diagonal Right Reverse **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i] == LTR_S);
            b_valid &= (get_line2[i+1] == LTR_A);
            b_valid &= (get_line3[i+2] == LTR_M);
            b_valid &= (get_line4[i+3] == LTR_X);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    printf("\nTotal count DR: %d", count);

    /* Reset file pointer before returning */
    rewind(file);


    /* Free up allocated memory */
    free(get_line1);
    free(get_line2);
    free(get_line3);
    free(get_line4);

    return count;
}

uint32_t scan_diagonal_left(FILE *file)
{
    char *get_line1 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line2 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line3 = (char *)malloc((MAX_CHAR) * sizeof(char));
    char *get_line4 = (char *)malloc((MAX_CHAR) * sizeof(char));
    uint32_t count = 0x0;
    uint8_t b_valid = 0x1;
    uint8_t i = 0;

    
    /********** Diagonal Right Forward **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i+3] == LTR_X);
            b_valid &= (get_line2[i+2] == LTR_M);
            b_valid &= (get_line3[i+1] == LTR_A);
            b_valid &= (get_line4[i] == LTR_S);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    // printf("\nTotal count DL-Forward: %d", count);

    /* Reset file pointer before returning */
    rewind(file);

    /********** Diagonal Right Reverse **********/
    fgets(get_line1, MAX_CHAR, file);
    fgets(get_line2, MAX_CHAR, file);
    fgets(get_line3, MAX_CHAR, file);
    
    /* Remove newline character if present */
    get_line1[strcspn(get_line1, "\n")] = '\0';
    get_line2[strcspn(get_line2, "\n")] = '\0';
    get_line3[strcspn(get_line3, "\n")] = '\0';

    /* Iterate over each lines */
    while (fgets(get_line4, MAX_CHAR, file) != NULL)
    {
        /* Remove newline character if present */
        get_line4[strcspn(get_line4, "\n")] = '\0';

        // Loop over line characters, comparing forward
        for (i = 0; i < MAX_CHAR-(2+3); i++)
        {
            b_valid = 0x1;

            b_valid &= (get_line1[i+3] == LTR_S);
            b_valid &= (get_line2[i+2] == LTR_A);
            b_valid &= (get_line3[i+1] == LTR_M);
            b_valid &= (get_line4[i] == LTR_X);

            if (b_valid)
            {
                count++;
            }
        }  

        /* Update lines for next vertical checking */
        strcpy(get_line1, get_line2);
        strcpy(get_line2, get_line3);
        strcpy(get_line3, get_line4);
    }
    
    printf("\nTotal count DL: %d", count);

    /* Reset file pointer before returning */
    rewind(file);


    /* Free up allocated memory */
    free(get_line1);
    free(get_line2);
    free(get_line3);
    free(get_line4);

    return count;
}


int main(void)
{
    uint32_t total_count = 0x0;

    FILE *file = fopen("../input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    /* Scan horizontal */
    total_count += scan_horizontal(file);
    total_count += scan_vertical(file);
    total_count += scan_diagonal_right(file);
    total_count += scan_diagonal_left(file);

    fclose(file);
    printf("\n\nOverall Count = %d", total_count);

    return 0;
}
