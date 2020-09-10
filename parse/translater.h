#ifndef _TRANSLATER_H_
#define _TRANSLATER_H_

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
    @breif -
    @param[in]
*/
void translater_create(translater_t* self, const char** args, int len);


/*
*/
void translater_build(translater_t* self);

void translater_run(translater_t* self);

void* translate_thread(void* arg);

#endif
