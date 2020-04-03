#pragma once

#include <malloc.h>
#include <stdio.h>

/*
	ERRORS
*/
typedef struct
{
	char* error;
	char* details;
} Error;

#define mk_Error(error, details) ((Error) { error, details })

const char* Error_ToString(Error self)
{
	char* _Buffer = (char*)malloc(sizeof(char) * 512);
	sprintf_s(_Buffer, 512, "%s: '%s'.", self.error, self.details);
	return _Buffer;
}

typedef Error IllegalCharacterError;

#define mk_IllegalCharacterError(details) ((Error) { "Illegal Character", details })

