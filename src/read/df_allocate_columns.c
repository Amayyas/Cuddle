/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_allocate_columns
*/

#include "dataframe.h"
#include <ctype.h>
#include <string.h>

static int count_columns(char *line, const char *separator)
{
    char *line_copy = strdup(line);
    char *token = NULL;
    int column_count = 0;

    if (!line_copy)
        return 0;
    token = strtok(line_copy, separator);
    while (token) {
        column_count++;
        token = strtok(NULL, separator);
    }
    free(line_copy);
    return column_count;
}

static column_t *initialize_columns(int column_count)
{
    column_t *columns = malloc(sizeof(column_t) * column_count);

    if (!columns)
        return NULL;
    for (int i = 0; i < column_count; i++) {
        columns[i].name = NULL;
        columns[i].type = UNDEFINED;
        columns[i].data = NULL;
    }
    return columns;
}

column_t *allocate_columns(const char *filename, const char *separator)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int column_count = 0;
    column_t *columns = NULL;

    if (!file)
        return NULL;
    read = getline(&line, &len, file);
    if (read == -1) {
        fclose(file);
        free(line);
        return NULL;
    }
    column_count = count_columns(line, separator);
    columns = initialize_columns(column_count);
    free(line);
    fclose(file);
    return columns;
}
