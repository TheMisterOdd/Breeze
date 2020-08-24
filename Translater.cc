#include "Translater.h"
#include "Lexer.h"

#include <iostream>
#include <memory>

Translater::Translater(int argc, char** argv, int from)
	:argv(argv)
{
	/* Memory initialization: */
	this->len = argc - (from + 1);
	this->executable_name = "a";
	this->flags = "";

	this->from = from;
	this->argc = argc;
}

void thrd(const char* file) 
{
	Lexer l(file);
	std::list<std::string> toks = l.make_tokens();
	for (const auto& t : toks)
	{
		std::cout << t << ", ";
	}
	std::cout << "\n\n";
}

void Translater::build()
{
	std::list<std::unique_ptr<std::thread>> threads;
	/* Loop over the arguments */
	int i;
	for (i = from + 1; i < argc; i++)
	{
		size_t len = strlen(argv[i]);
		/* check if file has .lei extension */
		if (len >= 4 && argv[i][len - 4] == '.' && argv[i][len - 3] == 'l' && argv[i][len - 2] == 'e' && argv[i][len - 1] == 'i')
		{
			this->filenames.push_back(argv[i]);
			threads.push_back(std::unique_ptr<std::thread>(new std::thread(thrd, argv[i])));
			threads.back().get()->detach();
		}
		else if (argv[i][0] == '-')
		{
			/* gets the flags for the compilation */
			this->flags += argv[i] + std::string(" ");
			this->len--;
		}
		else
		{
			/* error hndl */
			printf(ERROR_NOT_LEI_EXTENSION, argv[i]);
			break;
		}
	}

	for (auto& th : threads)
	{
		while (th.get()->joinable());
	}

	std::string _out = "gcc ";
	for (const auto& fp : this->filenames)
	{
		_out += fp + std::string(".c ");
	}
	_out += this->flags;
	std::cout << _out << std::endl;
}

Translater::~Translater()
{
	this->argv = nullptr;
}
