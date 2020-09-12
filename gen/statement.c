#include "statement.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define MATCH(x, y) ((!strcmp((char*)x, (char*)y)))

// gets the series of imports
static void get_import(struct elem* e) 
{   
    if (MATCH(e->next->value, "(")) 
    {   
        e = e->next;
        while (e != NULL) 
        {   
            if (MATCH(e->next->value, "\\n")) 
                goto skip;

            if (MATCH(e->next->value, ")")) 
            {
                
                break;
            }

            printf("import: %s\n", (char*)e->next->value);
            
            skip:
            e = e->next;
        }
    }
    else 
    {
        printf("import: %s\n", (char*)e->next->value);
    }
}

static void get_function(struct elem* e) 
{
    char* name = (char*)e->next->value;
    printf("fn %s(", name);

    e = e->next->next->next;
    while (e != NULL) 
    {   

        if (MATCH(e->value, ")")) 
            break;
            
        printf("%s ", (char*)e->value);

        e = e->next;
    }
    printf(")\n");
}

LEI_API const char* lei_get_statement(struct elem** root) 
{   
    struct elem* e = *root;
    while (e != NULL) 
    {      
        if (MATCH(e->value, "import")) 
        {
            get_import(e);
        }
        else if (MATCH(e->value, "fn")) 
        {
            get_function(e);
        }
        e = e->next;
    }

    return NULL;
}