/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby result functions
*/

#include <stdlib.h>
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
    result->columns = malloc(sizeof(column_t) * nb_columns);
    if (!result->columns) {
        free(result);
        return NULL;
    }
    return result;
}

int init_result_columns(dataframe_t *result, dataframe_t *source,
    const char *key_column, const char **agg_columns)
{
    int key_col_idx = get_column_idx(source, key_column);
    int i;
    int agg_col_idx;

    if (key_col_idx == -1)
        return 0;
    result->columns[0] = source->columns[key_col_idx];
    result->columns[0].data = malloc(sizeof(void *) * result->nb_rows);
    if (!result->columns[0].data)
        return 0;
    for (i = 0; agg_columns[i]; i++) {
        agg_col_idx = get_column_idx(source, agg_columns[i]);
        if (agg_col_idx == -1)
            return 0;
        result->columns[i + 1] = source->columns[agg_col_idx];
        result->columns[i + 1].data = malloc(sizeof(void *) * result->nb_rows);
        if (!result->columns[i + 1].data)
            return 0;
    }
    return 1;
}
