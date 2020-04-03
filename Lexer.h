#pragma once

#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

#define mk_TokenList() ((TokenList) { NULL, -1 });

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
		sprintf_s(_Buffer, 512, "{%s: %d}", TT_Buffer, (int)self.value);
	} else 
	{
		sprintf_s(_Buffer, 512, "{%s}", TT_Buffer);
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
	char current_char;
} Lexer;

void Lexer_Advance(Lexer* self) 
{
	self->pos++;
	if (self->pos < ((int)strlen(self->text) + 1)) 
		self->text[self->pos]; 
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
	self.pos = -1;
	self.current_char = 0;

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
	bool dot = false;
	char numStr[512] = "";

	while (self->current_char != 0 && in(self->current_char, digits_dot)) 
	{
		if (self->current_char == '.') 
		{
			if (dot) break;

			dot = true;
			strncat_s(numStr, 512, ".", sizeof(char) * 512);
		}
		else 
		{
			strncat_s(numStr, 512, &self->current_char, sizeof(char) * 512);
		}
			
	}

	printf("%d %.2f\n", atoi(numStr), atof(numStr));
	return dot ? mk_Token(INT, atoi(numStr)) : mk_Token(FLOAT, atoi(numStr));
}

Pair Lexer_MakeTokens(Lexer* self) 
{	
	TokenList tokens = mk_TokenList();

	while (self->current_char != 0) 
	{
		if (self->current_char == ' ' || self->current_char == '\t')
			Lexer_Advance(self);
		else if (in(self->current_char, digits)) 
		{
			TokenList_Append(&tokens, Token_MakeNumbers(self));
		}
		else if (self->current_char == '+') 
		{
			TokenList_Append(&tokens, mk_Token(PLUS, NULL));
			Lexer_Advance(self);
		}
		else if (self->current_char == '-')
		{
			TokenList_Append(&tokens, mk_Token(MINUS, NULL));
			Lexer_Advance(self);
		}
		else if (self->current_char == '*')
		{
			TokenList_Append(&tokens, mk_Token(MUL, NULL));
			Lexer_Advance(self);
		}
		else if (self->current_char == '/')
		{
			TokenList_Append(&tokens, mk_Token(DIV, NULL));
			Lexer_Advance(self);
		}
		else if (self->current_char == '(')
		{
			TokenList_Append(&tokens, mk_Token(LPAREN, NULL));
			Lexer_Advance(self);
		}
		else if (self->current_char == ')')
		{
			TokenList_Append(&tokens, mk_Token(RPAREN, NULL));
			Lexer_Advance(self);
		}
		else 
		{
			char c = self->current_char;
			Lexer_Advance(self);
			return (Pair){ NULL, &mk_IllegalCharacterError(&c) };
		}
	}

	return (Pair) { &tokens, NULL };
}