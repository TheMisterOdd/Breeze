#define LIST_IMPL
#include "args.h"

#include <stdio.h>
#include <string.h>


/*
    Main is in charge of getting the program arguments and
    analizing them in the 'args_analize' function.
 */
int main(int argc, const char** argv) 
{   

    // Cheking if arguments are less or equal to one
    // the program cannot operate with less than 2 commands,
    // so an error is shown
    if (argc <= 1)
    {
        fprintf(stderr, "%s\n", NO_ARGS_ERROR);
		return 1;
    }

    // Loop over 'argv' to get the program arguments
    // to perform the action that the user has indicated
    int i;
    for (i = 1; i < argc; i++)
    {
        // if argument is 'help'
        // in development
        if (MATCH(argv[i], KW_HELP))
		{
			printf("%s\n", HELP);
			break;
		}
        // if argument was 'version'
        // shows the version of the compiler,
        // also architecture and computer operating
        // system
        else if (MATCH(argv[i], KW_VERSION)) /* if the comand was 'version' */
		{
            printf("leiva version %d.%d.%d %s/%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, SYSTEM_ARCH, SYSTEM_OS);
			break;
		}
        // if the argument was 'build'
        // a specific function is going to be call
        // to translate the program into a binary file
		else if (MATCH(argv[i], KW_BUILD)) /* if the comand was 'build' */
		{
            translater_t t;
            translater_create(&t, &argv[i + 1], argc - i - 1);
            translater_build(&t);
			break;
		}
        // if the argument was 'build'
        // a specific function is going to be call
        // to translate the program into a binary file
        // and then run the executable
		else if (MATCH(argv[i], KW_RUN)) /* if the comand was 'run' */
		{
			if (argv[i + 1] == NULL)
			{
                printf("%s\n", NO_RUN_ARGS_ERROR);
				return 1; /* Fail. */
			}

			/*C out;
			//translater_run(argc, argv, i, &out);*/
			break;
		}
        // (in development)
        // this arguments parse the given file an shows its functions,
        // constanst and descriptions
        else if (MATCH(argv[i], KW_FMT))
        {
            puts("leiva fmt: in development.");
        }
        // If the command was unknown
        // the compiler will print this:
		else
		{
            fprintf(stderr, "leiva %s: unknow command\n", argv[i]);
			return 1; /* Fail. */
		}
    }
    return 0;
}