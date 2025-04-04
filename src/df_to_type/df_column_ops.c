/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_column_ops
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <string.h>
#include <stdlib.h>

column_t create_converted_column(column_t *src_column, column_type_t new_type)
{
    column_t new_column;

    new_column.name = strdup(src_column->name);
    new_column.type = new_type;
    new_column.data = NULL;
    return new_column;
}

bool allocate_column_data(column_t *column, int num_rows)
{
    column->data = malloc(sizeof(void *) * num_rows);
    return (column->data != NULL);
}

void *process_value_conversion(void *src_data, column_type_t src_type,
    column_type_t dst_type)
{
    type_converter_t converter;

    if (!src_data || src_type == dst_type)
        return df_copy_value(src_data, src_type);
    converter = get_converter(src_type, dst_type);
    if (converter)
        return converter(src_data);
    return df_copy_value(src_data, src_type);
}
