/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_write_csv
*/

#include "dataframe.h"
#include <stdio.h>
#include <stdbool.h>

static void write_data_value(FILE *file, column_t *column, int row)
{
    switch (column->type) {
        case BOOL:
            fprintf(file, "%s",
            *((bool *)column->data[row]) ? "true" : "false");
            break;
        case INT:
            fprintf(file, "%d", *((int *)column->data[row]));
            break;
        case UINT:
            fprintf(file, "%u", *((unsigned int *)column->data[row]));
            break;
        case FLOAT:
            fprintf(file, "%.2f", *((float *)column->data[row]));
            break;
        case STRING:
            fprintf(file, "%s", (char *)column->data[row]);
            break;
        default:
            fprintf(file, "UNKNOWN");
    }
}

int df_write_csv(const dataframe_t *dataframe, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file)
        return 84;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        fprintf(file, "%s", dataframe->columns[i].name);
        if (i < dataframe->nb_columns - 1)
            fprintf(file, "%s", dataframe->separator);
    }
    fprintf(file, "\n");
    for (int row = 0; row < dataframe->nb_rows; row++) {
        for (int col = 0; col < dataframe->nb_columns; col++) {
            write_data_value(file, &dataframe->columns[col], row);
            fprintf(file, col < dataframe->nb_columns - 1 ? "%s" : "\n",
            dataframe->separator);
        }
    }
    fclose(file);
    return 0;
}

void df_print_csv(const dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("%s", dataframe->columns[i].name);
        if (i < dataframe->nb_columns - 1)
            printf("%s", dataframe->separator);
    }
    printf("\n");
    for (int row = 0; row < dataframe->nb_rows; row++) {
        for (int col = 0; col < dataframe->nb_columns; col++) {
            write_data_value(stdout, &dataframe->columns[col], row);
            printf(col < dataframe->nb_columns - 1 ? "%s" : "\n",
            dataframe->separator);
        }
    }
}
