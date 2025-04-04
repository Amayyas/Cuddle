/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby population functions
*/

#include <stdlib.h>
#include "dataframe.h"
#include "df_groupby.h"

int compare_by_type(void *a, void *b, column_type_t type)
{
    if (!a || !b)
        return 0;
    if (type == INT)
        return *(int *)a == *(int *)b;
    if (type == FLOAT)
        return *(float *)a == *(float *)b;
    if (type == STRING)
        return strcmp((char *)a, (char *)b) == 0;
    if (type == BOOL)
        return *(bool *)a == *(bool *)b;
    return 0;
}

int find_group_index(group_array_t *groups, void *key, column_type_t type)
{
    group_item_t *item;
    int i;

    if (!groups || !key)
        return -1;
    for (i = 0; i < groups->size; i++) {
        item = groups->items[i];
        if (compare_by_type(item->key, key, type))
            return i;
    }
    return -1;
}

int populate_groups(group_array_t *groups, dataframe_t *dataframe,
    const char *key_column, const char *value_column)
{
    int key_idx = get_column_idx(dataframe, key_column);
    int val_idx = get_column_idx(dataframe, value_column);
    void *key;
    void *value;
    int i;
    int group_idx;

    if (key_idx == -1 || val_idx == -1)
        return 0;
    for (i = 0; i < dataframe->nb_rows; i++) {
        key = dataframe->columns[key_idx].data[i];
        value = dataframe->columns[val_idx].data[i];
        group_idx = find_group_index(groups, key,
            dataframe->columns[key_idx].type);
        if (group_idx == -1)
            return 0;
        if (!add_to_group(groups, group_idx, value))
            return 0;
    }
    return 1;
}

int populate_all_columns(group_array_t *groups, dataframe_t *dataframe,
    const char *key_column, const char **value_columns)
{
    int i = 0;

    if (!groups || !dataframe || !key_column || !value_columns)
        return 0;
    while (value_columns[i]) {
        if (!populate_groups(groups, dataframe, key_column,
            value_columns[i]))
            return 0;
        i++;
    }
    return 1;
}
