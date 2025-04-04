/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** bool_conversions
*/


#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void *convert_bool_to_string(void *value)
{
    bool *b = (bool *)value;
    char *result = NULL;

    if (!b)
        return NULL;
    result = strdup(*b ? "true" : "false");
    return result;
}

void *convert_bool_to_int(void *value)
{
    bool *b = (bool *)value;
    int *result = NULL;

    if (!b)
        return NULL;
    result = allocate_typed_memory(sizeof(int));
    if (!result)
        return NULL;
    *result = *b ? 1 : 0;
    return result;
}

void *convert_bool_to_float(void *value)
{
    bool *b = (bool *)value;
    float *result = NULL;

    if (!b)
        return NULL;
    result = allocate_typed_memory(sizeof(float));
    if (!result)
        return NULL;
    *result = *b ? 1.0f : 0.0f;
    return result;
}
