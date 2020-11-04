#include "Gen.h"

#include <iostream>

Gen::Gen(Files& fp)
	: fp(fp)
{	
	for (auto& tok : fp.tokens) {
		std::cout << tok << std::endl;
	}

	for (auto f = fp.tokens.begin(); f != fp.tokens.end(); f++) {
		if (*f == "crate") {
			auto c = std::next(f);
			this->m_PkgName = *c;
		}
		if (*f == "import") {
			this->GetImports(++f, fp.tokens.end());
		}
		if (*f == "const") {
			this->GetConsts(++f, fp.tokens.end());
		}
		if (*f == "func") {
			this->GetFunctions(++f, fp.tokens.end());
		}
	}

	/* print all */
	std::cout << "crate " << this->m_PkgName << std::endl;

	/* imports */
	std::cout << "import (\n";
	for (auto& imp : this->m_Imports) {
		std::cout << "\t" << imp << "" << std::endl;
	}
	std::cout << ")" << std::endl;

	/* consts */
	std::cout << "const (\n";
	for (auto& consts : this->m_Const) {
		std::cout << "\t" << consts.name << " = " << consts.value << std::endl;
	}
	std::cout  << ")" << std::endl;

	/* functions */
	for (auto& funcs : this->m_Functions) {
		std::cout << "func " << funcs.name << "(";
		for (auto& arg : funcs.args) {
			std::cout << arg.name << " : " << arg.type << ", ";
		}
		std::cout << ") ";
		for (auto ret : funcs.returns_types) {
			std::cout << ret << ", ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

void Gen::Build()
{
	
}

Gen::~Gen()
{
}

void Gen::GetImports(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	if ((*f).at(0) == '"') {
		this->m_Imports.push_back(*f);
		return;
	}
}

void Gen::GetConsts(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	if (*f != "(") {
		std::string name = *f;
		f++;
		if (*f == "=") {
			f++;
			this->m_Const.push_back({ name, *f });
		}
		return;
	}

	/*	Parenthesis implementation here. 

		E.g:
		const (
			...
		)
	*/


}

void Gen::GetFunctions(std::list<std::string>::iterator& f, std::list<std::string>::iterator end)
{
	Function fn;

	/* get name of the function */
	fn.name = *f;
	
	f++;
	f++;
	for (; f != end; f++) {
		if (*f == ")")
			break;

		std::string arg_name = *f;
		std::string arg_type = "";
		f++; // skip to next token (must be a ':')
		f++; // skipping the  ':'
		for (; f != end; f++) {
			if (*f == "," || *f == ")") {
				fn.args.push_back({ arg_name, arg_type });
				arg_name = "";
				arg_type = "";
				break;
			}
			arg_type += *f;
		}

		if (*f == ")")
			break;
	}

	this->m_Functions.push_back(fn);
}
