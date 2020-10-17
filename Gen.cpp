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
			for (auto imports = ++f; imports != fp.tokens.end(); imports++) {
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
		if (*f == "const") {
			for (auto consts = ++f; consts != fp.tokens.end(); consts++) {

				auto eq = std::next(consts);
				auto value = std::next(consts, 2);
				if (eq == fp.tokens.end())
					break;

				

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
	}

	/* print all */
	std::cout << "package " << this->m_PkgName << std::endl;
	std::cout << "import (\n";
	for (auto it = this->m_Imports.begin(); it != this->m_Imports.end(); it++) {
		std::cout << "\t" << *it << std::endl; 
	}
	std::cout << ")" << std::endl;
	std::cout << "const (\n";
	for (auto it = this->m_Const.begin(); it != this->m_Const.end(); it++) {
		std::cout << "\t" << it->first << " = " << it->second << std::endl;
	}
	std::cout  << ")" << std::endl;
}

void Gen::Build()
{
}

Gen::~Gen()
{
}
