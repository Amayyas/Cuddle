/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** float_conversions
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *convert_float_to_string(void *value)
{
    float *num = (float *)value;
    char *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(char) * 32);
    if (!result)
        return NULL;
    snprintf(result, 32, "%.2f", *num);
    return result;
}

void *convert_float_to_int(void *value)
{
    float *num = (float *)value;
    int *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(int));
    if (!result)
        return NULL;
    *result = (int)(*num);
    return result;
}

void *convert_float_to_bool(void *value)
{
    float *num = (float *)value;
    bool *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(bool));
    if (!result)
        return NULL;
    *result = *num != 0.0f;
    return result;
}
