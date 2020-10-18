#include "Gen.h"

#include <iostream>

Gen::Gen(Files& fp)
	: fp(fp)
{
	for (auto f = fp.tokens.begin(); f != fp.tokens.end(); f++) {
		if (*f == "package") {
			auto c = std::next(f);
			this->m_PkgName = *c;
		}
		if (*f == "import") {
			this->GetImports(++f, fp.tokens.end());
		}
		if (*f == "const") {
			this->GetConsts(++f, fp.tokens.end());
		}
		if (*f == "fun") {
			this->GetFunctions(++f, fp.tokens.end());
		}
	}

	/* print all */
	std::cout << "\n\npackage " << this->m_PkgName << std::endl;

	/* imports */
	std::cout << "import (\n";
	for (auto& imp : this->m_Imports) {
		std::cout << "\t" << imp << std::endl; 
	}
	std::cout << ")" << std::endl;

	/* consts */
	std::cout << "const (\n";
	for (auto& consts : this->m_Const) {
		std::cout << "\t" << consts.first << " = " << consts.second << std::endl;
	}
	std::cout  << ")" << std::endl;

	/* functions */
	for (auto& funcs : this->m_Functions) {
		std::cout << "fun " << funcs.name << "(";
		for (auto& arg : funcs.args) {
			std::cout << arg.first << " " << arg.second << " ,";
		}
		std::cout << ") -> ";
		for (auto ret : funcs.returns_types) {
			std::cout << ret << ", ";
		}
		std::cout << "\n";
	}
}

void Gen::Build()
{
	
}

Gen::~Gen()
{
}

void Gen::GetImports(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	for (auto imports = f; imports != end; imports++) {
		if (*imports == "\\n") {
			continue;
		}
		else if ((*imports).at(0) == '"') {
			this->m_Imports.push_back(*imports);
		}
		else {
			break;
		}
	}
}

void Gen::GetConsts(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	for (auto consts = f; consts != fp.tokens.end(); consts++) {

		auto eq = std::next(consts);
		auto value = std::next(consts, 2);
		if (eq == fp.tokens.end() || value == fp.tokens.end())
			break;

		/* add support for skipping new lines */

		if (*consts == "\\n") {
			continue;
		}
		else if (*eq == "=" && !(*value).empty()) {
			std::string val = "";
			for (auto v = value; v != fp.tokens.end(); v++) {
				if (*v == "\\n")
					break;
				val += " " + *v;
			}

			this->m_Const.insert(std::pair<std::string, std::string>(*consts, val));
		}
	}
}

void Gen::GetFunctions(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	Function fn;

	/* get name of the function */
	fn.name = *f;
	

	this->m_Functions.push_back(fn);
}
