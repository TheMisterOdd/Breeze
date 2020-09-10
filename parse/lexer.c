#include "lexer.h"

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static char* read_file(const char* filename)
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

void lexer_create(lexer_t* self, const char* filename)
{
    self->filename = filename;
    self->file = read_file(filename);
    self->index = -1;
}

list_t* lexer_make_tokens(lexer_t* self, size_t* len)
{
	char current;
	list_t* ls = mklist();
	
	int line = 0;
	while ((current = self->file[++self->index]) != '\0')
	{		
		
		if (iscntrl(current) || isspace(current) || isblank(current))
		{	
			if (current == '\n') 
				line++;

			continue;
		}
		else if (isdigit(current))
		{
			lexer_make_numbers(self, &ls, *len);
			(*len)++;
		}
		else if (isalpha(current))
		{
			lexer_make_keywords(self, &ls, *len);
			(*len)++;
		}
		else if (ispunct(current))
		{
			if (current == '"')
			{	
				lexer_make_quotes(self, &ls, *len);
				(*len)++;
			}
			else if (current == ':' && self->file[self->index + 1] == '=')
			{	
				char* c = (char*)malloc(sizeof(char) * 3);
                c[0] = ':';
				c[1] = '=';
				c[2] = 0;

				self->index++;
				(*len)++;
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
				(*len)++;
			}
		}
	}
 
	return ls;
}


void lexer_make_quotes(lexer_t* self, list_t** tokens, size_t len) 
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

void lexer_make_keywords(lexer_t* self, list_t** tokens, size_t len) 
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

void lexer_make_numbers(lexer_t* self, list_t** tokens, size_t len) 
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