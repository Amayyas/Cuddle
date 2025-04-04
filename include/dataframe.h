/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe
*/

#ifndef INCLUDED_DATAFRAME_H
    #define INCLUDED_DATAFRAME_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <sys/types.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED // only used internally before the type is determined
} column_type_t;

typedef struct column_s {
    char *name;
    column_type_t type;
    void **data;
} column_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    column_t *columns;
    char *separator;
} dataframe_t;

typedef struct {
    dataframe_t *src;
    dataframe_t *dest;
    int src_row;
    int dest_row;
    int col;
} cell_info_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct {
    int row_idx;
    void *value;
} sort_pair_t;

typedef struct {
    int row;
    int col;
    int target_col;
} cell_position_t;

// Read CSV functions
dataframe_t *df_read_csv(const char *filename, const char *separator);
column_t *allocate_columns(const char *filename, const char *separator);
int df_parse_store_data(dataframe_t *dataframe, const char *filename,
    const char *separator);
void df_free(dataframe_t *dataframe);
int df_write_csv(const dataframe_t *dataframe, const char *filename);
void df_print_csv(const dataframe_t *dataframe);

// String utility functions
char *clean_token(const char *token);
char *duplicate_line(const char *line);

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);

// Type handling functions
int handle_bool(const char *token, int *return_value);
int handle_float(const char *token, int *return_value);
int handle_int(const char *token, int *return_value);
column_type_t get_column_type(const char *token);
void update_column_type(column_t *column, column_type_t new_type);

// Data conversion functions
void *convert_bool(const char *token);
void *convert_int(const char *token);
void *convert_uint(const char *token);
void *convert_float(const char *token);
void *convert_string(const char *token);
void *convert_token(const char *token, column_type_t type);

// Memory handling functions
int allocate_data_arrays(dataframe_t *dataframe);
void initialize_column_types(dataframe_t *dataframe);
void finalize_column_types(dataframe_t *dataframe);

// Parsing helper functions
int process_token_for_type(dataframe_t *dataframe,
    const char *token, int col);
int process_line_for_types(dataframe_t *dataframe,
    char *line, const char *separator);
int store_token_data(dataframe_t *dataframe,
    const char *token, int row, int col);
int process_line_for_data(dataframe_t *dataframe,
    char *line, const char *separator, int row);

/* Common dataframe copy functions */
dataframe_t *df_create_subset(dataframe_t *dataframe,
    int start_row, int nb_rows);
int df_copy_column_metadata(dataframe_t *dest, dataframe_t *src);
void *df_copy_value(void *src_data, column_type_t type);
int df_copy_data(dataframe_t *dest, dataframe_t *src, int start_row);
dataframe_shape_t df_shape(dataframe_t *dataframe);

void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);

// Filter function
dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value));

// Sort functions
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2));

// Sort utility functions
int find_column_index(dataframe_t *dataframe, const char *column_name);
int prepare_sort_pairs(dataframe_t *dataframe, int column_idx,
    sort_pair_t **pairs);
void sort_row_pairs(sort_pair_t *pairs, int nb_rows,
    bool (*sort_func)(void *value1, void *value2));
dataframe_t *create_empty_dataframe(dataframe_t *dataframe);
int copy_data_in_sorted_order(dataframe_t *new_df,
    dataframe_t *dataframe, sort_pair_t *pairs);

// Apply function
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value));

// Type conversion function
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);

// Type conversion utility functions
void *convert_string_to_int(void *value);
void *convert_string_to_float(void *value);
void *convert_string_to_bool(void *value);
void *convert_int_to_string(void *value);
void *convert_float_to_string(void *value);
void *convert_bool_to_string(void *value);
void *convert_value(void *src_data, column_type_t src_type,
    column_type_t dst_type);

// Value retrieval utility functions
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);

// Value retrieval helper functions
int get_column_idx(dataframe_t *dataframe, const char *column);
bool is_value_in_array(void **array, void *value, int count,
    column_type_t type);
void *copy_int_value(void *value);
void *copy_float_value(void *value);
void *copy_bool_value(void *value);
void *copy_value_for_unique(void *value, column_type_t type);
void **allocate_unique_values(dataframe_t *dataframe);
void process_unique_values(dataframe_t *dataframe, void **unique_values,
    int column_idx, int *unique_count);

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate,
    void *(*agg_func)(void **values, int nb_values));

#endif /* !INCLUDED_DATAFRAME_H */
