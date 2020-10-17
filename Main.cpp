#include "Arguments.h"

#include <iostream>
int main(int argc, const char** argv)
{	
	if (argc == 1) {
		std::cout <<
			"breeze error: not arguments were listed.\n" <<
			"Use 'breeze help' for more information." <<
		std::endl;
	}

	/* adds the arguments to vector */
	std::list<std::string> args;
	args.assign(argv, argv + argc);
	args.erase(args.begin());

	/* Analize that vector */
	return Arguments::Analize(args);
}