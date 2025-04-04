/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_utils_functions
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>

void *copy_float_value(void *value)
{
    float *float_copy;

    if (!value)
        return NULL;
    float_copy = malloc(sizeof(float));
    if (!float_copy)
        return NULL;
    *float_copy = *(float *)value;
    return float_copy;
}

void *copy_bool_value(void *value)
{
    bool *bool_copy;

    if (!value)
        return NULL;
    bool_copy = malloc(sizeof(bool));
    if (!bool_copy)
        return NULL;
    *bool_copy = *(bool *)value;
    return bool_copy;
}

void *copy_value_for_unique(void *value, column_type_t type)
{
    if (!value)
        return NULL;
    if (type == INT)
        return copy_int_value(value);
    if (type == FLOAT)
        return copy_float_value(value);
    if (type == BOOL)
        return copy_bool_value(value);
    if (type == STRING)
        return strdup((char *)value);
    return NULL;
}
