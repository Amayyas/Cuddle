/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_converters_registry
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <stdbool.h>
#include <stdlib.h>

static const type_converter_t converters_table[MAX_TYPE][MAX_TYPE] = {
    [STRING] = {
        [INT] = convert_string_to_int,
        [FLOAT] = convert_string_to_float,
        [BOOL] = convert_string_to_bool
    },
    [INT] = {
        [STRING] = convert_int_to_string,
        [FLOAT] = convert_int_to_float,
        [BOOL] = convert_int_to_bool
    },
    [FLOAT] = {
        [STRING] = convert_float_to_string,
        [INT] = convert_float_to_int,
        [BOOL] = convert_float_to_bool
    },
    [BOOL] = {
        [STRING] = convert_bool_to_string,
        [INT] = convert_bool_to_int,
        [FLOAT] = convert_bool_to_float
    }
};

type_converter_t get_converter(column_type_t src_type, column_type_t dst_type)
{
    if (src_type >= MAX_TYPE || dst_type >= MAX_TYPE ||
        src_type < 0 || dst_type < 0)
        return NULL;
    if (src_type == dst_type)
        return NULL;
    return converters_table[src_type][dst_type];
}
