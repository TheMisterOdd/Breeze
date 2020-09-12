#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "../leiva.h"
#include "../list.h"

LEI_API const char* lei_get_statement(struct elem** root);

LEI_API void lei_get_import(struct elem* e);

LEI_API void lei_get_function(struct elem* e);

#endif