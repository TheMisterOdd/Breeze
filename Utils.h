#pragma once

#include <stdio.h>

////////////////////////////////////
//	Uselful functions macros:
////////////////////////////////////

#define panic(_Buffer, ...) fprintf(stderr, _Buffer)
#define cast_void_ptr(T, ptr) (*((T*)ptr))

////////////////////////////////////
//	Position Util:
////////////////////////////////////

typedef struct
{
	int index, line, column;
	char* filename, *filetext;
} Position;

Position mk_Position(int index, int line, int column, const char* filename, const char* filetext)
{
	Position self;
	self.index = index;
	self.line = line;
	self.column = column;

	self.filename = (char*)malloc(sizeof(char) * (strlen(filename) + 1));
	strcpy_s(self.filename, strlen(filename) + 1, filename);

	self.filetext = (char*)malloc(sizeof(char) * (strlen(filetext) + 1));
	strcpy_s(self.filetext, strlen(filetext) + 1, filetext);

	return self;
}

void Position_Advance(Position* self, char current_char)
{
	self->index++;
	self->column++;

	if (current_char == '\n')
	{
		self->line++;
		self->column = 0;
	}
}

Position Position_Copy(Position self)
{
	Position Cpy;
	memcpy(&Cpy, &self, sizeof(Position*));
	return Cpy;
}
