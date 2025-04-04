/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Filter dataframe rows based on a condition
*/

#include "dataframe.h"
#include <stdbool.h>


static int count_matching_rows(dataframe_t *dataframe, int column_idx,
    bool (*filter_func)(void *value))
{
    int count = 0;
    void *value;

    if (!dataframe || column_idx < 0 || !filter_func)
        return 0;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        value = dataframe->columns[column_idx].data[i];
        if (value && filter_func(value))
            count++;
    }
    return count;
}

static dataframe_t *allocate_filtered_dataframe(dataframe_t *dataframe,
    int matching_rows)
{
    dataframe_t *filtered;

    filtered = malloc(sizeof(dataframe_t));
    if (!filtered)
        return NULL;
    filtered->nb_rows = matching_rows;
    filtered->nb_columns = dataframe->nb_columns;
    filtered->columns = malloc(sizeof(column_t) * dataframe->nb_columns);
    if (!filtered->columns) {
        free(filtered);
        return NULL;
    }
    return filtered;
}

static int copy_row_data(dataframe_t *filtered, dataframe_t *dataframe,
    int filtered_row, int src_row)
{
    void *src_data;
    column_type_t type;

    for (int col = 0; col < dataframe->nb_columns; col++) {
        src_data = dataframe->columns[col].data[src_row];
        type = dataframe->columns[col].type;
        filtered->columns[col].data[filtered_row] =
        df_copy_value(src_data, type);
    }
    return 0;
}

static int copy_filtered_rows(dataframe_t *filtered, dataframe_t *dataframe,
    int column_idx, bool (*filter_func)(void *value))
{
    int filtered_row = 0;
    void *value;

    filtered->separator = strdup(dataframe->separator);
    for (int src_row = 0; src_row < dataframe->nb_rows; src_row++) {
        value = dataframe->columns[column_idx].data[src_row];
        if (value && filter_func(value)) {
            copy_row_data(filtered, dataframe, filtered_row, src_row);
            filtered_row++;
        }
    }
    return 0;
}

static int validate_filter_inputs(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value), int *column_idx)
{
    if (!dataframe || !column || !filter_func)
        return -1;
    *column_idx = find_column_index(dataframe, column);
    if (*column_idx < 0)
        return -1;
    return 0;
}

static dataframe_t *prepare_filtered_dataframe(dataframe_t *dataframe,
    int column_idx, bool (*filter_func)(void *value))
{
    int matching_rows;
    dataframe_t *filtered;

    matching_rows = count_matching_rows(dataframe, column_idx, filter_func);
    if (matching_rows == 0)
        return NULL;
    filtered = allocate_filtered_dataframe(dataframe, matching_rows);
    if (!filtered)
        return NULL;
    if (df_copy_column_metadata(filtered, dataframe) != 0) {
        df_free(filtered);
        return NULL;
    }
    return filtered;
}

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value))
{
    int column_idx;
    dataframe_t *filtered;

    if (validate_filter_inputs(dataframe,
        column, filter_func, &column_idx) != 0)
        return NULL;
    filtered = prepare_filtered_dataframe(dataframe, column_idx, filter_func);
    if (!filtered)
        return NULL;
    if (copy_filtered_rows(filtered, dataframe,
        column_idx, filter_func) != 0) {
        df_free(filtered);
        return NULL;
    }
    return filtered;
}
