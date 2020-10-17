#pragma once

#include <list>
#include <string>

typedef struct {
	std::string name;
	std::list<std::string> tokens;
} Files;

class Tokenizer 
{
public:
	Tokenizer(std::list<std::string>::iterator args, std::list<std::string>::iterator end);

	~Tokenizer();

	std::list<Files> GetTokens();

private:

	void Tokenize();

	std::list<std::string> GetTokenData(std::string data);

	std::string GetAlpha(std::string& data, size_t& i);

	std::string GetNumbers(std::string& data, size_t& i);

	std::string GetQuotes(std::string& data, size_t& i);

	std::string ReadFile(std::string filename);

	std::list<std::string> m_Files;
	std::list<std::string> m_Flags;

	std::list<Files> m_Tokens;
};

