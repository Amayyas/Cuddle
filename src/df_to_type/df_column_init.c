/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_column_init
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>

bool init_column_metadata(dataframe_t *result_df, dataframe_t *src_df,
    int target_col_idx, column_type_t new_type)
{
    for (int i = 0; i < src_df->nb_columns; i++) {
        if (i == target_col_idx)
            result_df->columns[i] = create_converted_column(
                &src_df->columns[i], new_type);
        else
            result_df->columns[i] = create_converted_column(
                &src_df->columns[i], src_df->columns[i].type);
        if (!allocate_column_data(&result_df->columns[i], src_df->nb_rows))
            return false;
    }
    return true;
}
