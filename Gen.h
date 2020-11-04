#pragma once

#include "Tokenizer.h"
#include <map>

typedef struct {
	std::string name;
	std::string type;
} Argument;

typedef struct {
	std::string name;
	std::list<Argument> args;
	std::list<std::string> returns_types;
	std::string body;
} Function;

typedef struct {
	std::string name;
	std::string value;
	std::string type;
} Constants;

class Gen
{
public:

	Gen(Files& fp);

	void Build();

	~Gen();

private:

	void GetImports(std::list<std::string>::iterator& f, std::list<std::string>::iterator end);

	void GetConsts(std::list<std::string>::iterator& f, std::list<std::string>::iterator end);

	void GetFunctions(std::list<std::string>::iterator& f, std::list<std::string>::iterator end);

	Files& fp;

	std::string m_PkgName;

	/* all the files imports */
	std::list<std::string> m_Imports;

	/* list of the constants in a file */
	std::list<Constants> m_Const;

	/* list of functions in th file */
	std::list<Function> m_Functions;
	
};

