/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Helper functions for dataframe value retrieval utilities
*/

#include "dataframe.h"
#include <stdbool.h>

int get_column_idx(dataframe_t *dataframe, const char *column)
{
    if (!dataframe || !column)
        return -1;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->columns[i].name, column) == 0)
            return i;
    }
    return -1;
}

bool is_value_in_array(void **array, void *value, int count,
    column_type_t type)
{
    for (int i = 0; i < count; i++) {
        if (!array[i] || !value)
            continue;
        if (type == INT && *(int *)array[i] == *(int *)value)
            return true;
        if (type == FLOAT && *(float *)array[i] == *(float *)value)
            return true;
        if (type == BOOL && *(bool *)array[i] == *(bool *)value)
            return true;
        if (type == STRING && strcmp((char *)array[i], (char *)value) == 0)
            return true;
    }
    return false;
}

void *copy_int_value(void *value)
{
    int *int_copy;

    if (!value)
        return NULL;
    int_copy = malloc(sizeof(int));
    if (!int_copy)
        return NULL;
    *int_copy = *(int *)value;
    return int_copy;
}

void **allocate_unique_values(dataframe_t *dataframe)
{
    void **unique_values;

    unique_values = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
    if (!unique_values)
        return NULL;
    return unique_values;
}

void process_unique_values(dataframe_t *dataframe, void **unique_values,
    int column_idx, int *unique_count)
{
    void *value;
    column_type_t type = dataframe->columns[column_idx].type;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        value = dataframe->columns[column_idx].data[i];
        if (!is_value_in_array(unique_values, value, *unique_count, type)) {
            unique_values[*unique_count] = copy_value_for_unique(value, type);
            (*unique_count)++;
        }
    }
    unique_values[*unique_count] = NULL;
}
