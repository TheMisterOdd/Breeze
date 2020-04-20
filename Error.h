#pragma once

#include <malloc.h>
#include <stdio.h>

#include "Utils.h"

/*
	ERRORS
*/
typedef struct
{
	Position pos_start, pos_end;
	char* error;
	char* details;
} Error;

#define mk_Error(pos_start, pos_end, error, details) ((Error) { pos_start, pos_end, error, details })

const char* Error_ToString(Error self)
{
	char* _Buffer = (char*)malloc(sizeof(char) * 512);
	sprintf(_Buffer, "%s: '%s'.", self.error, self.details);
	sprintf(_Buffer, "%s\nFile '%s', line: %d, index: %d.",_Buffer, self.pos_start.filename, self.pos_start.line + 1, self.pos_start.index + 2);

	return _Buffer;
}

#define mk_IllegalCharacterError(pos_start, pos_end, details) ((Error) { pos_start, pos_end, "Illegal Character", details })

void Error_Free(Error* self) 
{
	free(self->error);
	free(self->details);
}
