/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_read_csv
*/

#include "dataframe.h"
#include <ctype.h>
#include <string.h>

static dataframe_t *df_create_dataframe(void)
{
    dataframe_t *dataframe = malloc(sizeof(dataframe_t));

    if (!dataframe)
        return NULL;
    dataframe->columns = NULL;
    dataframe->nb_rows = 0;
    dataframe->nb_columns = 0;
    return dataframe;
}

static int parse_names(dataframe_t *dataframe, char *line,
    const char *separator)
{
    char *token = strtok(line, separator);
    int i = 0;

    while (token) {
        dataframe->columns[i].name = strdup(token);
        token = strtok(NULL, separator);
        i++;
    }
    dataframe->columns[i - 1].name[
        strlen(dataframe->columns[i - 1].name) - 1] = '\0';
    dataframe->nb_columns = i;
    return 0;
}

static void fill_lines(dataframe_t *dataframe, FILE *file,
    const char *separator)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int line_count = 0;

    read = getline(&line, &len, file);
    while (read != -1) {
        if (line_count == 0)
            parse_names(dataframe, line, separator);
        else
            dataframe->nb_rows++;
        line_count++;
        read = getline(&line, &len, file);
    }
    free(line);
}

static char *handle_separator(const char *separator)
{
    char *sep = malloc(sizeof(char) * 2);

    sep[0] = separator == NULL ? ',' : separator[0];
    sep[1] = '\0';
    return sep;
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *dataframe = df_create_dataframe();
    FILE *file = fopen(filename, "r");

    if (!file || !dataframe)
        return NULL;
    dataframe->separator = handle_separator(separator);
    dataframe->columns = allocate_columns(filename, dataframe->separator);
    fill_lines(dataframe, file, dataframe->separator);
    fclose(file);
    if (df_parse_store_data(dataframe, filename, dataframe->separator) == 84) {
        df_free(dataframe);
        return NULL;
    }
    return dataframe;
}
