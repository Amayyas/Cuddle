/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_data_copy
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <stdlib.h>

bool copy_cell_data(dataframe_t *dest_df, dataframe_t *src_df,
    position_t *position, column_type_t new_type)
{
    void *converted_value;
    column_type_t src_type = src_df->columns[position->col].type;

    if (position->col == position->target_col) {
        converted_value = process_value_conversion(
            src_df->columns[position->col].data[position->row],
            src_type, new_type);
    } else {
        converted_value = df_copy_value(
            src_df->columns[position->col].data[position->row], src_type);
    }
    dest_df->columns[position->col].data[position->row] = converted_value;
    return (converted_value != NULL);
}

bool copy_row_data(dataframe_t *dest_df, dataframe_t *src_df,
    position_t *position, column_type_t new_type)
{
    position_t cell_position;

    cell_position.row = position->row;
    cell_position.target_col = position->target_col;
    for (int col = 0; col < src_df->nb_columns; col++) {
        cell_position.col = col;
        if (!copy_cell_data(dest_df, src_df, &cell_position, new_type)) {
            return false;
        }
    }
    return true;
}

bool copy_all_data(dataframe_t *result_df, dataframe_t *src_df,
    int target_col_idx, column_type_t new_type)
{
    position_t position;

    position.target_col = target_col_idx;
    for (int row = 0; row < src_df->nb_rows; row++) {
        position.row = row;
        if (!copy_row_data(result_df, src_df, &position, new_type)) {
            return false;
        }
    }
    return true;
}
