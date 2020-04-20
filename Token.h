#pragma once

#include <string.h>
#include <malloc.h>
#include <stdio.h>

////////////////////////////////////
//	TOKENS:
////////////////////////////////////


bool in(char c, const char* arr)
{
	for (int i = 0; i < (int)strlen(arr); i++)
		if (c == arr[i])
			return true;

	return false;
}

#define NULL_TOK 0
#define INT 1
#define FLOAT 2
#define PLUS 3
#define MINUS 4
#define MUL 5
#define DIV 6
#define LPAREN 7
#define RPAREN 8

#define TokType char

typedef struct
{
	TokType T;
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
	case INT: return "i32";
	case FLOAT: return "f32";
	case PLUS: return "PLUS";
	case MINUS: return "MINUS";
	case MUL: return "MUL";
	case DIV: return "DIV";
	case LPAREN: return "LPAREN";
	case RPAREN: return "RPAREN";
	default: return "null";
	}
}

char* Token_ToString(Token self)
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
		else if (self.T == FLOAT)
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
	strcpy_s(_Buffer, 512, "[");

	for (int i = 0; i < self.size + 1; i++)
	{
		if (i == self.size)
		{
			sprintf_s(_Buffer, 512, "%s%s", _Buffer, Token_ToString(self.Data[i]));
		}
		else
		{
			sprintf_s(_Buffer, 512, "%s%s, ", _Buffer, Token_ToString(self.Data[i]));
		}
	}

	sprintf_s(_Buffer, 512, "%s]", _Buffer);
	return _Buffer;
}

void TokenList_Free(TokenList* self)
{
	free(self->Data);
	self->size = 0;
	self = NULL;
}

