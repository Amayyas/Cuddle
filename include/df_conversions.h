/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_conversions header
*/

#ifndef DF_CONVERSIONS_H
    #define DF_CONVERSIONS_H
    #define MAX_TYPE (STRING + 1)
    #include "dataframe.h"
    #include <stddef.h>
    #include <stdbool.h>

typedef struct position_s {
    int row;
    int col;
    int target_col;
} position_t;

typedef void *(*type_converter_t)(void *value);
void *allocate_typed_memory(size_t size);
void *convert_string_to_int(void *value);
void *convert_string_to_float(void *value);
void *convert_string_to_bool(void *value);
void *convert_int_to_string(void *value);
void *convert_int_to_float(void *value);
void *convert_int_to_bool(void *value);
void *convert_float_to_string(void *value);
void *convert_float_to_int(void *value);
void *convert_float_to_bool(void *value);
void *convert_bool_to_string(void *value);
void *convert_bool_to_int(void *value);
void *convert_bool_to_float(void *value);
type_converter_t get_converter(column_type_t src_type, column_type_t dst_type);
int validate_column(dataframe_t *dataframe, const char *column_name);
bool is_valid_type(column_type_t type);
int validate_to_type_inputs(dataframe_t *dataframe, const char *column,
    column_type_t downcast);
column_t create_converted_column(column_t *src_column, column_type_t new_type);
bool allocate_column_data(column_t *column, int num_rows);
void *process_value_conversion(void *src_data, column_type_t src_type,
    column_type_t dst_type);
dataframe_t *create_empty_result_df(dataframe_t *src_df);
bool allocate_df_columns(dataframe_t *df);
void cleanup_partial_df(dataframe_t *df);
bool init_column_metadata(dataframe_t *result_df, dataframe_t *src_df,
    int target_col_idx, column_type_t new_type);
bool copy_cell_data(dataframe_t *dest_df, dataframe_t *src_df,
    position_t *position, column_type_t new_type);
bool copy_row_data(dataframe_t *dest_df, dataframe_t *src_df,
    position_t *position, column_type_t new_type);
bool copy_all_data(dataframe_t *result_df, dataframe_t *src_df,
    int target_col_idx, column_type_t new_type);
dataframe_t *create_converted_dataframe(dataframe_t *src_df,
    int target_col_idx, column_type_t new_type);

#endif /* DF_CONVERSIONS_H */
