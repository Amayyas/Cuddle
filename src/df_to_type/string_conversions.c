/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** string_conversions
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void *convert_string_to_int(void *value)
{
    const char *str = (char *)value;
    int *result = NULL;

    if (!str)
        return NULL;
    result = allocate_typed_memory(sizeof(int));
    if (!result)
        return NULL;
    *result = atoi(str);
    return result;
}

void *convert_string_to_float(void *value)
{
    const char *str = (char *)value;
    float *result = NULL;

    if (!str)
        return NULL;
    result = allocate_typed_memory(sizeof(float));
    if (!result)
        return NULL;
    *result = atof(str);
    return result;
}

void *convert_string_to_bool(void *value)
{
    const char *str = (char *)value;
    bool *result = NULL;

    if (!str)
        return NULL;
    result = allocate_typed_memory(sizeof(bool));
    if (!result)
        return NULL;
    *result = (strcasecmp(str, "true") == 0 ||
    strcmp(str, "1") == 0 ||
    strcasecmp(str, "yes") == 0 ||
    strcasecmp(str, "y") == 0);
    return result;
}
