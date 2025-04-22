#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

#define MAX_CHAR (70)

//Create linklist sctructure
typedef struct Node {
    int data;
    struct Node *next;
} Node;


int main(void)
{
    /****** Read input.txt ******/
    FILE *file = fopen("../input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    /****** Initialize linked list ******/
    Node base = {.data=0, .next=NULL};
    Node *head = &base;

    // If number does not exist, create node and append.
    // If number exists, insert node after number

    /* Extract Page rules */
    char *get_line = (char *)malloc((MAX_CHAR) * sizeof(char));
    while (fgets(get_line, MAX_CHAR, file) != NULL)
    {
        /* Check for empty line - end of Page rules */
        if (strlen(get_line) <= 1)
        {
            break;
        }
        printf("%s", get_line);
    }

    /* Extract Page updates */
    printf("\n\nPAGE UPDATES\n\n");
    while (fgets(get_line, MAX_CHAR, file) != NULL)
    {
        printf("%s", get_line);
    }
    fclose(file);

    return 0;
}

