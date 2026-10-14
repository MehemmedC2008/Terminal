#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reader(void)
{
    size_t size;
    size_t old_cap = 100;
    size_t current_cap = 100;
    char *buff = (char *)malloc(sizeof(char) * current_cap);
    char *tmp = buff;

    if (buff == NULL)
    {
        perror("Allocation failed");
        return NULL;
    }

    if (fgets(buff, current_cap, stdin) == NULL)
    {
        if (ferror(stdin))
        {
            perror("fgets failed");
        }
        free(buff);
        return NULL;
    }

    size = strlen(buff) + 1;
    while (old_cap == size)
    {
        if (!feof(stdin) && buff[size - 2] != '\n')
        {
            current_cap *= 2;
            tmp = realloc(buff, sizeof(char) * current_cap);
            if (tmp == NULL)
            {
                perror("Reallocation failed in size change");
                free(buff);
                return NULL;
            }
            buff = tmp;

            if (fgets(buff + old_cap - 1, current_cap - old_cap + 1, stdin) == NULL)
            {
                if (ferror(stdin))
                {
                    perror("Error occurred during resizing");
                    free(buff);
                    return NULL;
                }
            }

            size = strlen(buff) + 1;
            old_cap = current_cap;
        }
        else
        {
            break;
        }
    }

    tmp = realloc(buff, sizeof(char) * size);
    if (tmp == NULL)
    {
        perror("resizing failed");
        free(buff);
        return NULL;
    }
    buff = tmp;

    if (buff[size - 2] == '\n')
    {
        size--;
        tmp = realloc(buff, sizeof(char) * size);
        if (tmp == NULL)
        {
            perror("resizing failed");
            free(buff);
            return NULL;
        }
        buff = tmp;
        buff[size - 1] = '\0';
    }

    return buff;
}