#pragma once

#include <malloc.h>

#include "Lexer.h"

///////////////////////////////////
//	NODES:
///////////////////////////////////

typedef struct
{
	Token token;
} NumberNode;

#define mk_NumberNode(token) ((NumberNode) { token })

const char* NumberNode_ToString(NumberNode self)
{
	return Token_ToString(self.token);
}

typedef struct
{
	NumberNode left_node, right_node;
	Token op_tok;
} BinOpNode;

#define mk_BinOpNode(left_node, op_tok, right_node) ((BinOpNode) { left_node, right_node, op_tok })

char* BinOpNode_ToString(BinOpNode self)
{
	char* _Buffer = (char*)malloc(sizeof(char*) * 512);
	if (_Buffer == NULL) 
	{
		panic("[Error]: Cannot alloc internal variable '_Buffer'\n");
	}

	sprintf_s(_Buffer, 512, "(%s, %s, %s)", NumberNode_ToString(self.left_node), Token_ToString(self.op_tok), NumberNode_ToString(self.right_node));
	return _Buffer;
}


///////////////////////////////////
//	PARSER:
///////////////////////////////////

typedef struct 
{
	TokenList tokens;
	Token current;
	int index;
} Parser;

Parser mk_Parser(TokenList tokens) 
{
	Parser self;
	memcpy(&self.tokens, &tokens, sizeof(TokenList*));

	self.index = 1;

	return self;
}

Token Parser_Advance(Parser* self)
{
	self->index++;

	if (self->index < (self->tokens.size + 1))
		self->current = self->tokens.Data[self->index];

	return self->current;
}

NumberNode Parser_GetFactor(Parser* self)
{
	Token token = self->current;
	if (token.T == INT || token.T == FLOAT) 
	{
		Parser_Advance(self);
		return (NumberNode){ token };
	}
	return (NumberNode){ (Token) { NIL, NULL } };
}

BinOpNode Parser_GetTerm(Parser* self)
{
	NumberNode left = Parser_GetFactor(self);
	BinOpNode op;

	while (self->current.T == MUL || self->current.T == DIV)
	{
		Token op_tok = self->current;
		NumberNode right = Parser_GetFactor(self);
		Parser_Advance(self);
		op = (BinOpNode){ left, right, op_tok };
	}
	return op;
}

BinOpNode Parser_GetExpr(Parser* self)
{
	NumberNode left = Parser_GetFactor(self);
	BinOpNode op;

	while (self->current.T == PLUS || self->current.T == MINUS)
	{
		Token op_tok = self->current;
		Parser_Advance(self);
		NumberNode right = Parser_GetFactor(self);
		op = (BinOpNode){ left, right, op_tok };
	}
	return op;
}

BinOpNode Parser_Parse(Parser* self)
{
	return Parser_GetExpr(self);
}
