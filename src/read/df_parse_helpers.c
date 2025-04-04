/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_parse_helpers
*/

#include "dataframe.h"
#include <string.h>

char *duplicate_line(const char *line)
{
    char *line_copy = strdup(line);

    if (!line_copy)
        return NULL;
    return line_copy;
}

int process_token_for_type(dataframe_t *dataframe, const char *token, int col)
{
    char *cleaned_token = clean_token(token);
    column_type_t type;

    if (!cleaned_token)
        return 84;
    type = get_column_type(cleaned_token);
    update_column_type(&dataframe->columns[col], type);
    free(cleaned_token);
    return 0;
}

int process_line_for_types(dataframe_t *dataframe, char *line,
    const char *separator)
{
    char *line_copy = duplicate_line(line);
    char *token = NULL;
    int col = 0;

    if (!line_copy)
        return 84;
    token = strtok(line_copy, separator);
    while (token != NULL && col < dataframe->nb_columns) {
        if (process_token_for_type(dataframe, token, col) == 84) {
            free(line_copy);
            return 84;
        }
        token = strtok(NULL, separator);
        col++;
    }
    free(line_copy);
    return 0;
}

int store_token_data(dataframe_t *dataframe, const char *token,
    int row, int col)
{
    dataframe->columns[col].data[row] = convert_token(token,
        dataframe->columns[col].type);
    if (!dataframe->columns[col].data[row])
        return 84;
    return 0;
}

int process_line_for_data(dataframe_t *dataframe, char *line,
    const char *separator, int row)
{
    char *line_copy = duplicate_line(line);
    char *token = NULL;
    int col = 0;

    if (!line_copy)
        return 84;
    token = strtok(line_copy, separator);
    while (token != NULL && col < dataframe->nb_columns) {
        if (store_token_data(dataframe, token, row, col) == 84) {
            free(line_copy);
            return 84;
        }
        token = strtok(NULL, separator);
        col++;
    }
    free(line_copy);
    return 0;
}
