#include "Tokenizer.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

Tokenizer::Tokenizer(std::list<std::string>::iterator args, std::list<std::string>::iterator end)
{
	auto n = std::next(args, 1); /* skipping one element of the list, because is the compilation mode */
	for (auto it = n; it != end; it++) 
	{
		/* add the files paths to a list */
		if (it->substr(it->find_last_of(".") + 1) == "bz")
			this->m_Files.push_back(*it);

		/* add flags */
		else if ((*it)[0] == '-')
			this->m_Flags.push_back(*it);

		/* warning */
		else
			std::cerr << "breeze warning: skipping file or flag: '" << *it << "'." << std::endl;
	}

	this->m_Files.sort();
	this->m_Flags.sort();
	this->m_Files.unique();
	this->m_Flags.unique();

	this->Tokenize();
}

Tokenizer::~Tokenizer() {}

std::list<Files> Tokenizer::GetTokens()
{
	return this->m_Tokens;
}

void Tokenizer::Tokenize()
{	
	for (auto& fp : this->m_Files)
		this->m_Tokens.push_back({ fp, this->GetTokenData(this->ReadFile(fp)) });
}

std::list<std::string> Tokenizer::GetTokenData(std::string data)
{
	std::list<std::string> ls;
	for (size_t i = 0; i < data.size(); i++) {
		const char c = data.at(i);
		if (isblank(c) || iscntrl(c)) {
			if (c == '\n')
				ls.push_back("\\n");

			continue;
		}
		else if (c == '"') {
			ls.push_back(this->GetQuotes(data, i));
		}

		/* skip comments */
		else if (c == '/' && data.at(i + 1) == '/') {
			i += 2;
			while (data.at(i) != '\n' && data.at(i) != '\0') {
				i++;
			}
			ls.push_back("\\n");
		}

		/* bitwise operators */
		else if (c == '<' && data.at(i + 1) == '<') {
			ls.push_back("<<");
			i++;
		}
		else if (c == '>' && data.at(i + 1) == '>') {
			ls.push_back(">>");
			i++;
		}

		/* and & or of if statements. */
		else if (c == '&' && data.at(i + 1) == '&') {
			ls.push_back("&&");
			i++;
		}
		else if (c == '|' && data.at(i + 1) == '|') {
			ls.push_back("||");
			i++;
		}

		/* increment and dicrement */
		else if (c == '+' && data.at(i + 1) == '+') {
			ls.push_back("++");
			i++;
		}
		else if (c == '-' && data.at(i + 1) == '-') {
			ls.push_back("--");
			i++;
		}

		/* comparasion */
		else if (c == '=' && data.at(i + 1) == '=') {
			ls.push_back("==");
			i++;
		}
		else if (c == '!' && data.at(i + 1) == '=') {
			ls.push_back("!=");
			i++;
		}
		else if (c == '<' && data.at(i + 1) == '=') {
			ls.push_back("<=");
			i++;
		}
		else if (c == '>' && data.at(i + 1) == '=') {
			ls.push_back(">=");
			i++;
		}

		/* equals */
		else if (c == ':' && data.at(i + 1) == '=') {
			ls.push_back(":=");
			i++;
		}
		else if (c == '+' && data.at(i + 1) == '=') {
			ls.push_back("+=");
			i++;
		}
		else if (c == '-' && data.at(i + 1) == '=') {
			ls.push_back("-=");
			i++;
		}
		else if (c == '*' && data.at(i + 1) == '=') {
			ls.push_back("*=");
			i++;
		}
		else if (c == '/' && data.at(i + 1) == '=') {
			ls.push_back("/=");
			i++;
		}
		else if (c == '%' && data.at(i + 1) == '=') {
			ls.push_back("%=");
			i++;
		}
		else if (c == '|' && data.at(i + 1) == '=') {
			ls.push_back("|=");
			i++;
		}
		else if (c == '&' && data.at(i + 1) == '=') {
			ls.push_back("&=");
			i++;
		}
		else if (c == '^' && data.at(i + 1) == '=') {
			ls.push_back("^=");
			i++;
		}
		else if (c == '<' && data.at(i + 1) == '<' && data.at(i + 1) == '=') {
			ls.push_back("<<=");
			i++;
		}
		else if (c == '>' && data.at(i + 1) == '>' && data.at(i + 1) == '=') {
			ls.push_back(">>=");
			i++;
		}

		else if (isalpha(c)) {
			ls.push_back(this->GetAlpha(data, i));
		}
		else if (ispunct(c)) {
			ls.push_back(std::string("") + c);
		}
		else if (isdigit(c)) {
			ls.push_back(this->GetNumbers(data, i));
		}
	}


	return ls;
}

std::string Tokenizer::GetAlpha(std::string& data, size_t& i)
{
	std::string ret;
	for (; i < data.size(); i++) {
		const char c = data.at(i);
		if (!isalnum(c))
			break;

		ret += c;
	}
	i--;
	return ret;
}

std::string Tokenizer::GetNumbers(std::string& data, size_t& i)
{
	std::string ret;
	for (; i < data.size(); i++) {
		const char c = data.at(i);
		if (c == '.') {
			ret += c;
			continue;
		}
		if (!isdigit(c))
			break;

		ret += c;
	}
	i--;
	return ret;
}

std::string Tokenizer::GetQuotes(std::string& data, size_t& i)
{
	i++;
	std::string ret = "\"";
	for (; i < data.size(); i++) {
		const char c = data.at(i);
		if (c == '\\') {
			ret += c;
			ret += data[++i];
			continue;
		}
		if (c == '"')
			break;
			
		ret += c;
	}
	return ret + "\"";
}

std::string Tokenizer::ReadFile(std::string filename)
{
	long length;
	FILE* f = fopen(filename.c_str(), "rb"); /* was "rb" */
	if (f == NULL)
	{
		fprintf(stderr, "[Error]: Cannot allocate memory for new file.\n");
		exit(-1);
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buffer = (char*)malloc((length + 1) * sizeof(char));
	if (buffer)
		fread(buffer, sizeof(char), length, f);
	fclose(f);
	buffer[length] = '\0';
	return std::string(buffer);
}
