#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(void)
{
    system("cls");
    char *text = "s";
    while (text != NULL)
    {
        text = reader();
        if (text == NULL)
        {
            printf("Loop has been stopped");
            break;
        }
        printf("%s <-> is the text\n", text);

        free(text);
    }

    return 0;
}