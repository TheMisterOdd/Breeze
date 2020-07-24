#ifndef _LEXER_H_
#define _LEXER_H_

#define STRING_MAX_LEN 0x200

#include "list.h"

typedef struct {
	char* text;
	unsigned int index;
} lexer_t;

lexer_t* lexer_init();

void lexer_set_text(lexer_t* self, char* text);

struct list_t* lexer_lex(lexer_t* self);

void lexer_make_numbers(lexer_t* self, struct list_t** tokens);

void lexer_make_keywords(lexer_t* self, struct list_t** ls);

#ifdef LEXER_IMPL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


lexer_t* lexer_init()
{
	lexer_t* self = (lexer_t*)malloc(sizeof(lexer_t));
	if (self == NULL)
	{
		fprintf(stderr, "[Error]: 'lexer_init' failed. Cannot alloc memory for the new 'lexer_t' object.\n");
		exit(-1);
	}
	self->text = NULL;
	self->index = -1;

	return self;
}

void lexer_set_text(lexer_t* self, char* text)
{
	free(self->text);
	self->text = (char*)malloc(sizeof(char) * (strlen(text) + 1));

	if (self->text == NULL)
	{
		fprintf(stderr, "[Error]: 'lexer_set_text' failed. Cannot alloc memory for the new 'lexer_t->text' object.\n");
		exit(-1);
	}

	strcpy(self->text, text);
}

struct list_t* lexer_lex(lexer_t* self)
{
	struct list_t* ls = NULL;
	char current;
	while ((current = *(self->text + ++self->index)))
	{
		if (current == '\n' || current == '\t' || current == ' ')
		{
			continue;
		}
		else if (current <= '9' && current >= '0') 
		{
			lexer_make_numbers(self, &ls);
		}
		else if (current <= 'z' && current >= 'a')
		{
			lexer_make_keywords(self, &ls);
		}
		else if (current == '+') 
		{
			list_push_back(&ls, (void*)'+', PLUS);
		}
		else if (current == '-')
		{
			list_push_back(&ls, (void*)'-', MINUS);
		}
		else if (current == '*')
		{
			list_push_back(&ls, (void*)'*', MUL);
		}
		else if (current == '/')
		{
			list_push_back(&ls, (void*)'/', DIV);
		}
		else if (current == '(') 
		{
			list_push_back(&ls, (void*)'(', LPAREN);
		}
		else if(current == ')') 
		{
			list_push_back(&ls, (void*)')', RPAREN);
		}
		else if (current == '^') 
		{
			list_push_back(&ls, (void*)'^', POWER);
		}
		else 
		{
			fprintf(stderr, "[Error]: '%c': Unknow value, symbol or character.\n", current);
			break;
		}
	}
	self->index = -1;
	return ls;
}

void lexer_make_numbers(lexer_t* self, struct list_t** ls)
{
	char current, * number = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	strcpy(number, "");

	size_t index = self->index;
	bool dot = false;

	while ((current = *(self->text + index++)))
	{
		if ((current <= '9' && current >= '0') || current == '.')
		{
			if (current == '.' && !dot)
			{
				dot = true;
			}
			else if (current == '.' && dot)
			{
				fprintf(stderr, "[Error]: Multiple decimals declaration in number.\n");
				exit(-1);
			}

			sprintf(number, "%s%c", number, current);
		}
		else {
			break;
		}
	}

	self->index = index - 2;
	if (dot)
	{
		double p = atof(number);
		list_push_back(ls, &p, DOUBLE);
	}
	else 
	{	
		list_push_back(ls, (void*)_atoi64(number), INT);
	}

}

void lexer_make_keywords(lexer_t* self, struct list_t** ls) 
{
	char current, *keyword = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	strcpy(keyword, "");

	size_t index = self->index;

	while ((current = *(self->text + index++)))
	{
		if ((current <= 'z' && current >= 'a'))
		{
			sprintf(keyword, "%s%c", keyword, current);
		}
		else {
			break;
		}
	}
	self->index = index - 2;
	list_push_back(ls, (void*)keyword, STRING);
	

}

#endif


#endif /* !_LEXER_H_ */

