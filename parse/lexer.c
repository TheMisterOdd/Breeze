#include "lexer.h"

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

LEI_API static char* read_file(const char* filename)
{
    long length;
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
	{
		fprintf(stderr, "leiva error: cannot find %s\n", filename);
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = (char*)malloc((length + 1) * sizeof(char));
	assert(buffer);

	fread(buffer, sizeof(char), length, f);
	buffer[length] = '\0';

	fclose(f);

	return buffer;
}

LEI_API void lei_lexer_create(lexer_t* self, const char* filename)
{
    self->filename = filename;
    self->file = read_file(filename);
    self->index = -1;
}

LEI_API list_t* lei_lexer_make_tokens(lexer_t* self)
{
	char current;
	list_t* ls = mklist();
	
	int line = 0;
	while ((current = self->file[++self->index]) != '\0')
	{		
		
		if (iscntrl(current) || isspace(current) || isblank(current))
		{	
			if (current == '\n') 
			{
				char* c = (char*)malloc(sizeof(char) * 3);
				strcpy(c, "\\n");
				pushbacklist(&ls, (void*)c);
				line++;
			}
				

			continue;
		}
		else if (isdigit(current))
		{
			lei_lexer_make_numbers(self, &ls);
		}
		else if (isalpha(current))
		{
			lei_lexer_make_keywords(self, &ls);
		}
		else if (ispunct(current))
		{
			if (current == '"')
			{	
				lei_lexer_make_quotes(self, &ls);
			}
			else if (current == ':' && self->file[self->index + 1] == '=')
			{	
				char* c = (char*)malloc(sizeof(char) * 3);
                c[0] = ':';
				c[1] = '=';
				c[2] = 0;

				self->index++;
			}
			else if (current == ';')
			{
                printf("leiva warning: unnecessary ';' on %s:%d\n", self->filename, line + 1);
			}
			/* skiping characters if there are in a comment */
			else if (current == '/' && self->file[self->index + 1] == '*')
			{
				while (self->file[++self->index])
					if (self->file[self->index] == '*' && self->file[self->index + 1] == '/') { break; };
				self->index++;
			}
			else if (current == '/' && self->file[self->index + 1] == '/')
			{
				while (self->file[++self->index])
					if (self->file[self->index] == '\n') { break; };
				self->index++;
			}
			else
			{	
				char* c = (char*)malloc(sizeof(char) * 2);
                c[0] = current;
				c[1] = 0;

				pushbacklist(&ls, c);
			}
		}
	}
 
	return ls;
}


LEI_API void lei_lexer_make_quotes(lexer_t* self, list_t** tokens) 
{
	char current;

	char* quotes = (char*)malloc(sizeof(char) * 4096);
	strcpy(quotes, "\"");

	while ((current = self->file[++self->index]) != '\0')
	{
		sprintf(quotes, "%s%c%c", quotes, current, '\0');
		if (current == '"')
		{
			break;
		}
	}
	pushbacklist(tokens, (void*)quotes);
}

LEI_API void lei_lexer_make_keywords(lexer_t* self, list_t** tokens) 
{
	char current;

	char* keyword = (char*)malloc(sizeof(char) * 1024);
	strcpy(keyword, "");

	size_t _index = self->index;
	while ((current = self->file[_index++]) != '\0')
	{
		if (
			(current == ' ' || current == '\t' || current == '\n' || current == '\r') ||
			(current <= 47 && current >= 33) ||
			(current <= 64 && current >= 58) ||
			(current <= 96 && current >= 91) ||
			(current <= 126 && current >= 123))
		{
			break;
		}
		else 
		{
			sprintf(keyword, "%s%c\0", keyword, current);
		}
	}

	self->index = _index - 2;
	pushbacklist(tokens, (void*)keyword);
}

LEI_API void lei_lexer_make_numbers(lexer_t* self, list_t** tokens) 
{
	char current;

	char* number = (char*)malloc(sizeof(char) * 1024);
	strcpy(number, "");

	bool dot = false;
	size_t _index = self->index;
	/* loops over the caracters that will make the given number. */
	while ((current = self->file[_index++]) != '\0' && (isdigit(current) || current == '.'))
	{
		if (current == '.')
		{
			if (dot == true)
			{	
				fprintf(stderr, "leiva parse error: multiple decimal definition");
				// TODO: make error handeler.
				exit(-1);
			}
			dot = true;
		}
		sprintf(number, "%s%c%c", number, current, 0);
	}

	self->index = _index - 2;
	pushbacklist(tokens, (void*)number);
}