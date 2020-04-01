// Utils:
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

// IO:
#include <stdio.h>
#include <dirent.h>

#define HELP \
"Leiva is a tool for managing Go source code.\n\n"\
"Usage: \n\n\tleiva [command / file] [arguments]\n\n"\
"Commands: \n\n"\
"\tbuild       compile packages and dependencies\n"\
"\tversion     prints leiva version\n"\
"\tdoc         opens leiva-doc\n"\
"\tlist		   list packages or modules"\

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

void print_dir() 
{
	struct dirent *de;  // Pointer for directory entry 

	// opendir() returns a pointer of DIR type.  
	DIR *dr = opendir("packages/.");

	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
	{
		printf("Could not open current directory");
		return;
	}

	while ((de = readdir(dr)) != NULL) 
	{
		if (!strcmp(".", de->d_name) || !strcmp("..", de->d_name))
			continue;

		printf("%s\n", de->d_name);
	}
		

	closedir(dr);
}

int main(int args, char** argv) 
{
    // Check if there are enough arguments:
	if (args <= 1) 
    	{
        	printf("%s: no listed files to interpret or command.\nUse '%s help', for help.\n", argv[0], argv[0]);
        	return -1;
    	}
	
	if (args <= 2) 
	{
		if (!strcmp(argv[1], "help")) 
		{
			if (argv[2] != NULL) 
			{
				
			} 
			else 
			{
				puts(HELP);
				return 0;
			}
			
		} 
		else if (!strcmp(argv[1], "version"))
		{
			printf("%d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
			return 0;
		} 
		else if (!strcmp(argv[1], "doc")) 
		{
			system("doc\\home.html");
			return 0;
		}
		else if (!strcmp(argv[1], "list"))
		{
			print_dir();
			return 0;
		}
	}

	// Allocating the returning buffer for interpret:
    	char* _Buffer = (char*)malloc(sizeof(char) * 512);
    	if (_Buffer == NULL) 
    	{
        	printf("%s: alloc error: could alloc internal variable '_Buffer'.\n", argv[0]);
        	return -1;
    	}
    	strcpy(_Buffer, "leivac");
    	bool ifExit = false, ifArgs = false;

	// Getting files:
    	for (int i = 1; i < args; i++) 
    	{
        	// Check if the the extension of a file is '.lei':
        	int len = strlen(argv[i]);
        	if (argv[i][len - 4] != '.' || argv[i][len - 3] != 'l' ||
            	    argv[i][len - 2] != 'e' || argv[i][len - 1] != 'i') {
            		printf("%s: error: Invalid type at given file '%s'. Should use '.lei' extension.\n", argv[0], argv[i]);
            		ifExit = true; 
		}

        	// Cheking if the given file existis:
		FILE* fp = fopen(argv[i], "rb");
        	if (fp == NULL) 
        	{
            		printf("%s: %s: No such file or directory.\n", argv[0], argv[i]);
            		ifExit = true;
        	}
        	fclose(fp);
        
        	if (!ifExit) 
            		sprintf_s(_Buffer, sizeof(char) * 512, "%s %s", _Buffer, argv[i]);
    	}
	
	if (!ifExit) 
	{
		puts(_Buffer);
		system(_Buffer);
	}
	
    	free(_Buffer);
    	return ifExit ? -1 : 0;
}
