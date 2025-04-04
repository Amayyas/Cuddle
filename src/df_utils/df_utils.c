/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Utility functions for retrieving values from a dataframe
*/

#include "dataframe.h"
#include <stdbool.h>

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int column_idx;

    if (!dataframe || row < 0 || row >= dataframe->nb_rows || !column)
        return NULL;
    column_idx = get_column_idx(dataframe, column);
    if (column_idx == -1)
        return NULL;
    return dataframe->columns[column_idx].data[row];
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int column_idx;
    void **values;

    if (!dataframe || !column)
        return NULL;
    column_idx = get_column_idx(dataframe, column);
    if (column_idx == -1)
        return NULL;
    values = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
    if (!values)
        return NULL;
    for (int i = 0; i < dataframe->nb_rows; i++)
        values[i] = dataframe->columns[column_idx].data[i];
    values[dataframe->nb_rows] = NULL;
    return values;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    int column_idx;
    void **unique_values;
    int unique_count = 0;

    if (!dataframe || !column)
        return NULL;
    column_idx = get_column_idx(dataframe, column);
    if (column_idx == -1)
        return NULL;
    unique_values = allocate_unique_values(dataframe);
    if (!unique_values)
        return NULL;
    process_unique_values(dataframe, unique_values,
        column_idx, &unique_count);
    return unique_values;
}
