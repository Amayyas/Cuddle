/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Utility functions for dataframe sorting
*/

#include "dataframe.h"
#include <stdbool.h>

int find_column_index(dataframe_t *dataframe, const char *column_name)
{
    if (!dataframe || !column_name)
        return -1;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->columns[i].name, column_name) == 0)
            return i;
    }
    return -1;
}

int prepare_sort_pairs(dataframe_t *dataframe, int column_idx,
    sort_pair_t **pairs)
{
    *pairs = malloc(sizeof(sort_pair_t) * dataframe->nb_rows);
    if (!*pairs)
        return -1;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        (*pairs)[i].row_idx = i;
        (*pairs)[i].value = dataframe->columns[column_idx].data[i];
    }
    return 0;
}

static bool should_swap_pairs(sort_pair_t *pairs, int j,
    bool (*sort_func)(void *value1, void *value2))
{
    return sort_func(pairs[j].value, pairs[j + 1].value);
}

static void swap_pairs(sort_pair_t *pairs, int j)
{
    sort_pair_t temp;

    temp = pairs[j];
    pairs[j] = pairs[j + 1];
    pairs[j + 1] = temp;
}

static void compare_and_swap_pairs(sort_pair_t *pairs, int j,
    bool (*sort_func)(void *value1, void *value2))
{
    if (should_swap_pairs(pairs, j, sort_func))
        swap_pairs(pairs, j);
}

void sort_row_pairs(sort_pair_t *pairs, int nb_rows,
    bool (*sort_func)(void *value1, void *value2))
{
    for (int i = 0; i < nb_rows - 1; i++) {
        for (int j = 0; j < nb_rows - i - 1; j++) {
            compare_and_swap_pairs(pairs, j, sort_func);
        }
    }
}

dataframe_t *create_empty_dataframe(dataframe_t *dataframe)
{
    dataframe_t *new_df;

    new_df = malloc(sizeof(dataframe_t));
    if (!new_df)
        return NULL;
    new_df->nb_rows = dataframe->nb_rows;
    new_df->nb_columns = dataframe->nb_columns;
    new_df->columns = malloc(sizeof(column_t) * dataframe->nb_columns);
    if (!new_df->columns) {
        free(new_df);
        return NULL;
    }
    new_df->separator = strdup(dataframe->separator);
    if (!new_df->separator) {
        free(new_df->columns);
        free(new_df);
        return NULL;
    }
    return new_df;
}

int copy_data_in_sorted_order(dataframe_t *new_df,
    dataframe_t *dataframe, sort_pair_t *pairs)
{
    void *src_data;
    column_type_t type;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        for (int col = 0; col < dataframe->nb_columns; col++) {
            src_data = dataframe->columns[col].data[pairs[i].row_idx];
            type = dataframe->columns[col].type;
            new_df->columns[col].data[i] = df_copy_value(src_data, type);
        }
    }
    return 0;
}
