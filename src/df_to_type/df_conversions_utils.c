/*
** EPITECH PROJECT, 2025
** G-AIA-200-MPL-2-1-cuddle-gabriel.brument
** File description:
** df_conversions_utils
*/


#include "dataframe.h"
#include "df_conversions.h"
#include <string.h>
#include <stdlib.h>

void *allocate_typed_memory(size_t size)
{
    void *mem = malloc(size);

    if (mem)
        memset(mem, 0, size);
    return mem;
}
