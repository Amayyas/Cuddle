/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_free
*/

#include "dataframe.h"

static void free_column_data(column_t *column, int nb_rows)
{
    if (!column->data)
        return;
    for (int j = 0; j < nb_rows; j++) {
        if (column->data[j])
            free(column->data[j]);
    }
    free(column->data);
}

static void free_columns(column_t *columns, int nb_columns, int nb_rows)
{
    if (!columns)
        return;
    for (int i = 0; i < nb_columns; i++) {
        if (columns[i].name)
            free(columns[i].name);
        free_column_data(&columns[i], nb_rows);
    }
    free(columns);
}

void df_free(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    free_columns(dataframe->columns, dataframe->nb_columns,
        dataframe->nb_rows);
    if (dataframe->separator)
        free(dataframe->separator);
    free(dataframe);
}
