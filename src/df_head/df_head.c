/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Implementation of df_head function to extract first n rows of dataframe
*/

#include "dataframe.h"
#include <stdbool.h>

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *head = NULL;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    head = df_create_subset(dataframe, 0, nb_rows);
    if (!head)
        return NULL;
    if (df_copy_column_metadata(head, dataframe) == 84) {
        df_free(head);
        return NULL;
    }
    if (df_copy_data(head, dataframe, 0) == 84) {
        df_free(head);
        return NULL;
    }
    return head;
}
