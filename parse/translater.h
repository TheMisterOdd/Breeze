#ifndef _TRANSLATER_H_
#define _TRANSLATER_H_

#include "../leiva.h"
#include <stddef.h>

typedef struct
{
    /* arguments (including filenames and flags) */
    const char** args;

    /* filenames */
    char** filenames;

    /* flags */
    char* flags;

    /* number of files */
    size_t filenames_len;

    /* arguments count */
    int argc;

} translater_t; /* type to store and translate '.lei' files */

/*
    @breif - Creates a new 'translater_t'
    @param[out] self The pointer to the translater that is going to be created
    @param[in] argv The arguments of the program
    @param[in] len The lenght of the arguments array
*/
LEI_API void lei_translater_create(translater_t* self, const char* argv[], int len);


/*
    @breif - Creates an executable from 'translater_t'
    @param[in] self The pointer to the translater_t
*/
LEI_API void lei_translater_build(translater_t* self);

/*
    @breif - Creates an executable from 'translater_t' and then runs it
    @param[in] self The pointer to the translater_t
*/
LEI_API void lei_translater_run(translater_t* self);

/*
    @breif - Thread in charge of translating the file form leiva to C
    @param[in] arg The pointer to the arguments
*/
LEI_API void* lei_translate_thread(void* arg);

#endif
