#include <stdio.h>
#include <malloc.h>

char* bytes_load(const char* _Src)
{
    char* _Buffer = NULL;
    FILE* fp = fopen(_Src, "rb");

    if (!fp) 
        return NULL;
    
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    _Buffer = (char*)malloc(sizeof(char) * length);
    fread(_Buffer, length, sizeof(char), fp);
    fclose(fp);

    if (!_Buffer) 
    {   
        puts("[Error]: Cannot read data, and data was NULL");
        free(_Buffer);
        return NULL;
    }

    return _Buffer;
}

int main(int args, char** argv) 
{
	for (int i = 1; i < args; i++) 
	{
		puts(bytes_load(argv[i]));
	}

	return 0;
}