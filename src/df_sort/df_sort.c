/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Sort dataframe rows based on a column
*/

#include "dataframe.h"
#include <stdbool.h>

static int validate_sort_inputs(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2), int *column_idx)
{
    if (!dataframe || !column || !sort_func)
        return -1;
    *column_idx = find_column_index(dataframe, column);
    if (*column_idx < 0)
        return -1;
    return 0;
}

static dataframe_t *prepare_sorted_dataframe(dataframe_t *dataframe)
{
    dataframe_t *new_df;

    new_df = create_empty_dataframe(dataframe);
    if (!new_df)
        return NULL;
    if (df_copy_column_metadata(new_df, dataframe) != 0) {
        df_free(new_df);
        return NULL;
    }
    return new_df;
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    int column_idx;
    dataframe_t *sorted_df;
    sort_pair_t *pairs = NULL;

    if (validate_sort_inputs(dataframe, column, sort_func, &column_idx) != 0 ||
        prepare_sort_pairs(dataframe, column_idx, &pairs) != 0)
        return NULL;
    sort_row_pairs(pairs, dataframe->nb_rows, sort_func);
    sorted_df = prepare_sorted_dataframe(dataframe);
    if (!sorted_df) {
        free(pairs);
        return NULL;
    }
    if (copy_data_in_sorted_order(sorted_df, dataframe, pairs) != 0) {
        df_free(sorted_df);
        free(pairs);
        return NULL;
    }
    free(pairs);
    return sorted_df;
}
