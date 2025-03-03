#include "common.h"
#include <assert.h>

uint32_t *remove_array_element(uint32_t *list, uint32_t size, uint32_t index)
{
    uint32_t idx = 0;

    /* Guard assertions */
    assert(index < size);

    /* Shift elements */
    for (idx = index+1; idx < size; idx++)
    {
       list[idx-1] = list[idx];
    }

    return list;
}

void clear_array(uint32_t *list, uint32_t size)
{
    for (uint32_t idx = 0; idx < size; idx++)
    {
        list[idx] = 0;
    }
}

int __compare(const void *a, const void *b)
{
    return (*(uint32_t *)a - *(uint32_t *)b);
}

void sort_ascending(uint32_t *list, uint32_t size)
{
    qsort(list, size, sizeof(uint32_t), __compare);
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    char *buf = *lineptr;
    size_t size = *n;
    int c = 0;
    size_t len = 0;

    if (buf == NULL || size == 0) {
        size = 128;
        buf = (char *)malloc(size);
        if (buf == NULL) {
            return -1;
        }
    }

    while ((c = fgetc(stream)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buf = (char *)realloc(buf, size);
            if (new_buf == NULL) {
                free(buf);
                return -1;
            }
            buf = new_buf;
        }
        buf[len++] = (char)c;
        if (c == '\n') {
            break;
        }
    }

    if (len == 0 && c == EOF) {
        return -1;
    }

    buf[len] = '\0';
    *lineptr = buf;
    *n = size;

    return len;
}

FILE *get_input_data(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    return file;
}
