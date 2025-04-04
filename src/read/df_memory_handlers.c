/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_memory_handlers
*/

#include "dataframe.h"

int allocate_data_arrays(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        dataframe->columns[i].data = malloc(
        sizeof(void *) * dataframe->nb_rows);
        if (!dataframe->columns[i].data)
            return 84;
        for (int j = 0; j < dataframe->nb_rows; j++)
            dataframe->columns[i].data[j] = NULL;
    }
    return 0;
}

void initialize_column_types(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_columns; i++)
        dataframe->columns[i].type = UNDEFINED;
}

void finalize_column_types(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (dataframe->columns[i].type == UNDEFINED) {
            dataframe->columns[i].type = STRING;
        }
    }
}
