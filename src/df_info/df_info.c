/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_info
*/

#include "dataframe.h"

static void print_column_type(column_type_t type)
{
    switch (type) {
        case BOOL:
            printf("bool\n");
            break;
        case INT:
            printf("int\n");
            break;
        case UINT:
            printf("unsigned int\n");
            break;
        case FLOAT:
            printf("float\n");
            break;
        case STRING:
            printf("string\n");
            break;
        case UNDEFINED:
            printf("undefined\n");
            break;
    }
}

void df_info(dataframe_t *dataframe)
{
    printf("%d columns:\n", dataframe->nb_columns);
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("- %s: ", dataframe->columns[i].name);
        print_column_type(dataframe->columns[i].type);
    }
}
