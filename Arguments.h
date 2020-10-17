#pragma once

#include <string>
#include <list>

class Arguments {
public:
	/*
		@breif - Analiz the given arguments
		@param[in] args Is a Vector that contains the program args
		@returns - An exit code
	*/
	static int Analize(std::list<std::string> args);
};

