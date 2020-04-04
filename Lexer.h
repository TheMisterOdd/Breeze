#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utils.h"
#include "Error.h"

////////////////////////////////////
//
//	TOKENS:
//
////////////////////////////////////

const char* digits_dot = "0123456789.";

bool in(char c, const char* arr)
{
	for (int i = 0; i < (int)strlen(arr); i++)
		if (c == arr[i])
			return true;

	return false;
}

enum TokenType
{
	INT,
	FLOAT,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LPAREN,
	RPAREN
};

typedef struct
{
	enum TokenType T;
	void* value;
} Token;

#define mk_Token(T, value) ((Token) { T, (void*)value })

typedef struct
{
	Token* Data;
	int size;
} TokenList;

#define mk_TokenList() ((TokenList) { NULL, -1 })

const char* TokenType_ToString(enum TokenType T)
{
	switch (T)
	{
	case INT: return "INT";
	case FLOAT: return "FLOAT";
	case PLUS: return "PLUS";
	case MINUS: return "MINUS";
	case MUL: return "MUL";
	case DIV: return "DIV";
	case LPAREN: return "LPAREN";
	case RPAREN: return "RPAREN";
	default: return "null";
	}
}

const char* Token_ToString(Token self)
{
	char* _Buffer = (char*)malloc(sizeof(char) * 512);
	if (_Buffer == NULL)
	{
		return NULL;
	}

	const char* TT_Buffer = TokenType_ToString(self.T);
	if (self.value != NULL)
	{
		if (self.T == INT) 
		{
			int i = *((int*)self.value);
			sprintf_s(_Buffer, 512, "%s: %ld", TT_Buffer, i);
		}
		else if(self.T == FLOAT) 
		{
			float f = *((float*)self.value);
			sprintf_s(_Buffer, 512, "%s: %f", TT_Buffer, f);
		}
	}
	else
	{
		sprintf_s(_Buffer, 512, "%s", TT_Buffer);
	}

	return _Buffer;
}

const char* TokenList_ToString(TokenList self)
{
	char* _Buffer = (char*)malloc(sizeof(char*) * 512);
	strcpy(_Buffer, "[");

	for (int i = 0; i < self.size + 1; i++)
	{
		if (i == self.size)
		{
			sprintf(_Buffer, "%s%s", _Buffer, Token_ToString(self.Data[i]));
		}
		else
		{
			sprintf(_Buffer, "%s%s, ", _Buffer, Token_ToString(self.Data[i]));
		}
	}

	sprintf(_Buffer, "%s]", _Buffer);
	return _Buffer;
}

void Token_Free(Token* self) 
{
	free(self->value);
}

void TokenList_Free(TokenList* self) 
{
	Token_Free(self->Data);
	self->size = 0;
}

/*
	LEXER
*/


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
	strcpy(self.text, text);
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
			sprintf(_Str, "%s.", _Str);
		}
		else 
		{
			sprintf(_Str, "%s%c", _Str, *self->text);
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

typedef struct
{
	TokenList list;
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
			return (Pair) { mk_TokenList(), mk_IllegalCharacterError(p, self->pos, c) };
		}
	}

	return (Pair) { tokens, NULL };
}

void Pair_Free(Pair* self) 
{
	TokenList_Free(&self->list);
	Error_Free(&self->error);
}

/*
	RUNTIME:
*/

Pair run(const char* filename, const char* text)
{
	Lexer lexer = mk_Lexer(filename, text);

	return Lexer_MakeTokens(&lexer);
}
