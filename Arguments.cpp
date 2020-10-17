#include "Arguments.h"

#include "Tokenizer.h"
#include "Gen.h"

#include <iostream>
#include <thread>


int Arguments::Analize(std::list<std::string> args)
{
	std::list<std::thread> thds;
	for (auto it = args.begin(); it != args.end(); it++)
	{
		if (*it == "c") 
		{
			auto next = std::next(it);
			if (next != args.end()) 
			{	
				/* parallel processing of files */
				thds.push_back(std::thread(
					[](std::list<std::string>::iterator it, std::list<std::string>::iterator end) {
						Tokenizer toks(it, end);
						for (auto& ls : toks.GetTokens()) {
							Gen gen(ls);
						}
					},
					it, args.end()
				));				
			}
			else 
			{
				std::cout << "breeze compile: not files or aguments listed." << std::endl;
			}
		}
		else if (*it == "r")
		{
			//std::cout << "wanna compile & run" << std::endl;
		}
	}

	for (auto& th : thds) {
		th.join();
	}

	return 0;
}
