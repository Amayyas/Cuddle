/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_parse_store_data
*/

#include "dataframe.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

static int analyze_column_types(dataframe_t *dataframe, FILE *file,
    const char *separator)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int row = 0;

    initialize_column_types(dataframe);
    if (allocate_data_arrays(dataframe) == 84)
        return 84;
    getline(&line, &len, file);
    read = getline(&line, &len, file);
    while (read != -1 && row < dataframe->nb_rows) {
        if (process_line_for_types(dataframe, line, separator) == 84)
            return 84;
        row++;
        read = getline(&line, &len, file);
    }
    finalize_column_types(dataframe);
    free(line);
    return 0;
}

static int store_data(dataframe_t *dataframe, FILE *file,
    const char *separator)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int row = 0;

    rewind(file);
    getline(&line, &len, file);
    read = getline(&line, &len, file);
    while (read != -1 && row < dataframe->nb_rows) {
        if (process_line_for_data(dataframe, line, separator, row) == 84) {
            free(line);
            return 84;
        }
        row++;
        read = getline(&line, &len, file);
    }
    free(line);
    return 0;
}

static int parse_and_store_data(dataframe_t *dataframe, FILE *file,
    const char *separator)
{
    if (analyze_column_types(dataframe, file, separator) == 84)
        return 84;
    if (store_data(dataframe, file, separator) == 84)
        return 84;
    return 0;
}

int df_parse_store_data(dataframe_t *dataframe, const char *filename,
    const char *separator)
{
    FILE *file = fopen(filename, "r");
    int result;

    if (!file || !dataframe)
        return 84;
    result = parse_and_store_data(dataframe, file, separator);
    fclose(file);
    return result;
}
