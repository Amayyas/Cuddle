/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_string_utils
*/

#include "dataframe.h"
#include <string.h>

char *clean_token(const char *token)
{
    char *cleaned_token = strdup(token);
    int len = 0;

    if (!cleaned_token)
        return NULL;
    len = strlen(cleaned_token);
    for (int i = 0; cleaned_token[i]; i++) {
        if (cleaned_token[i] == '\n' || cleaned_token[i] == '\r')
            cleaned_token[i] = '\0';
    }
    while (len > 0 && (cleaned_token[len - 1] == '\n' ||
        cleaned_token[len - 1] == '\r' ||
        cleaned_token[len - 1] == ' ')) {
        cleaned_token[len - 1] = '\0';
        len--;
    }
    return cleaned_token;
}
