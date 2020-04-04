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

	return _Buffer;
}

int main(int args, char** argv)
{
	clock_t begin = clock();

	while (true)
	{
		printf("/> ");
		char* _Buffer = input();
		Pair result = run("<stdin>", _Buffer);

		if (result.error.error != NULL)
			puts(Error_ToString(result.error));
		else
			puts(TokenList_ToString(result.list));

		puts("");
		free(_Buffer);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("%s: execution finished. Total time: %.2lf", argv[0], time_spent);
	getchar();
	return 0;
}