/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_type_handlers
*/

#include "dataframe.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int handle_bool(const char *token, int *return_value)
{
    char *cleaned_token = clean_token(token);
    int result = 0;

    if (!cleaned_token)
        return 0;
    if (strcasecmp(cleaned_token, "true") == 0 ||
        strcasecmp(cleaned_token, "false") == 0) {
        *return_value = BOOL;
        result = 1;
    }
    free(cleaned_token);
    return result;
}

int handle_float(const char *token, int *return_value)
{
    char *endptr;
    int dot_count = 0;

    for (int i = 0; token[i]; i++)
        if (token[i] == '.')
            dot_count++;
    if (dot_count != 1)
        return 0;
    strtof(token, &endptr);
    if (*endptr == '\0' || *endptr == '\n' || *endptr == '\r') {
        *return_value = FLOAT;
        return 1;
    }
    return 0;
}

int handle_int(const char *token, int *return_value)
{
    char *endptr;

    if (strchr(token, '.') != NULL)
        return 0;
    strtol(token, &endptr, 10);
    if (*endptr == '\0' || *endptr == '\n' || *endptr == '\r') {
        *return_value = INT;
        return 1;
    }
    return 0;
}

static int handle_uint(const char *token, int *return_value)
{
    if (token[0] == '-')
        return 0;
    return handle_int(token, return_value);
}

column_type_t get_column_type(const char *token)
{
    int return_value = UNDEFINED;

    if (handle_bool(token, &return_value) == 1)
        return return_value;
    if (handle_float(token, &return_value) == 1)
        return return_value;
    if (handle_uint(token, &return_value) == 1)
        return UINT;
    if (handle_int(token, &return_value) == 1)
        return return_value;
    return STRING;
}

void update_column_type(column_t *column, column_type_t new_type)
{
    if (column->type == UNDEFINED || column->type == new_type)
        column->type = new_type;
    if (column->type == BOOL)
        column->type = new_type;
    if (column->type == UINT && new_type == INT)
        column->type = INT;
    if (column->type == UINT && new_type == FLOAT)
        column->type = FLOAT;
    if ((column->type == INT || column->type == UINT) && new_type == FLOAT)
        column->type = FLOAT;
    if (new_type == STRING)
        column->type = STRING;
}
