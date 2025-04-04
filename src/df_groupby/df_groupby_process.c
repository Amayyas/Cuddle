/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby process functions
*/

#include <stdlib.h>
#include "dataframe.h"
#include "df_groupby.h"

void set_result_key(dataframe_t *result, group_array_t *groups)
{
    int i;

    for (i = 0; i < groups->size; i++)
        result->columns[0].data[i] = groups->items[i]->key;
}

void process_column(dataframe_t *result, group_array_t *groups,
    int col_idx, void *(*agg_func)(void **values, int count))
{
    int i;

    for (i = 0; i < groups->size; i++) {
        result->columns[col_idx].data[i] =
            agg_func(groups->items[i]->values, groups->items[i]->count);
    }
}

dataframe_t *process_groups(group_array_t *groups, dataframe_t *result,
    dataframe_t *source, void *(*agg_func)(void **values, int count))
{
    int i;

    if (!groups || !result || !source || !agg_func)
        return NULL;
    set_result_key(result, groups);
    for (i = 1; i < result->nb_columns; i++)
        process_column(result, groups, i, agg_func);
    return result;
}

dataframe_t *perform_groupby(dataframe_t *dataframe,
    const char *aggregate_by, const char **to_aggregate,
    void *(*agg_func)(void **values, int count))
{
    group_array_t *groups = create_groups(dataframe, aggregate_by);
    dataframe_t *result;

    if (!groups)
        return NULL;
    result = prepare_groupby_result(dataframe, aggregate_by,
        to_aggregate, groups->size);
    if (!result) {
        free_groups(groups);
        return NULL;
    }
    if (!populate_all_columns(groups, dataframe, aggregate_by, to_aggregate)) {
        cleanup_groupby_resources(result, groups);
        return NULL;
    }
    result = process_groups(groups, result, dataframe, agg_func);
    free_groups(groups);
    return result;
}
