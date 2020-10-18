#pragma once

#include "Tokenizer.h"
#include <unordered_map>

typedef struct {
	std::string name;
	std::unordered_map<std::string, std::string> args;
	std::list<std::string> returns_types;
	std::string body;
} Function;

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

	/* map<Constant Name, Value of the constant> */
	std::unordered_map<std::string, std::string> m_Const;

	/* */
	std::list<Function> m_Functions;
	
};

