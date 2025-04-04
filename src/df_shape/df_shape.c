/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_shape
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape;

    shape.nb_rows = dataframe->nb_rows;
    shape.nb_columns = dataframe->nb_columns;
    return shape;
}
