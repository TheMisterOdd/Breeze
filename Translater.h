#pragma once
#include <list>
#include <vector>
#include <string>
#include <thread>

#define ERROR_NOT_LEI_EXTENSION "leiva build: invalid extension at given file '%s'. Should use '.lei' extension.\n"

class Translater
{
public:


	Translater(int argc, char** argv, int from);

	void build();

	~Translater();

private:
	std::list<std::string> filenames;

	std::string executable_name, flags;
	size_t len;

	int argc, from;
	char**& argv;
};

