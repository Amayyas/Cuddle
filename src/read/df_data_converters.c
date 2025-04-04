/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_data_converters
*/

#include "dataframe.h"
#include <stdbool.h>
#include <string.h>

void *convert_bool(const char *token)
{
    bool *value = malloc(sizeof(bool));
    char *cleaned_token = clean_token(token);

    if (!value || !cleaned_token) {
        free(value);
        free(cleaned_token);
        return NULL;
    }
    *value = (strcasecmp(cleaned_token, "true") == 0) ? true : false;
    free(cleaned_token);
    return value;
}

void *convert_int(const char *token)
{
    int *value = malloc(sizeof(int));
    char *cleaned_token = clean_token(token);

    if (!value || !cleaned_token) {
        free(value);
        free(cleaned_token);
        return NULL;
    }
    *value = (int)strtol(cleaned_token, NULL, 10);
    free(cleaned_token);
    return value;
}

void *convert_uint(const char *token)
{
    unsigned int *value = malloc(sizeof(unsigned int));
    char *cleaned_token = clean_token(token);

    if (!value || !cleaned_token) {
        free(value);
        free(cleaned_token);
        return NULL;
    }
    *value = (unsigned int)strtoul(cleaned_token, NULL, 10);
    free(cleaned_token);
    return value;
}

void *convert_float(const char *token)
{
    float *value = malloc(sizeof(float));
    char *cleaned_token = clean_token(token);

    if (!value || !cleaned_token) {
        free(value);
        free(cleaned_token);
        return NULL;
    }
    *value = strtof(cleaned_token, NULL);
    free(cleaned_token);
    return value;
}

void *convert_token(const char *token, column_type_t type)
{
    switch (type) {
        case BOOL:
            return convert_bool(token);
        case INT:
            return convert_int(token);
        case UINT:
            return convert_uint(token);
        case FLOAT:
            return convert_float(token);
        case STRING:
        case UNDEFINED:
            return clean_token(token);
        default:
            return NULL;
    }
}
