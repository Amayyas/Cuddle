/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Common functions for creating dataframe subsets
*/

#include "dataframe.h"
#include <stdbool.h>

dataframe_t *df_create_subset(dataframe_t *dataframe,
    int start_row, int nb_rows)
{
    dataframe_t *subset = malloc(sizeof(dataframe_t));
    int max_available_rows = dataframe->nb_rows - start_row;
    int actual_rows = 0;

    if (!subset || start_row < 0 || start_row >= dataframe->nb_rows)
        return NULL;
    actual_rows = (max_available_rows < nb_rows) ?
        max_available_rows : nb_rows;
    subset->nb_rows = actual_rows;
    subset->nb_columns = dataframe->nb_columns;
    subset->columns = malloc(sizeof(column_t) * dataframe->nb_columns);
    subset->separator = strdup(dataframe->separator);
    if (!subset->separator || !subset->columns) {
        free(subset);
        return NULL;
    }
    return subset;
}

int df_copy_column_metadata(dataframe_t *dest, dataframe_t *src)
{
    for (int i = 0; i < src->nb_columns; i++) {
        dest->columns[i].name = strdup(src->columns[i].name);
        if (!dest->columns[i].name)
            return 84;
        dest->columns[i].type = src->columns[i].type;
        dest->columns[i].data = malloc(sizeof(void *) * dest->nb_rows);
        if (!dest->columns[i].data)
            return 84;
        for (int j = 0; j < dest->nb_rows; j++)
            dest->columns[i].data[j] = NULL;
    }
    return 0;
}
