#ifndef _LEXER_H_
#define _LEXER_H_

#include <stddef.h>

#include "../leiva.h"
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

/*
    @breif - Creates a new 'lexer_t
    @param[out] self The lexer struct
    @param[in] filename The file is going to be analized
*/
LEI_API void lei_lexer_create(lexer_t* self, const char* filename);

/*
    @breif - Tokenizes the file saved in the 'lexer_t'
    @param[in] self The lexer struct
*/
LEI_API list_t* lei_lexer_make_tokens(lexer_t* self);

LEI_API void lei_lexer_make_keywords(lexer_t* self, list_t** tokens);

LEI_API void lei_lexer_make_quotes(lexer_t* self, list_t** tokens);

LEI_API void lei_lexer_make_numbers(lexer_t* self, list_t** tokens);

#endif
