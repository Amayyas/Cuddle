/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_create_converted
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>

dataframe_t *create_converted_dataframe(dataframe_t *src_df,
    int target_col_idx, column_type_t new_type)
{
    dataframe_t *result_df;

    result_df = create_empty_result_df(src_df);
    if (!result_df)
        return NULL;
    if (!allocate_df_columns(result_df)) {
        cleanup_partial_df(result_df);
        return NULL;
    }
    if (!init_column_metadata(result_df, src_df, target_col_idx, new_type)) {
        df_free(result_df);
        return NULL;
    }
    if (!copy_all_data(result_df, src_df, target_col_idx, new_type)) {
        df_free(result_df);
        return NULL;
    }
    return result_df;
}
