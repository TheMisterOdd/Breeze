#include "Arg.h"

#include "Lexer.h"

#include <iostream>
#include <string.h>

#define MATCH(x, y) (!strcmp(x, y))

#include "Translater.h"
int Arg::analize(int argc, char** argv)
{
	/* Exiting the program if there are not enought arguments. */
	if (argc <= 1)
	{
		std::cout << (NO_ARGS_ERROR) << std::endl;
		return EXIT_FAILURE;
	}

	/* Iterate over all the arguments, skiping the program name: */
	int i;
	for (i = 1; i < argc; i++)
	{
		/* if the comand was 'help' */
		if (MATCH(argv[i], KW_HELP))
		{
			std::cout << (HELP) << std::endl;
			break;
		}
		/* if the comand was 'version' */
		else if (MATCH(argv[i], KW_VERSION))
		{
			std::cout << "leiva version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_REVISION << ' ' <<
				SYSTEM_ARCH << SYSTEM_OS << std::endl;
			break;
		}
		/* if the comand was 'build' */
		else if (MATCH(argv[i], KW_BUILD))
		{
			if (argv[i + 1] == NULL)
			{
				std::cout << (NO_BUILD_ARGS_ERROR) << std::endl;
				return EXIT_FAILURE; /* Fail. */
			}


			Translater t(argc, argv, i);
			t.build();

			return EXIT_SUCCESS;
		}
		/* if the comand was 'run' */
		else if (MATCH(argv[i], KW_RUN))
		{
			if (argv[i + 1] == NULL)
			{
				std::cout << (NO_RUN_ARGS_ERROR) << std::endl;
				return EXIT_FAILURE; /* Fail. */
			}

			//C out;
			//translater_run(argc, argv, i, &out);
			break;
		}
		/* if the command is unknown */
		else
		{
			std::cout << "leiva " << argv[i] << ": unknow command\n" << std::endl;
			return EXIT_FAILURE; /* Fail. */
		}
	}

	return EXIT_SUCCESS;
}
