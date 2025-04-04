/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_dataframe_create
*/

#include "dataframe.h"
#include "df_conversions.h"
#include <string.h>
#include <stdlib.h>

dataframe_t *create_empty_result_df(dataframe_t *src_df)
{
    dataframe_t *result_df;

    result_df = malloc(sizeof(dataframe_t));
    if (!result_df)
        return NULL;
    result_df->nb_rows = src_df->nb_rows;
    result_df->nb_columns = src_df->nb_columns;
    result_df->separator = strdup(src_df->separator);
    result_df->columns = NULL;
    return result_df;
}

bool allocate_df_columns(dataframe_t *df)
{
    df->columns = malloc(sizeof(column_t) * df->nb_columns);
    return (df->columns != NULL);
}

void cleanup_partial_df(dataframe_t *df)
{
    if (df->separator)
        free(df->separator);
    if (df->columns)
        free(df->columns);
    free(df);
}
