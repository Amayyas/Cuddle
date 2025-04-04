/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Functions for copying dataframe values
*/

#include "dataframe.h"
#include <stdbool.h>

static void *copy_uint_value(unsigned int *src_data)
{
    unsigned int *value = malloc(sizeof(unsigned int));

    if (value)
        *value = *src_data;
    return value;
}

void *df_copy_value(void *src_data, column_type_t type)
{
    if (!src_data)
        return NULL;
    if (type == BOOL)
        return copy_bool_value(src_data);
    if (type == INT)
        return copy_int_value(src_data);
    if (type == UINT)
        return copy_uint_value(src_data);
    if (type == FLOAT)
        return copy_float_value(src_data);
    if (type == STRING)
        return src_data ? strdup((char *)src_data) : NULL;
    return NULL;
}

static int is_valid_src_data(cell_info_t *info)
{
    return info->src_row >= 0 &&
        info->src_row < info->src->nb_rows &&
        info->src->columns[info->col].data &&
        info->src->columns[info->col].data[info->src_row];
}

static int df_copy_cell(cell_info_t *info)
{
    void *value = NULL;
    void *src_data = NULL;
    column_type_t type = info->src->columns[info->col].type;

    if (!is_valid_src_data(info)) {
        info->dest->columns[info->col].data[info->dest_row] = NULL;
        return 0;
    }
    src_data = info->src->columns[info->col].data[info->src_row];
    value = df_copy_value(src_data, type);
    if (!value && src_data && type != UNDEFINED)
        return 84;
    info->dest->columns[info->col].data[info->dest_row] = value;
    return 0;
}

static int df_copy_column(dataframe_t *dest, dataframe_t *src,
    int start_row, int col)
{
    cell_info_t info = {src, dest, 0, 0, col};
    int result = 0;

    for (int dest_row = 0; dest_row < dest->nb_rows; dest_row++) {
        info.dest_row = dest_row;
        info.src_row = start_row + dest_row;
        result = df_copy_cell(&info);
        if (result != 0)
            return result;
    }
    return 0;
}

int df_copy_data(dataframe_t *dest, dataframe_t *src, int start_row)
{
    int result = 0;

    for (int col = 0; col < src->nb_columns; col++) {
        result = df_copy_column(dest, src, start_row, col);
        if (result != 0)
            return result;
    }
    return 0;
}
