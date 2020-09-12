/* include */
#include "translater.h"

#include "lexer.h"
#include "../gen/statement.h"

#include <stdio.h>      // input and output, stream
#include <string.h>     // string handeling 
#include <malloc.h>     // memory allocation
#include <assert.h>     
#include <stdbool.h>    // boolean variables

#include <dirent.h>     // analazing directories
#include <pthread.h>    // threads


#define ERROR_NOT_LEI_EXTENSION     "leiva build: invalid extension at given file '%s'. Should use '.lei' extension.\n"
#define WARNING_DUPLICATED_FILE     "leiva warning: skipping duplicated file: %s.\n"

LEI_API void lei_translater_create(translater_t* self, const char** args, int len)
{
    self->args = args;
    self->argc = len;

    self->filenames_len = 0;
    self->filenames = NULL;

    /* alloc memory for flags */
    self->flags = (char*)malloc(sizeof(char) * 1024);
    strcpy(self->flags, "");

    int i, j, k;
    /* add files to the array */
    for (i = 0; i < self->argc; i++)
    {
        size_t len = strlen(self->args[i]);
		/* check if file has .lei extension */
		if (len >= 4 && self->args[i][len - 4] == '.' && self->args[i][len - 3] == 'l' && self->args[i][len - 2] == 'e' && self->args[i][len - 1] == 'i')
		{
            /* adds a new filename to the array */
            self->filenames_len++;

            /* add new position to introduce a new string */
            if (self->filenames == NULL)
                self->filenames = (char**)malloc(sizeof(char*) * self->filenames_len);
            else
                self->filenames = (char**)realloc(self->filenames, sizeof(char*) * self->filenames_len);

            /* alloc memory for new string */
            self->filenames[self->filenames_len - 1] = (char*)malloc(sizeof(char) * (strlen(self->args[i]) + 1));
            strcpy(self->filenames[self->filenames_len - 1], self->args[i]);
		}
        else if (self->args[i][0] == '-')
        {
            sprintf(self->flags, "%s %s", self->flags, self->args[i]);
        }
		else
		{
			/* error hndl */
			printf(ERROR_NOT_LEI_EXTENSION, self->args[i]);
			break;
		}
    }

    /* check duplicates */
    for (i = 0; i < self->filenames_len; i++)
    {
        for (j = i + 1; j < self->filenames_len; j++)
        {
            if (!strcmp(self->args[i], self->args[j]))
            {
                printf(WARNING_DUPLICATED_FILE, self->args[i]);
                for(k = j; k < self->filenames_len; k++)
                {
                    self->filenames[k] = self->filenames[k + 1];
                }

                self->filenames_len--;
                j--;
            }
        }
    }
    self->filenames = (char**)realloc(self->filenames, sizeof(char*) * self->filenames_len);
}

LEI_API void lei_translater_build(translater_t* self)
{
    DIR* dir = opendir(".");
    assert(dir);

    struct dirent *ent;

    /* leiva file from the directorie */
    char** filenames = NULL;
    
    pthread_t* threads = NULL;
    int len = 0, out_len = 0;
    bool empty = true;

    /* get all .lei files from the directorie */
    while ((ent = readdir (dir)) != NULL)
    {
        /* string lenght */
        char* filename = ent->d_name;
        int slen = strlen(filename);

        if (!strcmp(filename, ".") || !strcmp(filename, ".."))
            continue;
        
        if (slen >= 4 && filename[slen - 4] == '.' && filename[slen - 3] == 'l' && filename[slen - 2] == 'e' && filename[slen - 1] == 'i')
        {
            len++;
            if (filenames == NULL)
            {
                filenames = (char**)malloc(sizeof(char*) * len);
                threads = (pthread_t*)malloc(sizeof(pthread_t) * len);
            }
            else
            {
                filenames = (char**)realloc(filenames, sizeof(char*) * len);
                threads = (pthread_t*)realloc(threads, sizeof(pthread_t) * len);
            }
            assert(filename);
            assert(threads);
            empty = false;

            filenames[len - 1] = (char*)malloc(sizeof(char) * (strlen(filename) + 1));
            strcpy(filenames[len - 1], filename);
            pthread_create(&threads[len - 1], NULL, lei_translate_thread, filenames[len - 1]);
        }
        out_len += slen;
    }
    closedir(dir);

    if (empty) 
    {
        fprintf(stderr, "leiva error: not leiva files found on the directory.\n");
        return;
    }
    char* out = (char*)malloc(sizeof(char) * (out_len + 512));
    assert(out);
    strcpy(out, "gcc");

    int i;
    for (i = 0; i < len; i++)
        sprintf(out, "%s %s.c", out, filenames[i]);

    sprintf(out, "%s%s", out, self->flags);
    puts(out);
    
    /* go thru all the threads to join them */
    for (i = 0; i < len; i++)
        pthread_join(threads[i], NULL);
}

LEI_API void* lei_translate_thread(void* arg)
{
    lexer_t lex;
    lei_lexer_create(&lex, (char*)arg);

    list_t* toks = lei_lexer_make_tokens(&lex);
    if (toks == NULL) 
    {
        fprintf(stderr, "leiva error: file could not be tokenized correctly.\n");
        exit(1);
    }
    
    struct elem* e = toks->root;
    lei_get_statement(&e);

    rmlist(&toks);
    return NULL;
}
