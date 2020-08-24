#pragma once

#include <list>
#include <string>

#define STRING_MAX_LEN 4096

class Lexer
{

public:
	Lexer(const char* file);

	~Lexer();

	std::list<std::string> make_tokens();

private:

	static char* read_file(const char* filename);

	void make_keywords(std::list<std::string>& ls);

	void make_numbers(std::list<std::string>& ls);

	void make_quotes(std::list<std::string>& ls);

	char* file, *filename;
	std::list<std::string> filenames;
	size_t index;


};

