/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** Implementation of df_tail function to extract last n rows of dataframe
*/

#include "dataframe.h"
#include <stdbool.h>

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *tail = NULL;
    int start_row = 0;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    start_row = dataframe->nb_rows - nb_rows;
    if (start_row < 0)
        start_row = 0;
    tail = df_create_subset(dataframe, start_row, nb_rows);
    if (!tail)
        return NULL;
    if (df_copy_column_metadata(tail, dataframe) == 84) {
        df_free(tail);
        return NULL;
    }
    if (df_copy_data(tail, dataframe, start_row) == 84) {
        df_free(tail);
        return NULL;
    }
    return tail;
}
