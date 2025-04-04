/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_describe
*/

#include "dataframe.h"
#include <math.h>

static double calculate_mean(void **data, int count, column_type_t type)
{
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        if (type == INT)
            sum += *(int *)data[i];
        if (type == UINT)
            sum += *(unsigned int *)data[i];
        if (type == FLOAT)
            sum += *(float *)data[i];
    }
    return sum / count;
}

static double calculate_std(void **data, int count,
    column_type_t type, double mean)
{
    double sum_squared_diff = 0.0;
    double value;

    for (int i = 0; i < count; i++) {
        if (type == INT)
            value = *(int *)data[i];
        if (type == UINT)
            value = *(unsigned int *)data[i];
        if (type == FLOAT)
            value = *(float *)data[i];
        sum_squared_diff += (value - mean) * (value - mean);
    }
    return sqrt(sum_squared_diff / count);
}

static double find_min(void **data, int count, column_type_t type)
{
    double min;
    double value;

    if (type == INT)
        min = *(int *)data[0];
    if (type == UINT)
        min = *(unsigned int *)data[0];
    if (type == FLOAT)
        min = *(float *)data[0];
    for (int i = 1; i < count; i++) {
        if (type == INT)
            value = *(int *)data[i];
        if (type == UINT)
            value = *(unsigned int *)data[i];
        if (type == FLOAT)
            value = *(float *)data[i];
        if (value < min)
            min = value;
    }
    return min;
}

static double find_max(void **data, int count, column_type_t type)
{
    double max;
    double value;

    if (type == INT)
        max = *(int *)data[0];
    if (type == UINT)
        max = *(unsigned int *)data[0];
    if (type == FLOAT)
        max = *(float *)data[0];
    for (int i = 1; i < count; i++) {
        if (type == INT)
            value = *(int *)data[i];
        if (type == UINT)
            value = *(unsigned int *)data[i];
        if (type == FLOAT)
            value = *(float *)data[i];
        if (value > max)
            max = value;
    }
    return max;
}

static void describe_column(column_t column, int count)
{
    double mean = 0;
    double std = 0;
    double min = 0;
    double max = 0;

    if (column.type != INT && column.type != UINT && column.type != FLOAT)
        return;
    mean = calculate_mean(column.data, count, column.type);
    std = calculate_std(column.data, count, column.type, mean);
    min = find_min(column.data, count, column.type);
    max = find_max(column.data, count, column.type);
    printf("Column: %s\n", column.name);
    printf("Count: %d\n", count);
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", std);
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
}

void df_describe(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_columns; i++)
        describe_column(dataframe->columns[i], dataframe->nb_rows);
}
