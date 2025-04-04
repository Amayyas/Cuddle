/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_validation
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>

int validate_column(dataframe_t *dataframe, const char *column_name)
{
    int col_idx;

    if (!dataframe || !column_name)
        return -1;
    col_idx = find_column_index(dataframe, column_name);
    return col_idx;
}

bool is_valid_type(column_type_t type)
{
    return (type >= BOOL && type <= STRING);
}

int validate_to_type_inputs(dataframe_t *dataframe, const char *column,
    column_type_t downcast)
{
    int col_idx;

    if (!dataframe || !column || !is_valid_type(downcast))
        return -1;
    col_idx = validate_column(dataframe, column);
    return col_idx;
}
