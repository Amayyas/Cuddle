/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Dataframe groupby header file
*/

#ifndef INCLUDED_DF_GROUPBY_H
    #define INCLUDED_DF_GROUPBY_H

    #include "dataframe.h"
typedef struct group_item_s {
    void *key;
    void **values;
    int count;
} group_item_t;

typedef struct group_array_s {
    group_item_t **items;
    int size;
    int capacity;
} group_array_t;

typedef struct agg_context_s {
    dataframe_t *src_df;
    dataframe_t *result_df;
    const char *key_column;
    const char **agg_columns;
    void *(*agg_func)(void **values, int count);
} agg_context_t;

group_array_t *create_empty_groups(int initial_capacity);
group_array_t *create_groups(dataframe_t *dataframe, const char *key_column);
int add_group(group_array_t *groups, void *key);
int add_to_group(group_array_t *groups, int index, void *value);
void free_groups(group_array_t *groups);
int find_group_index(group_array_t *groups, void *key, column_type_t type);
int populate_groups(group_array_t *groups, dataframe_t *dataframe,
    const char *key_column, const char *value_column);
int populate_all_columns(group_array_t *groups, dataframe_t *dataframe,
    const char *key_column, const char **value_columns);
int compare_by_type(void *a, void *b, column_type_t type);
dataframe_t *prepare_groupby_result(dataframe_t *dataframe,
    const char *key_column, const char **agg_columns, int group_count);
int init_key_column(dataframe_t *result, dataframe_t *source,
    const char *key_column);
int init_agg_columns(dataframe_t *result, dataframe_t *source,
    const char **agg_columns);
void cleanup_groupby_resources(dataframe_t *result, group_array_t *groups);
int count_aggregate_columns(const char **agg_columns);
dataframe_t *create_result_df(int nb_rows, int nb_columns);
void free_dataframe_columns(dataframe_t *df);
void free_dataframe(dataframe_t *df);
void *df_count_agg(void **values, int count);
void set_result_key(dataframe_t *result, group_array_t *groups);
void process_column(dataframe_t *result, group_array_t *groups,
    int col_idx, void *(*agg_func)(void **values, int count));
dataframe_t *process_groups(group_array_t *groups, dataframe_t *result,
    dataframe_t *source, void *(*agg_func)(void **values, int count));
dataframe_t *perform_groupby(dataframe_t *dataframe,
    const char *aggregate_by, const char **to_aggregate,
    void *(*agg_func)(void **values, int count));

#endif /* !INCLUDED_DF_GROUPBY_H */
