#include "statement.h"

#include <string.h>
#include <malloc.h>
#include <assert.h>

#define MATCH(x, y) ((!strcmp((char*)x, (char*)y)))

LEI_API void lei_get_statements(const char* C_filename, struct elem** root) 
{   
    printf("FILE: %s\n", C_filename);
    lei_File* f = calloc(sizeof(lei_File), 1);
    assert(f);

    f->fp = fopen(C_filename, "wb");
    assert(f->fp);

    struct elem* e = *root;
    while (e != NULL) 
    {      
        if (MATCH(e->value, "import")) 
        {
            lei_get_import(f, e);
        }
        else if (MATCH(e->value, "fn")) 
        {
            lei_get_function(f, e);
        }
        else if (MATCH(e->value, "package")) 
        {
            lei_get_package(f, e);
        }
        e = e->next;
    }

    printf("package: %s\n", f->package);
    free(f);
}

// gets the series of imports
LEI_API void lei_get_import(lei_File* f, struct elem* e) 
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

LEI_API void lei_get_package(lei_File* f, struct elem* e) 
{   
    char* value = e->next->value;
    if (value != NULL) 
    {
        f->package = calloc(sizeof(char), strlen(value) + 1);
        assert(f->package);
        strcpy(f->package, value);
    }
}

LEI_API void lei_get_function(lei_File* f, struct elem* e) 
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
