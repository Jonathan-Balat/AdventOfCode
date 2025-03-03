
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


uint32_t *remove_array_element(uint32_t *list, uint32_t size, uint32_t index);
void clear_array(uint32_t *list, uint32_t size);
void sort_ascending(uint32_t *list, uint32_t size);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
FILE *get_input_data(char *filename);


#endif // __COMMON_H__
