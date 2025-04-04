/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Main groupby function implementation
*/

#include <stdlib.h>
#include "dataframe.h"
#include "df_groupby.h"

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate,
    void *(*agg_func)(void **values, int nb_values))
{
    if (!dataframe || !aggregate_by || !to_aggregate || !agg_func)
        return NULL;
    return perform_groupby(dataframe, aggregate_by, to_aggregate, agg_func);
}
