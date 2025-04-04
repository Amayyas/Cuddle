/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Apply a function to transform a column in a dataframe
*/

#include "dataframe.h"
#include <stdbool.h>

static int validate_apply_inputs(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value), int *column_idx)
{
    if (!dataframe || !column || !apply_func)
        return -1;
    *column_idx = find_column_index(dataframe, column);
    if (*column_idx < 0)
        return -1;
    return 0;
}

static dataframe_t *prepare_applied_dataframe(dataframe_t *dataframe)
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

static void *process_cell_data(dataframe_t *dataframe, cell_position_t pos,
    void *(*apply_func)(void *value))
{
    void *src_data;
    void *result;
    column_type_t type;

    src_data = dataframe->columns[pos.col].data[pos.row];
    type = dataframe->columns[pos.col].type;
    if (pos.col == pos.target_col && src_data) {
        result = apply_func(src_data);
    } else {
        result = df_copy_value(src_data, type);
    }
    return result;
}

static int copy_data_with_transform(dataframe_t *new_df,
    dataframe_t *dataframe, int target_col,
    void *(*apply_func)(void *value))
{
    void *cell_data;
    cell_position_t pos;

    pos.target_col = target_col;
    for (int row = 0; row < dataframe->nb_rows; row++) {
        pos.row = row;
        for (int col = 0; col < dataframe->nb_columns; col++) {
            pos.col = col;
            cell_data = process_cell_data(dataframe, pos, apply_func);
            new_df->columns[col].data[row] = cell_data;
        }
    }
    return 0;
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    int column_idx;
    dataframe_t *applied_df;

    if (validate_apply_inputs(dataframe, column, apply_func, &column_idx) != 0)
        return NULL;
    applied_df = prepare_applied_dataframe(dataframe);
    if (!applied_df)
        return NULL;
    if (copy_data_with_transform(applied_df, dataframe,
        column_idx, apply_func) != 0) {
        df_free(applied_df);
        return NULL;
    }
    return applied_df;
}
