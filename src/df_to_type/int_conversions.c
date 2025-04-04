/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** int_conversions
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *convert_int_to_string(void *value)
{
    int *num = (int *)value;
    char *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(char) * 12);
    if (!result)
        return NULL;
    snprintf(result, 12, "%d", *num);
    return result;
}

void *convert_int_to_float(void *value)
{
    int *num = (int *)value;
    float *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(float));
    if (!result)
        return NULL;
    *result = (float)(*num);
    return result;
}

void *convert_int_to_bool(void *value)
{
    int *num = (int *)value;
    bool *result = NULL;

    if (!num)
        return NULL;
    result = allocate_typed_memory(sizeof(bool));
    if (!result)
        return NULL;
    *result = *num != 0;
    return result;
}
