/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** Groupby creation functions
*/

#include <stdlib.h>
#include "dataframe.h"
#include "df_groupby.h"

group_array_t *create_empty_groups(int initial_capacity)
{
    group_array_t *groups = malloc(sizeof(group_array_t));

    if (!groups)
        return NULL;
    groups->size = 0;
    groups->capacity = initial_capacity;
    groups->items = malloc(sizeof(group_item_t *) * initial_capacity);
    if (!groups->items) {
        free(groups);
        return NULL;
    }
    return groups;
}

group_array_t *create_groups(dataframe_t *dataframe, const char *key_column)
{
    void **unique_keys = df_get_unique_values(dataframe, key_column);
    group_array_t *groups;
    int i = 0;

    if (!unique_keys)
        return NULL;
    while (unique_keys[i])
        i++;
    groups = create_empty_groups(i);
    if (!groups) {
        free(unique_keys);
        return NULL;
    }
    for (i = 0; unique_keys[i]; i++)
        add_group(groups, unique_keys[i]);
    free(unique_keys);
    return groups;
}

int add_group(group_array_t *groups, void *key)
{
    group_item_t *item;

    if (!groups || !key)
        return 0;
    item = malloc(sizeof(group_item_t));
    if (!item)
        return 0;
    item->key = key;
    item->values = NULL;
    item->count = 0;
    groups->items[groups->size] = item;
    groups->size++;
    return 1;
}

int add_to_group(group_array_t *groups, int index, void *value)
{
    group_item_t *item;
    void **new_values;

    if (!groups || index < 0 || index >= groups->size || !value)
        return 0;
    item = groups->items[index];
    new_values = realloc(item->values, sizeof(void *) * (item->count + 1));
    if (!new_values)
        return 0;
    item->values = new_values;
    item->values[item->count] = value;
    item->count++;
    return 1;
}
