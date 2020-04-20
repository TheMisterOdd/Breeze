#include "Lexer.h"

// Loads from a file:
char* bytes_load(const char* _Src)
{
	char* _Buffer = NULL;

	FILE* fp = NULL;
	fopen_s(&fp, _Src, "rb");

	if (!fp) 
	{
		puts("[Error]: Source file does not exist.");
		return NULL;
	}
	
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	_Buffer = (char*)malloc(sizeof(char) * length);
	fread(_Buffer, length, sizeof(char), fp);
	fclose(fp);

	if (!_Buffer)
	{
		puts("[Error]: Cannot read data.");
		free(_Buffer);
		return NULL;
	}

	return _Buffer;
}

// Returns a char* input from 'stdin': 
char* input()
{
	char* _Buffer = (char*)malloc(sizeof(char) * 512);
	if (_Buffer == NULL) 
	{
		panic("[Error]: Cannot alloc internal variable: '_Buffer'.");
		return NULL;
	}

	fgets(_Buffer, 512, stdin);
	for (int i = 0; i < 512; i++) 
	{
		if (_Buffer[i] == '\n')
			_Buffer[i] = '\0';
	}

	if (!strcmp(_Buffer, "exit()")) 
	{
		free(_Buffer);
		_Buffer = NULL;
		exit(0);
	} 
	else if (!strcmp(_Buffer, "exit"))
	{
		panic("Use exit() or Ctrl-C to exit\n\n");
		free(_Buffer);
		_Buffer = NULL;
	}

	return _Buffer;
}

int main(int args, char** argv)
{
	char* _Buffer = NULL;

	while (1)
	{
		printf("/> ");
		char* _Buffer = input();
		if (_Buffer == NULL)
			continue;

		run("<stdin>", _Buffer);
		
		puts("");
		free(_Buffer);
	}


	return 0;
}