/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_to_type
*/

#include "dataframe.h"
#include "df_conversions.h"

dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast)
{
    int col_idx;
    dataframe_t *result;

    col_idx = validate_to_type_inputs(dataframe, column, downcast);
    if (col_idx < 0)
        return NULL;
    result = create_converted_dataframe(dataframe, col_idx, downcast);
    return result;
}
