#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "../leiva.h"
#include "../list.h"
#include <stdio.h>

typedef struct 
{
    // file pointer
    FILE* fp;

    // name of the package
    char* package;

    // list of constants
    list_t* constants;

    // list of imports
    list_t* imports;

} lei_File;

LEI_API void lei_get_statements(const char* C_filename, struct elem** root);

LEI_API void lei_get_import(lei_File* f, struct elem* e);

LEI_API void lei_get_function(lei_File* f, struct elem* e);

LEI_API void lei_get_package(lei_File* f, struct elem* e);

#endif