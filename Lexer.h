#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#include "Token.h"
#include "Error.h"
#include "Parser.h"


const char* digits_dot = "0123456789.";

////////////////////////////////////
//	LEXER:
///////////////////////////////////

typedef struct
{
	char* text;
	Position pos;
} Lexer;

void Lexer_Advance(Lexer* self) 
{
	self->text++;
	Position_Advance(&self->pos, *self->text);
}

Lexer mk_Lexer(const char* filename, const char* text)
{
	Lexer self;
	self.text = (char*)malloc(sizeof(char) * 512);
	if (self.text == NULL)
	{
		panic("[Error]: Cannot alloc internal variable 'self.text' in Lexer.class().");
		return self;
	}
	strcpy_s(self.text, strlen(text) + 1, text);
	self.pos = mk_Position(-1, 0, -1, filename, text);

	return self;
}

void TokenList_Append(TokenList* self, Token new_val)
{
	++self->size;
	if (self->size == -1 && self->Data == NULL)
		self->Data = (Token*)malloc(sizeof(Token) * (self->size + 1));
	else
		self->Data = (Token*)realloc(self->Data, sizeof(Token) * (self->size + 1));

	self->Data[self->size] = new_val;
}

Token Lexer_MakeNumbers(Lexer* self)
{
	bool dot = false;
	char _Str[512] = "";

	while (*self->text != '\0' && in(*self->text, digits_dot))
	{
		if (*self->text == '.') 
		{
			if (dot) break;
			dot = true;
			sprintf_s(_Str, 512, "%s.", _Str);
		}
		else 
		{
			sprintf_s(_Str, 512, "%s%c", _Str, *self->text);
		}
		
		Lexer_Advance(self);
	}

	if (dot) 
	{
		float* f = (float*)malloc(sizeof(float));
		*f = (float)atof(_Str);
		return mk_Token(FLOAT, f);
	}
	else
	{
		int* i = (int*)malloc(sizeof(int));
		*i = atoi(_Str);
		return mk_Token(INT, i);
	}
}

////////////////////////////////////
//	Pair Util:
////////////////////////////////////

typedef struct
{
	void* data;
	Error error;
} Pair;

Pair Lexer_MakeTokens(Lexer* self)
{
	TokenList tokens = mk_TokenList();

	while (*self->text != '\0')
	{
		if (*self->text == ' ' || *self->text == '\t') 
			Lexer_Advance(self);
		else if (in(*self->text, digits_dot))
			TokenList_Append(&tokens, Lexer_MakeNumbers(self));

		else if (*self->text == '+') 
		{
			TokenList_Append(&tokens, mk_Token(PLUS, NULL));
			Lexer_Advance(self);
		}
		else if (*self->text == '-') 
		{
			TokenList_Append(&tokens, mk_Token(MINUS, NULL));
			Lexer_Advance(self);
		}
		else if (*self->text == '*') 
		{
			TokenList_Append(&tokens, mk_Token(MUL, NULL));
			Lexer_Advance(self);
		}
		else if (*self->text == '/') 
		{
			TokenList_Append(&tokens, mk_Token(DIV, NULL));
			Lexer_Advance(self);
		}
		else if (*self->text == '(')
		{
			TokenList_Append(&tokens, mk_Token(LPAREN, NULL));
			Lexer_Advance(self);
		}
		else if (*self->text == ')')
		{
			TokenList_Append(&tokens, mk_Token(RPAREN, NULL));
			Lexer_Advance(self);
		}
		else 
		{
			Position p = Position_Copy(self->pos);
			char* c = &*self->text;

			Lexer_Advance(self);
			return (Pair) { &mk_TokenList(), mk_IllegalCharacterError(p, self->pos, c) };
		}
	}

	return (Pair) { &tokens, mk_Error(-1, -1, NULL, NULL) };
}

void Pair_Free(Pair* self) 
{
	TokenList_Free(((TokenList*)self->data));
	Error_Free(&self->error);
}


///////////////////////////////////
//	RUNTIME:
///////////////////////////////////

void run(const char* filename, const char* text)
{
	Lexer lexer = mk_Lexer(filename, text);
	Pair pair = Lexer_MakeTokens(&lexer);
	
	TokenList ls = *((TokenList*)pair.data);
	Error err = pair.error;

	if (err.error)
		puts(Error_ToString(err));
	else 
		puts(TokenList_ToString(ls));

	Parser parser = mk_Parser(ls);
	BinOpNode ast = Parser_Parse(&parser);

	puts(BinOpNode_ToString(ast));
}
