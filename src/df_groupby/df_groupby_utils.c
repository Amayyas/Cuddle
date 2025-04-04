/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby utility functions
*/

#include <stdlib.h>
#include <string.h>
#include "dataframe.h"
#include "df_groupby.h"

int count_aggregate_columns(const char **agg_columns)
{
    int count = 0;

    if (!agg_columns)
        return 0;
    while (agg_columns[count])
        count++;
    return count;
}

dataframe_t *create_result_df(int nb_rows, int nb_columns)
{
    dataframe_t *result = malloc(sizeof(dataframe_t));

    if (!result)
        return NULL;
    result->nb_rows = nb_rows;
    result->nb_columns = nb_columns;
    result->separator = NULL;
    result->columns = malloc(sizeof(column_t) * nb_columns);
    if (!result->columns) {
        free(result);
        return NULL;
    }
    return result;
}

int init_key_column(dataframe_t *result, dataframe_t *source,
    const char *key_column)
{
    int key_col_idx = get_column_idx(source, key_column);

    if (key_col_idx == -1)
        return 0;
    if (source->separator)
        result->separator = strdup(source->separator);
    result->columns[0].type = source->columns[key_col_idx].type;
    result->columns[0].name = strdup(source->columns[key_col_idx].name);
    result->columns[0].data = malloc(sizeof(void *) * result->nb_rows);
    if (!result->columns[0].data || !result->columns[0].name)
        return 0;
    return 1;
}

int init_agg_columns(dataframe_t *result, dataframe_t *source,
    const char **agg_columns)
{
    int i;
    int agg_col_idx;

    for (i = 0; agg_columns[i]; i++) {
        agg_col_idx = get_column_idx(source, agg_columns[i]);
        if (agg_col_idx == -1)
            return 0;
        result->columns[i + 1].type = source->columns[agg_col_idx].type;
        result->columns[i + 1].name = strdup(
            source->columns[agg_col_idx].name);
        result->columns[i + 1].data = malloc(sizeof(void *) * result->nb_rows);
        if (!result->columns[i + 1].data || !result->columns[i + 1].name)
            return 0;
    }
    return 1;
}

dataframe_t *prepare_groupby_result(dataframe_t *dataframe,
    const char *key_column, const char **agg_columns, int group_count)
{
    int num_agg_cols = count_aggregate_columns(agg_columns);
    dataframe_t *result;

    if (!num_agg_cols)
        return NULL;
    result = create_result_df(group_count, num_agg_cols + 1);
    if (!result)
        return NULL;
    if (!init_key_column(result, dataframe, key_column)) {
        free(result->columns);
        free(result);
        return NULL;
    }
    if (!init_agg_columns(result, dataframe, agg_columns)) {
        free(result->columns);
        free(result);
        return NULL;
    }
    return result;
}
