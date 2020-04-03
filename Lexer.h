#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utils.h"
#include "Error.h"

/*
	TOKENS:
*/

const char* digits = "0123456789";
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
	int __bytes;
} TokenList;

#define mk_TokenList() ((TokenList) { NULL, -1 })

const char* Token_ToString(Token);

const char* TokenList_ToString(TokenList self) 
{
	char* _Buffer = (char*)malloc(sizeof(char*) * 512);
	strcpy(_Buffer, "[");

	for (int i = 0; i < self.__bytes + 1; i++) 
	{
		if (i == self.__bytes) 
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

const char* TokenType_ToString(enum TokenType T)
{
	switch (T)
	{
	case INT: return "INT";
	case FLOAT: return "FLOAT";
	case PLUS: return "+";
	case MINUS: return "-";
	case MUL: return "*";
	case DIV: return "/";
	case LPAREN: return "(";
	case RPAREN: return ")";
	default: return "nil";
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
		sprintf_s(_Buffer, 512, "%s: %d", TT_Buffer, (int)self.value);
	}
	else
	{
		sprintf_s(_Buffer, 512, "%s", TT_Buffer);
	}

	return _Buffer;
}

/*
	LEXER
*/

typedef struct
{
	char* text;
	int pos;
} Lexer;

void Lexer_Advance(Lexer* self)
{
	self->pos++;
	if (self->pos != 0)
		*self->text++;

}

Lexer mk_Lexer(const char* text)
{
	Lexer self;
	self.text = (char*)malloc(sizeof(char) * 512);
	if (self.text == NULL)
	{
		panic("[Error]: Cannot alloc internal variable 'self.text' in Lexer.class().");
		return self;
	}
	strcpy_s(self.text, 512, text);
	self.pos = -1;
	Lexer_Advance(&self);

	return self;
}

#define TokenList_GetLenght(self) (self.__bytes + 1)

void TokenList_Append(TokenList* self, Token new_val)
{
	++self->__bytes;
	if (self->__bytes == -1 && self->Data == NULL)
		self->Data = (Token*)malloc(sizeof(Token) * (self->__bytes + 1));
	else
		self->Data = (Token*)realloc(self->Data, sizeof(Token) * (self->__bytes + 1));

	self->Data[self->__bytes] = new_val;
}

Token Token_MakeNumbers(Lexer* self)
{
	char* text = (char*)malloc(sizeof(char) * (strlen(self->text) + 1));
	memcpy(&text, &self->text, sizeof(char*));

	bool dot = false;
	char* numStr = (char*)malloc(sizeof(char) * 512);
	strcpy(numStr, "");

	while (*text != '\0' || in(*text, digits_dot))
	{
		if (dot) break;

		if (*text == '.')
			dot = true;

		sprintf(numStr, "%s%c", numStr, *text);
		*text++;
	}

	return dot ? mk_Token(FLOAT, atoi(numStr)) : mk_Token(INT, atoi(numStr));
}


typedef struct
{
	TokenList list;
	Error err;
} Pair;

Pair Lexer_MakeTokens(Lexer* self)
{
	TokenList tokens = mk_TokenList();

	while (*self->text != '\0')
	{
		if (*self->text == ' ' || *self->text == '\t') 
			*self->text++;
		else if (in(*self->text, digits))
		{
			TokenList_Append(&tokens, Token_MakeNumbers(self));
			self->text++;
		}
		else if (*self->text == '+') 
		{
			TokenList_Append(&tokens, mk_Token(PLUS, NULL));
			*self->text++;
		}
		else if (*self->text == '-') 
		{
			TokenList_Append(&tokens, mk_Token(MINUS, NULL));
			*self->text++;
		}
		else if (*self->text == '*') 
		{
			TokenList_Append(&tokens, mk_Token(MUL, NULL));
			*self->text++;
		}
		else if (*self->text == '/') 
		{
			TokenList_Append(&tokens, mk_Token(DIV, NULL));
			*self->text++;
		}
		else if (*self->text == '(')
		{
			TokenList_Append(&tokens, mk_Token(LPAREN, NULL));
			*self->text++;
		}
		else if (*self->text == ')')
		{
			TokenList_Append(&tokens, mk_Token(RPAREN, NULL));
			*self->text++;
		}
		else 
		{
			return (Pair) { mk_TokenList(), mk_IllegalCharacterError(&*self->text++) };
		}
	}

	return (Pair) { tokens, NULL };
}

/*
	RUNTIME:
*/

Pair run(const char* text)
{
	Lexer lexer = mk_Lexer(text);

	return Lexer_MakeTokens(&lexer);
}