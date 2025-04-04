/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby cleanup functions
*/

#include <stdlib.h>
#include "dataframe.h"
#include "df_groupby.h"

static void free_group_item(group_item_t *item)
{
    if (!item)
        return;
    if (item->values)
        free(item->values);
    free(item);
}

void free_groups(group_array_t *groups)
{
    int i;

    if (!groups)
        return;
    if (groups->items) {
        for (i = 0; i < groups->size; i++)
            free_group_item(groups->items[i]);
        free(groups->items);
    }
    free(groups);
}

void free_dataframe_columns(dataframe_t *df)
{
    int i;

    if (!df || !df->columns)
        return;
    for (i = 0; i < df->nb_columns; i++) {
        if (df->columns[i].data)
            free(df->columns[i].data);
        if (df->columns[i].name)
            free(df->columns[i].name);
    }
    free(df->columns);
}

void free_dataframe(dataframe_t *df)
{
    if (!df)
        return;
    free_dataframe_columns(df);
    if (df->separator)
        free(df->separator);
    free(df);
}

void cleanup_groupby_resources(dataframe_t *result, group_array_t *groups)
{
    free_dataframe(result);
    free_groups(groups);
}
