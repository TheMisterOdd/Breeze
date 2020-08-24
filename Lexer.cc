#include "Lexer.h"
#include <assert.h>
#include <iostream>

Lexer::Lexer(const char* filename)
{
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);

	this->file = Lexer::read_file(filename);
	this->index = -1;
}

Lexer::~Lexer()
{
	delete[] this->file, this->filename;
}

std::list<std::string> Lexer::make_tokens()
{
	std::list<std::string> ls;

	char current;
	while ((current = file[++index]) != '\0')
	{
		if ((current == ' ' || current == '\t' || current == '\n' || current == '\r'))
		{
			continue;
		}
		else if ((current <= 47 && current >= 33) ||
			(current <= 64 && current >= 58) ||
			(current <= 96 && current >= 91) ||
			(current <= 126 && current >= 123))
		{
			if (current == '"')
			{
				this->make_quotes(ls);
			}
			else if (current == ':' && file[index + 1] == '=')
			{
				ls.push_back((char*)":=");
				index++;
			}
			else if (current == '@' && (file[index + 1] <= 'z' && file[index + 1] >= 'a'))
			{
				this->make_keywords(ls);
				index++;
			}
			else if (current == ';') 
			{
				std::cerr << "leiva: unecessary ';' on " << this->filename << "." << std::endl;
			}
			/* skiping characters if there are in a comment */
			else if (current == '/' && file[index + 1] == '*')
			{
				while (file[++index])
					if (file[index] == '*' && file[index + 1] == '/') { break; };
				index++;
			}
			else if (current == '/' && file[index + 1] == '/')
			{
				while (file[++index])
					if (file[index] == '\n') { break; };
				index++;
			}
			else
			{
				char* c = (char*)malloc(sizeof(char) * 4);
				sprintf(c, "%c\0", current);
				ls.push_back(c);
			}
		}
		else if ((current <= 'z' && current >= 'a') || (current <= 'Z' && current >= 'A'))
		{
			this->make_keywords(ls);
		}
		else if (current <= '9' && current >= '0')
		{
			this->make_numbers(ls);
		}

	}

	return ls;
}

char* Lexer::read_file(const char* filename)
{
	long length;
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
	{
		fprintf(stderr, "leiva error: cannot find %s\n", filename);
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = (char*)malloc((length + 1) * sizeof(char));
	assert(buffer);

	fread(buffer, sizeof(char), length, f);
	buffer[length] = '\0';

	fclose(f);

	return buffer;
}

void Lexer::make_keywords(std::list<std::string>& ls)
{
	char current, * keyword = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	strcpy(keyword, "");

	size_t _index = this->index;
	while ((current = this->file[_index++]) != '\0')
	{
		if (
			(current == ' ' || current == '\t' || current == '\n' || current == '\r') ||
			(current <= 47 && current >= 33) ||
			(current <= 64 && current >= 58) ||
			(current <= 96 && current >= 91) ||
			(current <= 126 && current >= 123))
		{
			break;
		}
		else {
			sprintf(keyword, "%s%c", keyword, current);
		}
	}

	this->index = _index - 2;
	ls.push_back((char*)keyword);
}

void Lexer::make_numbers(std::list<std::string>& ls)
{
	char current, * number = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	strcpy(number, "");

	bool dot = false;
	size_t _index = this->index;
	while ((current = file[_index++]) != '\0')
	{
		if ((current <= '9' && current >= '0') || current == '.')
		{
			if (current == '.')
			{
				if (dot == true)
				{
					fprintf(stderr, "leiva parse error: multiple decimal definition");
					exit(-1);
				}
				dot = true;
			}
			sprintf(number, "%s%c", number, current);
		}
		else {
			break;
		}
		this->index++;
	}

	this->index = _index - 2;
	ls.push_back((char*)number);
}

void Lexer::make_quotes(std::list<std::string>& ls)
{
	char current, * quotes = (char*)malloc(sizeof(char) * STRING_MAX_LEN);
	strcpy(quotes, "\"");

	bool dot = false;
	while ((current = file[++this->index]) != '\0')
	{
		sprintf(quotes, "%s%c", quotes, current);
		if (current == '"')
		{
			break;
		}
	}

	ls.push_back((char*)quotes);
}