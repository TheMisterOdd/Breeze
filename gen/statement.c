#include "statement.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define MATCH(x, y) ((!strcmp(x, y)))

const char* get_statement(struct elem** root) 
{
    while (*root != NULL) 
    {      
        struct elem* e = *root;
        if (MATCH(e->value, "import")) 
        {
            printf("wants to import: %s\n", e->next->value);
        }
        else if (MATCH(e->value, "fn")) 
        {
            printf("function %s\n", e->next->value);
        }
        (*root) = (*root)->next;
    }

    return NULL;
}