#ifndef _LEXER_H_
#define _LEXER_H_

#include <stddef.h>
#include "../list.h"

typedef struct
{
    /* data of the .lei file */
    char* file;

    /* the name of the .lei file */
    const char* filename;

    /* file character index */
    size_t index;

} lexer_t;

void lexer_create(lexer_t* self, const char* filename);

list_t* lexer_make_tokens(lexer_t* self, size_t* len);

void lexer_make_keywords(lexer_t* self, list_t** tokens, size_t len);

void lexer_make_quotes(lexer_t* self, list_t** tokens, size_t len);

void lexer_make_numbers(lexer_t* self, list_t** tokens, size_t len);

#endif
