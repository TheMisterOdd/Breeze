#include <stdio.h>

#define LEXER_IMPL
#define LIST_IMPL

#include "lexer.h"
#include "list.h"

char* input() 
{
	char *_Input_Ptr = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	if (_Input_Ptr == NULL) 
	{
		fprintf(stderr, "[Error]: 'input' failed. Cannot alloc memory for the new '_Input_Ptr' object.\n");
		exit(-1);
	}

	fgets(_Input_Ptr, STRING_MAX_LEN, stdin);
	int i;
	for (i = 0; i < STRING_MAX_LEN; i++)
	{
		if (_Input_Ptr[i] == '\n') 
		{
			_Input_Ptr[i] = '\0';
			break;
		}
	}
	return _Input_Ptr;
}

int main(void) 
{
	lexer_t* lex = lexer_init();
	struct list_t* ls = NULL;

	while (1) 
	{
		printf(" > ");
		char* _data = input();

		lexer_set_text(lex, _data);
		free(_data);

		ls = lexer_lex(lex);
		_data = list_to_string(&ls);
		printf(" < %s\n\n", _data);

		free(_data);
		free(ls);
	}
	
	free(lex);

	return 0;
}