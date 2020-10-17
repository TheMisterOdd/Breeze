#pragma once

#include "Tokenizer.h"
#include <unordered_map>

class Gen
{
public:

	Gen(Files& fp);

	void Build();

	~Gen();

private:

	Files& fp;

	std::string m_PkgName;

	/* all the files imports */
	std::list<std::string> m_Imports;

	/* map<Name, Value> */
	std::unordered_map<std::string, std::string> m_Const;

	/* function names */
	std::list<std::string> m_Funcs;
	
};

